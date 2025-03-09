#ifndef DLGCUSTOMERPAYWHENGETCLO_H
#define DLGCUSTOMERPAYWHENGETCLO_H

#include <QDialog>
#include "customerinfo.h"
namespace Ui {
class dlgCustomerPayWhenGetClo;
}

class dlgCustomerPayWhenGetClo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCustomerPayWhenGetClo(QWidget *parent,customerInfo customer = customerInfo(),QString money = "0");
    customerInfo currentCustomer;
    ~dlgCustomerPayWhenGetClo();
    QString thisOrderNotPaidMoney;
private slots:
    void on_BtnEnter_clicked();

    void on_BtnNumOne_clicked();

    void on_BtnNumTwo_clicked();

    void on_BtnNumFive_clicked();

    void on_BtnNumTen_clicked();

    void on_BtnNumTwenty_clicked();

    void on_BtnNumFifty_clicked();

    void on_BtnNumOneH_clicked();

    void on_BtnNumTwoH_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::dlgCustomerPayWhenGetClo *ui;
};

#endif // DLGCUSTOMERPAYWHENGETCLO_H
