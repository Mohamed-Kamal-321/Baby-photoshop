#include "effects_page.h"
#include "ui_effects_page.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include "elramly_page.h"
#include "bouns.h"
#include "our_team.h"
#include "mainstart.h"
#include "aboutus.h"


Effects_page::Effects_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Effects_page)
{

    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix2(":/photos/project photos/5.png");
    ui->label->setPixmap(pix2);
}

Effects_page::~Effects_page()
{
    delete ui;
}

void Effects_page::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}


void Effects_page::on_ExitButton_2_clicked()
{
    close();
}


void Effects_page::on_ElramlyButton_2_clicked()
{
    this->hide();
    Mohamed_Elramly_Page elramly;
    elramly.setModal(true);
    elramly.exec();
}


void Effects_page::on_BounsButton_2_clicked()
{
    this->hide();
    Bouns bouns;
    bouns.setModal(true);
    bouns.exec();
}


void Effects_page::on_OurTeamButton_2_clicked()
{
    this->hide();
    our_team OurTeam;
    OurTeam.setModal(true);
    OurTeam.exec();
}


void Effects_page::on_StartButtonPage2_2_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}


void Effects_page::on_AboutUsButtonPage2_2_clicked()
{
    this->hide();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

