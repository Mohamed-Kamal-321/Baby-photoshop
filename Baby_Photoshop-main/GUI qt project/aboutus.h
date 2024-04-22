#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QDialog>

namespace Ui {
class aboutUs;
}

class aboutUs : public QDialog
{
    Q_OBJECT

public:
    explicit aboutUs(QWidget *parent = nullptr);
    ~aboutUs();

private slots:
    void on_BackButton_3_clicked();

    void on_ExitButton_2_clicked();

    void on_StartButtonPage2_2_clicked();

    void on_Effects_page_clicked();

private:
    Ui::aboutUs *ui;
};

#endif // ABOUTUS_H
