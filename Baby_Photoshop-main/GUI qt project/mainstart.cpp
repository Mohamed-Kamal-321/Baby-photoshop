#include<iostream>
using namespace std;
#include "mainstart.h"
#include "ui_mainstart.h"
#include "effects_page.h"
#include "mainwindow.h"
#include "elramly_page.h"
#include "bouns.h"
#include "our_team.h"
#include "mainstart.h"
#include "aboutus.h"
#include"filters.h"
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QVector>
#include <QQueue>
#include <QPainter>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

MainStart::MainStart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainStart)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix7(":/photos/project photos/10.png");
    ui->label->setPixmap(pix7);
    ui->merge->hide();
    ui->choose_image->hide();
    ui->flipH->hide();
    ui->flipV->hide();
    connect(ui->filter_4, &QPushButton::clicked, this, &MainStart::on_filter_4_clicked);
    connect(ui->filter_5, &QPushButton::clicked, this, &MainStart::on_filter_5_clicked);
}
MainStart::~MainStart()
{
    delete ui;
}
void MainStart:: hide(){
    ui->merge->hide();
    ui->choose_image->hide();
    ui->flipH->hide();
    ui->flipV->hide();
}
void MainStart::on_ExitButton_2_clicked()
{
    close();
}


void MainStart::on_EffectsButtonPage2_2_clicked()
{
    this->hide();
    close();
    Effects_page effectspage;
    effectspage.setModal(true);
    effectspage.exec();
}

void MainStart::display_pic(QImage img, QLabel *lab) {
    QSize labelSize = lab->size(); // Size of the label
    QImage scaledImage = img.scaled(labelSize, Qt::KeepAspectRatio);

    QPixmap pixmap = QPixmap::fromImage(scaledImage);

    // Calculate the position to center the pixmap within the label
    int xPos = (labelSize.width() - pixmap.width()) / 2;
    int yPos = (labelSize.height() - pixmap.height()) / 2;

    // Create a centered pixmap with transparent background
    QPixmap centeredPixmap(labelSize);
    centeredPixmap.fill(Qt::transparent);
    QPainter painter(&centeredPixmap);
    painter.drawPixmap(xPos, yPos, pixmap);

    // Set the centered pixmap to the label
    lab->setPixmap(centeredPixmap);
}

void MainStart::on_upload_image_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (!file_name.isEmpty()){
        image.load(file_name);
        image2=image.copy();
        image3=image.copy();
       display_pic(image,ui->label_pic);   
    }

}


void MainStart::on_reset_clicked()
{
    image=image2.copy();
    // Set an empty pixmap to label_pic_2
    ui->label_pic_2->setPixmap(QPixmap());

    // Optionally, you can also clear the text of label_pic_2
    ui->label_pic_2->setText("");
}



void MainStart::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void MainStart::updateDisplayedImage() {
    QSize labelSize = ui->label_pic->size(); // Size of the label
    QImage scaledImage = image.scaled(labelSize, Qt::KeepAspectRatio);

    QPixmap pixmap = QPixmap::fromImage(scaledImage);

    // Calculate the position to center the pixmap within the label
    int xPos = (labelSize.width() - pixmap.width()) / 2;
    int yPos = (labelSize.height() - pixmap.height()) / 2;

    // Create a centered pixmap with transparent background
    QPixmap centeredPixmap(labelSize);
    centeredPixmap.fill(Qt::transparent);
    QPainter painter(&centeredPixmap);
    painter.drawPixmap(xPos, yPos, pixmap);

    // Set the centered pixmap to the label
    ui->label_pic_2->setPixmap(centeredPixmap);
}
void MainStart::on_SaveButton_clicked() {
    // Check if there is a modified image in image3
    if (image.isNull()) {
        QMessageBox::critical(this, tr("Error"), tr("No modified image to save!"));
        return;
    }

    // Save the modified image
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.jpg *.bmp)"));
    if (!saveFileName.isEmpty()) {
        if (!image.save(saveFileName)) {
            QMessageBox::critical(this, tr("Error"), tr("Error saving image!"));
        } else {
            QMessageBox::information(this, tr("Success"), tr("Image saved successfully!"));
        }
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Save operation canceled!"));
    }
}


void MainStart::on_filter_1_clicked()
{
    hide();
        greyscale(image);

        updateDisplayedImage();
}

void MainStart::on_filter_2_clicked()
{
    hide();
    Black_and_White(image);

     updateDisplayedImage();
}


void MainStart::on_filter_3_clicked()
{
    hide();
    invert(image);

    updateDisplayedImage();
}


