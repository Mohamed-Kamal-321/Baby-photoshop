#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include "effects_page.h"
#include "bouns.h"
#include "elramly_page.h"
#include "mainstart.h"
#include "aboutus.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix(":/photos/project photos/1.png");
    ui->label_2->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Effects_Button_clicked()
{

    this->hide();
    Effects_page effectspage;
    effectspage.setModal(true);
    effectspage.exec();

}


void MainWindow::on_ExitButton_clicked()
{
    close();
}


void MainWindow::on_Start_button22_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}


void MainWindow::on_Start_Button_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}





void MainWindow::on_AboutUs_Butoon_clicked()
{
    this->hide();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

