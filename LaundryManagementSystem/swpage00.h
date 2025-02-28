#ifndef SWPAGE00_H
#define SWPAGE00_H

#include <QDialog>

namespace Ui {
class swpage00;
}

class swpage00 : public QDialog
{
    Q_OBJECT

public:
    explicit swpage00(QWidget *parent = nullptr);
    ~swpage00();
    int type = 0;
private slots:

    void on_BtnOther_clicked();

    void on_BtnDry_clicked();

    void on_BtnWater_clicked();

    void on_BtnLeather_clicked();

    void on_BtnSingleIroning_clicked();

private:
    Ui::swpage00 *ui;


signals:
    void chosenType();
};

#endif // SWPAGE00_H
