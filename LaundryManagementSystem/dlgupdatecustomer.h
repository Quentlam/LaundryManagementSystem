#ifndef DLGUPDATECUSTOMER_H
#define DLGUPDATECUSTOMER_H

#include <QDialog>
#include "customerinfo.h"
#include "laundrymanagementlogger.h"



namespace Ui {
class dlgUpdateCustomer;
}

class dlgUpdateCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUpdateCustomer(QWidget *parent = nullptr);
    explicit dlgUpdateCustomer(QWidget *parent = nullptr,customerInfo temp = customerInfo());
    ~dlgUpdateCustomer();
    customerInfo customerTemp;
    Operate updateCustomerOperate;

private slots:
    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::dlgUpdateCustomer *ui;
};

#endif // DLGUPDATECUSTOMER_H
