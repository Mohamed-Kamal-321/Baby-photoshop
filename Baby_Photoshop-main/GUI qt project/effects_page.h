#ifndef EFFECTS_PAGE_H
#define EFFECTS_PAGE_H

#include <QDialog>

namespace Ui {
class Effects_page;
}

class Effects_page : public QDialog
{
    Q_OBJECT

public:
    explicit Effects_page(QWidget *parent = nullptr);
    ~Effects_page();

private slots:

    void on_BackButton_3_clicked();

    void on_ExitButton_2_clicked();

    void on_ElramlyButton_2_clicked();

    void on_BounsButton_2_clicked();

    void on_OurTeamButton_2_clicked();

    void on_StartButtonPage2_2_clicked();

    void on_AboutUsButtonPage2_2_clicked();

private:
    Ui::Effects_page *ui;
};

#endif // EFFECTS_PAGE_H
