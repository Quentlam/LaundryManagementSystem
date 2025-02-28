#ifndef DLGCUSTOMERRECHARGE_H
#define DLGCUSTOMERRECHARGE_H

#include <QDialog>
#include "customerinfo.h"
#include "dlgchosecustomer.h"
#include "customercost.h"
#include "dlgcustomercostforhavenotpaid.h"
#include "dlgcustomergetclothes.h"
namespace Ui {
class dlgCustomerRecharge;
}

class dlgCustomerRecharge : public QDialog
{
    Q_OBJECT

public:
    dlgCustomerRecharge(QWidget *parent = nullptr);
    dlgCustomerRecharge(QWidget *parent = nullptr,customerInfo currentCustomer = customerInfo());
    ~dlgCustomerRecharge();
    customerInfo currentCustomer;
    dlgChoseCustomer chosenCustomer;
    dlgCustomerCostForHaveNotPaid* dlgPayForNotPay;
    dlgCustomerGetClothes* dlggetClothes;
    customerCost currentCustomerCostOrRecharge;


    int exec();
    void chosenSuccess();
    void updateForPayForNotPaid();


private slots:
    void on_BtnSelectCustomer_clicked();

    void on_BtnRecharge_clicked();

    void on_BtnPayForHaveNotPay_clicked();

    void on_LeRecharge_textChanged(const QString &arg1);

    void on_pushButton_clicked();

signals:
    void rechargeSuccess();

private:
    Ui::dlgCustomerRecharge *ui;
};

#endif // DLGCUSTOMERRECHARGE_H
