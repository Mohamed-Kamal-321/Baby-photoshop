#include "our_team.h"
#include "ui_our_team.h"
#include "mainwindow.h"
#include "bouns.h"
#include "elramly_page.h"
#include "effects_page.h"
#include "mainstart.h"
#include "aboutus.h"
our_team::our_team(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::our_team)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix5(":/photos/project photos/9.png");
    ui->label->setPixmap(pix5);

}

our_team::~our_team()
{
    delete ui;
}

void our_team::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}


void our_team::on_ExitButton_2_clicked()
{
    close();
}


void our_team::on_AllButton_2_clicked()
{
    close();
    Effects_page *effectpage = new Effects_page;
    effectpage->show();
}


void our_team::on_ElramlyButton_2_clicked()
{
    this->hide();
    Mohamed_Elramly_Page elramly;
    elramly.setModal(true);
    elramly.exec();
}


void our_team::on_BounsButton_3_clicked()
{
    this->hide();
    Bouns bouns;
    bouns.setModal(true);
    bouns.exec();
}


void our_team::on_StartButtonPage2_2_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}


void our_team::on_AboutUsButtonPage2_2_clicked()
{
    this->hide();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

