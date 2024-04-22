#ifndef MAINSTART_H
#define MAINSTART_H

#include <QDialog>
#include <QMessageBox>
#include<string>
#include<iostream>
#include <QImage>
#include<QObject>
#include"filters.h"
using namespace std;


namespace Ui {
class MainStart;
}

class MainStart :  public QDialog,public filters
{
    Q_OBJECT

public:
    explicit MainStart(QWidget *parent = nullptr);
    ~MainStart();

private slots:
    void display_pic(QImage img,QLabel *lab);
    void on_ExitButton_2_clicked();

    void on_EffectsButtonPage2_2_clicked();

   // void on_ExitButton_4_clicked();

    void on_upload_image_clicked();

    void on_BackButton_3_clicked();

    //void on_Camera_button_clicked();

    void on_filter_1_clicked();

    void updateDisplayedImage();


    void on_SaveButton_clicked();

    void on_filter_2_clicked();

    void on_filter_3_clicked();

    void on_filter_7_clicked();

    void on_filter_10_clicked();

    void on_filter_12_clicked();

    void on_filter_13_clicked();

    void on_filter_15_clicked();

    void on_filter_16_clicked();

    void on_filter_17_clicked();

    void on_reset_clicked();

    void on_filter_4_clicked();

    void on_choose_image_clicked();

    void on_filter_5_clicked();

    void on_filter_8_clicked();

    void on_filter_21_clicked();

    void on_filter_20_clicked();

    void on_filter_14_clicked();

    void on_filter_18_clicked();

    void on_filter_11_clicked();

    void on_filter_23_clicked();

    void on_filter_22_clicked();

    void on_filter_6_clicked();

    void on_merge_clicked();

    void on_flipH_clicked();

    void on_flipV_clicked();
    void hide();

    void on_filter_24_clicked();

    void on_filter_9_clicked();

    void on_filter_19_clicked();

    void on_AboutUsButtonPage2_2_clicked();

private:
    Ui::MainStart *ui;

    QImage image;
    QImage image2;
    QImage image3;
    QImage second_image;

};

#endif // MAINSTART_H


