#ifndef DLGUPDATECLOTHES_H
#define DLGUPDATECLOTHES_H

#include <QDialog>
#include "clothesinfo.h"
#include "laundrymanagementlogger.h"

namespace Ui {
class dlgUpdateClothes;
}

class dlgUpdateClothes : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUpdateClothes(QWidget *parent = nullptr);
    explicit dlgUpdateClothes(QWidget *parent = nullptr,clothesInfo temp = clothesInfo());
    ~dlgUpdateClothes();
    clothesInfo clothesTemp;
    Operate updateClothesOperate;

private slots:
    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::dlgUpdateClothes *ui;
};

#endif // DLGUPDATECLOTHES_H
