#ifndef OUR_TEAM_H
#define OUR_TEAM_H

#include <QDialog>

namespace Ui {
class our_team;
}

class our_team : public QDialog
{
    Q_OBJECT

public:
    explicit our_team(QWidget *parent = nullptr);
    ~our_team();

private slots:
    void on_BackButton_3_clicked();

    void on_ExitButton_2_clicked();

    void on_AllButton_2_clicked();

    void on_ElramlyButton_2_clicked();

    void on_BounsButton_3_clicked();

    void on_StartButtonPage2_2_clicked();

    void on_AboutUsButtonPage2_2_clicked();

private:
    Ui::our_team *ui;
};

#endif // OUR_TEAM_H