void MainStart::on_filter_7_clicked()
{
    hide();
    darken(image);

    updateDisplayedImage();
}


void MainStart::on_filter_10_clicked()
{
    hide();
        QDialog dialog(this);
        dialog.setWindowTitle("Frame Filter");
        dialog.setFixedSize(400, 300);

        QLabel thicknessLabel("Thickness (1, 2, or 3):", &dialog);
        QSpinBox thicknessSpinBox(&dialog);
        thicknessSpinBox.setRange(1, 3);

        QLabel colorLabel("Frame Color:", &dialog);
        QComboBox colorComboBox(&dialog);
        colorComboBox.addItem("White");
        colorComboBox.addItem("Black");
        colorComboBox.addItem("Red");
        colorComboBox.addItem("Blue");
        colorComboBox.addItem("Green");
        colorComboBox.addItem("Yellow");
        colorComboBox.addItem("Purple");
        colorComboBox.addItem("Orange");
        colorComboBox.addItem("Dark Grey");
        colorComboBox.addItem("Indigo");

        QPushButton applyButton("Apply", &dialog);

        QVBoxLayout layout(&dialog);
        layout.addWidget(&thicknessLabel);
        layout.addWidget(&thicknessSpinBox);
        layout.addWidget(&colorLabel);
        layout.addWidget(&colorComboBox);
        layout.addWidget(&applyButton);
        dialog.setLayout(&layout);

        // Connect Apply button
        connect(&applyButton, &QPushButton::clicked, [&]() {
            // Get thickness and color values
            int thickness = thicknessSpinBox.value();
            QString colorIndex = colorComboBox.currentText();

            // Apply filter
            simple(image, thickness, colorIndex);

            // Update displayed image
            updateDisplayedImage();

            // Close the dialog
            dialog.close();
        });

        dialog.exec();



}


void MainStart::on_filter_12_clicked()
{
    hide();
    applySepiaTone(image);

    updateDisplayedImage();
}


void MainStart::on_filter_13_clicked()
{
     blur(image);
     hide();

     updateDisplayedImage();
}


void MainStart::on_filter_15_clicked()
{
    oil_paint(image);
    hide();

    updateDisplayedImage();
}


void MainStart::on_filter_16_clicked()
{
    old_tv((image));
    hide();
     updateDisplayedImage();
}


void MainStart::on_filter_17_clicked()
{
    purple(image);
    hide();

    updateDisplayedImage();
}




void MainStart::on_filter_4_clicked()
{
    ui->merge->show(); // Show the merge button
    ui->choose_image->show(); // Show the choose_image button
    ui->flipH->hide();
    ui->flipV->hide();
}


void MainStart::on_choose_image_clicked()
{
    QString file_name2 = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (!file_name2.isEmpty()){
        second_image.load(file_name2);
    }

}


void MainStart::on_filter_5_clicked()
{
    ui->flipH->show(); // Show the flipH button
    ui->flipV->show(); // Show the flipV button
    ui->merge->hide();
    ui->choose_image->hide();

}



void MainStart::on_filter_8_clicked()
{
    hide();
    lighten(image);

    updateDisplayedImage();
}


void MainStart::on_filter_21_clicked()
{
    hide();
        hide();
        QDialog dialog(this);
        dialog.setWindowTitle("Fancy Frame Filter");
        dialog.setFixedSize(400, 200);

        QLabel titleLabel("Select Frame Type:", &dialog);

        QPushButton fancyButton("Fancy Frame 1", &dialog);
        QPushButton alternatingButton("Fancy Frame 2", &dialog);

        QVBoxLayout layout(&dialog);
        layout.addWidget(&titleLabel);
        layout.addWidget(&fancyButton);
        layout.addWidget(&alternatingButton);
        dialog.setLayout(&layout);

        // Connect Fancy Frame button
        connect(&fancyButton, &QPushButton::clicked, [&]() {
            // Apply Fancy Frame filter
            frame(image, 1);

            // Update displayed image
            updateDisplayedImage();

            // Close the dialog
            dialog.close();
        });

        // Connect Alternating White and Black Frame button
        connect(&alternatingButton, &QPushButton::clicked, [&]() {
            // Apply Alternating White and Black Frame filter
            frame(image, 2);

            // Update displayed image
            updateDisplayedImage();

            // Close the dialog
            dialog.close();
        });

        dialog.exec();
    }






void MainStart::on_filter_20_clicked()
{
    hide();
    Detect_Image_Edges(image);

    updateDisplayedImage();

}


void MainStart::on_filter_14_clicked()
{
    hide();
    wano(image);

    updateDisplayedImage();

}


