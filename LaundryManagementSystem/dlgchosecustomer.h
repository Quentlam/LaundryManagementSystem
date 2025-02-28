#ifndef DLGCHOSECUSTOMER_H
#define DLGCHOSECUSTOMER_H

#include <QDialog>
#include "customerinfo.h"


namespace Ui {
class dlgChoseCustomer;
}

class dlgChoseCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit dlgChoseCustomer(QWidget *parent = nullptr);
    ~dlgChoseCustomer();
    customerInfo chosedCustomer;


    int exec();
    void reFresh();
    void show();
    void updateChosenCustomerById(customerInfo &customer,QString id);
private slots:
    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

    void on_LeSearch_textChanged(const QString &arg1);

signals:
    void chosedSuccess();


private:
    Ui::dlgChoseCustomer *ui;
};

#endif // DLGCHOSECUSTOMER_H
