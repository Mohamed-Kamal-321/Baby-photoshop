#include "elramly_page.h"
#include "ui_elramly_page.h"
#include "effects_page.h"
#include "bouns.h"
#include "mainwindow.h"
#include "our_team.h"
#include "mainstart.h"
#include "aboutus.h"

Mohamed_Elramly_Page::Mohamed_Elramly_Page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mohamed_Elramly_Page)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix3(":/photos/project photos/6.png");
    ui->label->setPixmap(pix3);
}

Mohamed_Elramly_Page::~Mohamed_Elramly_Page()
{
    delete ui;
}

void Mohamed_Elramly_Page::on_AllButton_2_clicked()
{
    close();
    Effects_page *effectpage = new Effects_page;
    effectpage->show();
}


void Mohamed_Elramly_Page::on_BounsButton_2_clicked()
{
    this->hide();
    Bouns bouns;
    bouns.setModal(true);
    bouns.exec();
}


void Mohamed_Elramly_Page::on_ExitButton_2_clicked()
{
    close();
}


void Mohamed_Elramly_Page::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}


void Mohamed_Elramly_Page::on_OurTeamButton_2_clicked()
{
    this->hide();
    our_team OurTeam;
    OurTeam.setModal(true);
    OurTeam.exec();
}


void Mohamed_Elramly_Page::on_StartButtonPage2_2_clicked()
{
    this->hide();
    Effects_page effectspage;
    effectspage.setModal(true);
    effectspage.exec();
}


void Mohamed_Elramly_Page::on_AboutUsButtonPage2_2_clicked()
{
    this->hide();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

