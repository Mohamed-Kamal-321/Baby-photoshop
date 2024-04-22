#include "aboutus.h"
#include "ui_aboutus.h"
#include "effects_page.h"
#include "bouns.h"
#include "mainwindow.h"
#include "our_team.h"
#include "mainstart.h"


aboutUs::aboutUs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutUs)
{
    ui->setupUi(this);
    setWindowTitle("Baby Photoshop");
    QPixmap pix2(":/photos/project photos/11.png");
    ui->label->setPixmap(pix2);
}

aboutUs::~aboutUs()
{
    delete ui;
}

void aboutUs::on_BackButton_3_clicked()
{
    close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}


void aboutUs::on_ExitButton_2_clicked()
{
    close();
}


void aboutUs::on_StartButtonPage2_2_clicked()
{
    this->hide();
    MainStart mainstart;
    mainstart.setModal(true);
    mainstart.exec();
}


void aboutUs::on_Effects_page_clicked()
{
    this->hide();
    Effects_page effectspage;
    effectspage.setModal(true);
    effectspage.exec();

}

