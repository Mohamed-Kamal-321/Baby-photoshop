#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "effects_page.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Effects_Button_clicked();
    void on_ExitButton_clicked();


    void on_Start_button22_clicked();

    void on_Start_Button_clicked();

    void on_AboutUs_Butoon_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
