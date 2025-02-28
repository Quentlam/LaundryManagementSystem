#ifndef DLGADDCLOTHES_H
#define DLGADDCLOTHES_H

#include <QDialog>
#include "laundrymanagementlogger.h"

namespace Ui {
class dlgAddClothes;
}

class dlgAddClothes : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAddClothes(QWidget *parent = nullptr);
    ~dlgAddClothes();
    Operate addClothesOperate;

    int exec();
private slots:
    void on_BtnEnter_clicked();
    void on_BtnCancel_clicked();

private:
    Ui::dlgAddClothes *ui;
};

#endif // DLGADDCLOTHES_H
