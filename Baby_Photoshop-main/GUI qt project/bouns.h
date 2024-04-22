#ifndef BOUNS_H
#define BOUNS_H

#include <QDialog>

namespace Ui {
class Bouns;
}

class Bouns : public QDialog
{
    Q_OBJECT

public:
    explicit Bouns(QWidget *parent = nullptr);
    ~Bouns();

private slots:
    void on_ExitButton_2_clicked();

    void on_BackButton_3_clicked();

    void on_AllButton_2_clicked();

    void on_ElramlyButton_2_clicked();

    void on_OurTeamButton_2_clicked();

    void on_StartButtonPage2_2_clicked();

    void on_AboutUsButtonPage2_2_clicked();

private:
    Ui::Bouns *ui;
};

#endif // BOUNS_H