void MainStart::on_filter_18_clicked()
{
    hide();
    infrared(image);

    updateDisplayedImage();

}


void MainStart::on_filter_11_clicked()
{
    hide();
    QDialog dialog(this);
    dialog.setWindowTitle("Skew");
    dialog.setFixedSize(400, 300);

    QLabel * angle= new QLabel(" Skew angle:", &dialog);
    angle->setGeometry(20, 20, 140, 30);

    QSpinBox *spinBox1 = new QSpinBox(&dialog);
    spinBox1->setGeometry(180, 20, 100, 30);
    spinBox1->setRange(1, 89);

    QPushButton *applyButton = new QPushButton("continue", &dialog);
    applyButton->setGeometry(160, 250, 80, 30);

    connect(applyButton, &QPushButton::clicked, &dialog, &QDialog::accept);


    if (dialog.exec() == QDialog::Accepted) {
        int x = spinBox1->value();
        skew(image,x);
        updateDisplayedImage();
    }


}


void MainStart::on_filter_23_clicked()
{
    hide();
    Contrast_plus(image);
    updateDisplayedImage();
}


void MainStart::on_filter_22_clicked()
{
    hide();
    blur_edges(image);

    updateDisplayedImage();
}


void MainStart::on_filter_6_clicked()
{
    hide();
    rotate(image);

    updateDisplayedImage();
}


void MainStart::on_merge_clicked()
{
    hide();
     merge(image,second_image);
    updateDisplayedImage();
}


void MainStart::on_flipH_clicked()
{
    hide();
    flip_horizontal(image);
    updateDisplayedImage();

}


void MainStart::on_flipV_clicked()
{
    hide();
    flip_vertical(image);
    updateDisplayedImage();
}


void MainStart::on_filter_24_clicked()
{
    hide();
    Contrast_minus(image);
    updateDisplayedImage();
}


void MainStart::on_filter_9_clicked()
{
    hide();
    QDialog dialog(this);
    dialog.setWindowTitle("Crop");
    dialog.setFixedSize(400, 300);

    QLabel * x= new QLabel(" Initial position on X axis:", &dialog);
    x->setGeometry(20, 20, 140, 30);

    QLabel *y = new QLabel(" Initial position on Y axis:", &dialog);
    y->setGeometry(20, 70, 140, 30);

    QLabel *width = new QLabel(" Width:", &dialog);
    width->setGeometry(20, 120, 100, 30);

    QLabel *height = new QLabel(" Height:", &dialog);
    height->setGeometry(20, 170, 100, 30);

    QSpinBox *spinBox1 = new QSpinBox(&dialog);
    spinBox1->setGeometry(180, 20, 100, 30);
    spinBox1->setRange(0, image.width());


    QSpinBox *spinBox2 = new QSpinBox(&dialog);
    spinBox2->setGeometry(180, 70, 100, 30);
    spinBox2->setRange(0, image.height());

    QSpinBox *spinBox3 = new QSpinBox(&dialog);
    spinBox3->setGeometry(180, 120, 100, 30);
    spinBox3->setRange(1, image.width());

    QSpinBox *spinBox4 = new QSpinBox(&dialog);
    spinBox4->setGeometry(180, 170, 100, 30);
    spinBox4->setRange(1, image.height());

    QPushButton *applyButton = new QPushButton("continue", &dialog);
    applyButton->setGeometry(160, 250, 80, 30);

    connect(applyButton, &QPushButton::clicked, &dialog, &QDialog::accept);


      if (dialog.exec() == QDialog::Accepted) {
        int X = spinBox1->value();
        int Y = spinBox2->value();
        int Width = spinBox3->value();
        int Height = spinBox4->value();
        if (X+Width > image.width() ||Y+Height > image.height()) {
            QMessageBox::critical(this, "Error", "Dimensions is not valid ");
            return;
        }
        crop(image,X,Y,Width,Height);
          updateDisplayedImage();
    }


}


