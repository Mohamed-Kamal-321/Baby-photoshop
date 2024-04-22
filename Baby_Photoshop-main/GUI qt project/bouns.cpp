#include "mainstart.h"
#include "bouns.h"
#include "ui_bouns.h"
#include "effects_page.h"
#include "mainwindow.h"
#include "elramly_page.h"
#include "our_team.h"
#include "aboutus.h"

Bouns::Bouns(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Bouns)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix4(":/photos/project photos/7.png");
    ui->label->setPixmap(pix4);
}

Bouns::~Bouns()
{
    delete ui;
}

void Bouns::on_ExitButton_2_clicked()
{
    close();
}


void Bouns::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}


void Bouns::on_AllButton_2_clicked()
{
    close();
    Effects_page *effectpage = new Effects_page;
    effectpage->show();
}


void Bouns::on_ElramlyButton_2_clicked()
{
    this->hide();
    Mohamed_Elramly_Page elramly;
    elramly.setModal(true);
    elramly.exec();
}


void Bouns::on_OurTeamButton_2_clicked()
{
    this->hide();
    our_team OurTeam;
    OurTeam.setModal(true);
    OurTeam.exec();
}


void Bouns::on_StartButtonPage2_2_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}


void Bouns::on_AboutUsButtonPage2_2_clicked()
{
    this->hide();
    aboutUs about;
    about.setModal(true);
    about.exec();
}

