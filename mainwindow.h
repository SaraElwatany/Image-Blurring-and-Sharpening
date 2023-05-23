#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "frequency.h"
#include "histograms.h"
#include "filters.h"
#include "tab2dialog.h"

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Mat getImage();


private slots:

    void on_actionUniform_Noise_triggered();

    void on_actionGaussian_Noise_triggered();

    void on_actionSalt_Pepper_Noise_triggered();

    void on_actionMedian_Filter_triggered();

    void on_actionGaussian_Filter_triggered();

    void on_actionAverage_Filter_triggered();

    void on_NormalizeButton_clicked();

    void on_EqualizeButton_clicked();

    void on_NoneButton_clicked();

    void on_tab1_Browse_clicked();

    void on_tab2_Browse_clicked();

    void on_GreyButton_clicked();

    void on_HistogramBox_currentTextChanged(const QString &arg1);

    void on_CumulateBox_currentTextChanged(const QString &arg1);

    void on_spinBox_textChanged(const QString &arg1);

    void on_HistogramBox_activated(int index);

    void on_tab2_currentChanged(int index);

    void on_Median_button_clicked();

    //void on_Median_close_clicked();

    void on_Gaussin_close_clicked();

    void on_Gaussin_button_clicked();

    //void on_Average_close_clicked();

    void on_Average_button_clicked();

    //void on_Local_close_clicked();

    void on_Local_button_clicked();

    void  on_actionLocal_triggered();

    //void on_Global_close_clicked();

    void on_actionGlobal_triggered();

    void on_Global_button_clicked();

    // Edge Detection Menu
    void DisplayOutpt(Mat image);

    void on_actionPrewitt_triggered();

    void on_actionSobel_triggered();

    void on_prewitt_close_clicked();

    void on_prewitt_applay_clicked();

    void on_actionRoberts_triggered();

    void on_actionCanny_triggered();

    void on_canny_applay_clicked();

    void on_canny_close_clicked();

    void on_Sobel_clicked();

    // Noise Addition Box
    void on_noiseclose_clicked();

    void on_noiseBox1_valueChanged(double arg1);

    void on_noiseBox2_valueChanged(double arg1);

    // tab 3
    void on_image_1_low_clicked();

    void on_image_1_high_clicked();

    void on_image_2_low_clicked();

    void on_image_2_high_clicked();

    void on_Hyperid_clicked();

    void on_Tab2_tabBarClicked(int index);


private:
    Ui::MainWindow *ui;
    Mat colored_uploadedImage_2;
    Mat uploadedImage_1;
    Mat uploadedImage_2; 
    Mat NormalizedImg;
    Mat EqualizedImg;
    Mat spareimage;


    Frequency freq;
    Histograms hist;
    QString Norm_Number;
    QImage coloredimage;
    int noise_menu_index;
    double noise_value1=0;
    double noise_value2=0;

    Mat spareimage1;
    Mat uploadedImage;
    Mat originalImage;
    Mat filteredImg;
    Filters kernals;
    int averageKernal;
    int KernalSize;
    int globalT;
    int boxSize;
    int globalMax;
    int c;

    int radius;
    Mat filteredImage;

};
#endif // MAINWINDOW_H
