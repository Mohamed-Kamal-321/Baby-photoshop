#include<iostream>
using namespace std;
#include "mainwindow.h"
#include "effects_page.h"
#include "elramly_page.h"
#include "bouns.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/photos/project photos/8.png"));

    MainWindow w;
    w.setMaximumSize(1200, 650);
    w.setMinimumSize(1200, 650);

    Effects_page x;
    x.setMaximumSize(1200, 650);
    x.setMinimumSize(1200, 650);

    Mohamed_Elramly_Page y;
    y.setMaximumSize(1200, 650);
    y.setMinimumSize(1200, 650);

    Bouns z;
    z.setMaximumSize(1200, 650);
    z.setMinimumSize(1200, 650);

    w.show();
    return a.exec();
}
