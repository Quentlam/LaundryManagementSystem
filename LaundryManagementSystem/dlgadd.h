#ifndef DLGADD_H
#define DLGADD_H

#include <QDialog>
#include <QTableWidget>
#include "dlgaddcustomer.h"
#include "dlgaddclothes.h"
#include "dlgadduser.h"
#include "dlgupadateuser.h"
#include "dlgupdateclothes.h"
#include "dlgupdatecustomer.h"
#include "dlgupdateclothesotherattributes.h"
#include "dlgaddclothesotherattributes.h"
#include <memory>


namespace Ui {
class dlgAdd;
}

class dlgAdd : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAdd(QWidget *parent = nullptr);
    ~dlgAdd();
    int choseMode();
    void reFresh(int index);
    void show();
public slots:
    void on_BtnAdd_clicked();

    void on_choseCBox_currentIndexChanged(int index);

private slots:

    void on_BtnreFresh_clicked();

    void on_BtnDelete_clicked();

    void on_BetnUpdate_clicked();

    void on_LeSearch_textChanged(const QString &arg1);

    void onRadioButtonChanged();

    void on_CBWashWay_currentIndexChanged(int index);

private:
    Ui::dlgAdd *ui;
    int currentMode;
    dlgAddCustomer mDlgAddCustomer;
    dlgAddClothes mDlgAddClothes;
    dlgAddUser mDlgAddUser;
    dlgUpadateUser* mDlgUpdaterUser;
    dlgUpdateClothes* mDlgUpdateClothes;
    dlgUpdateCustomer* mDlgUpdateCustomer;
    Operate deleteOperate;
    dlgUpdateClothesOtherAttributes* dlgUC;
    dlgAddClothesOtherAttributes* dlgAC;


    clothesInfo clothesTemp;


};

#endif // DLGADD_H
