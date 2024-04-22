#ifndef ELRAMLY_PAGE_H
#define ELRAMLY_PAGE_H

#include <QDialog>

namespace Ui {
class Mohamed_Elramly_Page;
}

class Mohamed_Elramly_Page : public QDialog
{
    Q_OBJECT

public:
    explicit Mohamed_Elramly_Page(QWidget *parent = nullptr);
    ~Mohamed_Elramly_Page();

private slots:
    void on_AllButton_2_clicked();

    void on_BounsButton_2_clicked();

    void on_ExitButton_2_clicked();

    void on_BackButton_3_clicked();

    void on_OurTeamButton_2_clicked();

    void on_StartButtonPage2_2_clicked();

    void on_AboutUsButtonPage2_2_clicked();

private:
    Ui::Mohamed_Elramly_Page *ui;
};

#endif // ELRAMLY_PAGE_H
