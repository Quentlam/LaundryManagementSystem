#ifndef DLGADDCUSTOMER_H
#define DLGADDCUSTOMER_H

#include <QDialog>
#include "laundrymanagementlogger.h"



namespace Ui {
class dlgAddCustomer;
}

class dlgAddCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAddCustomer(QWidget *parent = nullptr);
    ~dlgAddCustomer();
    Operate addCustomerOperate;
    int exec();

private slots:
    void on_BtnEnter_clicked();
    void on_BtnCancel_clicked();

    void on_RaHaveNotPaid_clicked();

    void on_RaHavePaid_clicked();

private:
    Ui::dlgAddCustomer *ui;


};

#endif // DLGADDCUSTOMER_H
