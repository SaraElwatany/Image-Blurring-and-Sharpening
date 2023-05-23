#include "histograms.h"

Histograms::Histograms()
{

}



void Histograms::expand_img_to_optimal(Mat &padded, Mat &image) {
    int m = getOptimalDFTSize(image.rows);
    int n = getOptimalDFTSize(image.cols);
    copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));
}



void Histograms::crop_and_rearrange(Mat &magI) {
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    Mat q0(magI, Rect(0, 0, cx, cy));
    Mat q1(magI, Rect(cx, 0, cx, cy));
    Mat q2(magI, Rect(0, cy, cx, cy));
    Mat q3(magI, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}


void Histograms::DFT(Mat &image, Mat &output) {
    Mat padded;
    expand_img_to_optimal(padded, image);
    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);

    dft(complexImg, complexImg, DFT_COMPLEX_OUTPUT);
    output = complexImg;
}


void Histograms::invers_DFT(Mat &DFT_image, Mat &imgOutput) {
     Mat planes[2];
     idft(DFT_image, DFT_image);
     split(DFT_image, planes);
     normalize(planes[0], imgOutput, 0, 1, NORM_MINMAX);
}


void Histograms::highpassFilter(Mat &dft_filter, int distance) {

    Mat tmp=Mat(dft_filter.rows,dft_filter.cols,CV_32F);
    Point center = cv::Point(dft_filter.rows/2,dft_filter.cols/2);
    double radius;

    for(int i=0;i<dft_filter.rows;i++){
        for(int j=0;j<dft_filter.cols;j++){
            radius = (double)sqrt(pow(i-center.x,2)+pow(j-center.y,2));
            if(radius<distance){
                tmp.at<float>(i,j)=0.0;
            }
            else{
                tmp.at<float>(i,j)=1.0;
            }
        }
    }
    Mat toMerge[] = {tmp, tmp};
    merge(toMerge, 2, dft_filter);
}





void Histograms::lowpassFilter(Mat &dft_filter, int distance) {

    Mat tmp=Mat(dft_filter.rows,dft_filter.cols,CV_32F);
    Point center = cv::Point(dft_filter.rows/2,dft_filter.cols/2);
    double radius;

    for(int i=0;i<dft_filter.rows;i++){
        for(int j=0;j<dft_filter.cols;j++){
            radius = (double)sqrt(pow(i-center.x,2)+pow(j-center.y,2));
            if(radius>distance){
                tmp.at<float>(i,j)=0.0;
            }
            else{
                tmp.at<float>(i,j)=1.0;
            }
        }
    }
    Mat toMerge[] = {tmp, tmp};
    merge(toMerge, 2, dft_filter);
}



Mat Histograms::Hyprid_images(Mat image1,Mat image2,int redius1,int redius2){
    resize(image1, image1, image2.size());
    Mat dft_image1,dft_image2;
    DFT(image1,dft_image1);
    DFT(image2,dft_image2);
    Mat filter_low=dft_image2.clone();
    Mat filter_high=dft_image1.clone();
    lowpassFilter(filter_low, redius1);
    highpassFilter(filter_high, redius2);
    crop_and_rearrange(dft_image1);
    crop_and_rearrange(dft_image2);
    mulSpectrums(dft_image1, filter_low, dft_image1, 0);
    mulSpectrums(dft_image2, filter_high, dft_image2, 0);
    crop_and_rearrange(dft_image1);
    crop_and_rearrange(dft_image2);
    // invers_DFT(dft_image1,dft_image1);
    // invers_DFT(dft_image2,dft_image2);

    Mat hyprid_image=dft_image1+dft_image2;
     invers_DFT(hyprid_image,hyprid_image);

    return hyprid_image;

}