void MainStart::on_filter_19_clicked() {
    // Create the main dialog
    hide();
    QDialog mainDialog(this);
    mainDialog.setWindowTitle("Main Dialog");
    mainDialog.setFixedSize(200, 150);

    QPushButton aspectButton("Aspect Mode", &mainDialog);
    QPushButton noAspectButton("No Aspect Mode", &mainDialog);

    QVBoxLayout layout(&mainDialog);
    layout.addWidget(&aspectButton);
    layout.addWidget(&noAspectButton);
    mainDialog.setLayout(&layout);

    // Connect the aspect mode button to open the aspect mode dialog
    // Connect the aspect mode button to open the aspect mode dialog
    connect(&aspectButton, &QPushButton::clicked, [&]() {
        mainDialog.close();
        QDialog aspectModeDialog(this);
        aspectModeDialog.setWindowTitle("Aspect Mode Dialog");
        aspectModeDialog.setFixedSize(200, 150);

        // Create radio buttons for choosing between width and height
        QRadioButton widthRadioButton("Enter Width", &aspectModeDialog);
        QRadioButton heightRadioButton("Enter Height", &aspectModeDialog);

        QVBoxLayout aspectLayout(&aspectModeDialog);
        aspectLayout.addWidget(&widthRadioButton);
        aspectLayout.addWidget(&heightRadioButton);
        aspectModeDialog.setLayout(&aspectLayout);

        // Connect signals for width and height radio buttons
        connect(&widthRadioButton, &QRadioButton::clicked, [&]() {
            aspectModeDialog.close();
            QDialog widthDialog(this);
            widthDialog.setWindowTitle("Enter Width");
            widthDialog.setFixedSize(200, 150);

            QLabel widthLabel("Width:", &widthDialog);
            QSpinBox widthSpinBox(&widthDialog);
            widthSpinBox.setRange(1, 10000);

            QPushButton continueButton("Continue", &widthDialog);

            QVBoxLayout widthLayout(&widthDialog);
            widthLayout.addWidget(&widthLabel);
            widthLayout.addWidget(&widthSpinBox);
            widthLayout.addWidget(&continueButton);
            widthDialog.setLayout(&widthLayout);

            connect(&continueButton, &QPushButton::clicked, [&]() {
                int width = widthSpinBox.value();
                aspect_width(image,width);
                updateDisplayedImage();
                // Process the width value
                widthDialog.accept();
            });

            widthDialog.exec();
        });

        connect(&heightRadioButton, &QRadioButton::clicked, [&]() {
            aspectModeDialog.close();
            QDialog heightDialog(this);
            heightDialog.setWindowTitle("Enter Height");
            heightDialog.setFixedSize(200, 150);

            QLabel heightLabel("Height:", &heightDialog);
            QSpinBox heightSpinBox(&heightDialog);
            heightSpinBox.setRange(1, 10000);

            QPushButton continueButton("Continue", &heightDialog);


            QVBoxLayout heightLayout(&heightDialog);
            heightLayout.addWidget(&heightLabel);
            heightLayout.addWidget(&heightSpinBox);
            heightLayout.addWidget(&continueButton);
            heightDialog.setLayout(&heightLayout);

            connect(&continueButton, &QPushButton::clicked, [&]() {
                int height = heightSpinBox.value();

                // Process the height value
                heightDialog.accept();
                aspect_height(image,height);
                updateDisplayedImage();

            });

            heightDialog.exec();
        });

        aspectModeDialog.exec();
    });


    // Connect the no aspect mode button to open the no aspect mode dialog
    // Connect the no aspect mode button to open the no aspect mode dialog
    connect(&noAspectButton, &QPushButton::clicked, [&]() {
        mainDialog.close();
        QDialog noAspectDialog(this);
        noAspectDialog.setWindowTitle("No Aspect Mode Dialog");
        noAspectDialog.setFixedSize(200, 150);

        QLabel widthLabel("Width:", &noAspectDialog);
        QLabel heightLabel("Height:", &noAspectDialog);
        QSpinBox widthSpinBox(&noAspectDialog);
        QSpinBox heightSpinBox(&noAspectDialog);
        QPushButton continueButton("Continue", &noAspectDialog);
        // Set the range for the width and height spin boxes
        widthSpinBox.setRange(1, 10000);
        heightSpinBox.setRange(1, 10000);

        // Layout for the dialog
        QVBoxLayout noAspectLayout(&noAspectDialog);
        noAspectLayout.addWidget(&widthLabel);
        noAspectLayout.addWidget(&widthSpinBox);
        noAspectLayout.addWidget(&heightLabel);
        noAspectLayout.addWidget(&heightSpinBox);
        noAspectLayout.addWidget(&continueButton); // Add the "Continue" button
        noAspectDialog.setLayout(&noAspectLayout);

        // Connect "Continue" button to a slot
        connect(&continueButton, &QPushButton::clicked, [&]() {
            // Retrieve the width and height values from spin boxes
            int width = widthSpinBox.value();
            int height = heightSpinBox.value();
            no_aspect(image,width,height);
            updateDisplayedImage();

            // Close the dialog
            noAspectDialog.accept();
        });

        noAspectDialog.exec();
    });


    mainDialog.exec();
}





void MainStart::on_AboutUsButtonPage2_2_clicked()
{
    this->hide();
    this->close();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

