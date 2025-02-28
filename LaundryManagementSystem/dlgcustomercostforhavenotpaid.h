#ifndef DLGCUSTOMERCOSTFORHAVENOTPAID_H
#define DLGCUSTOMERCOSTFORHAVENOTPAID_H

#include <QDialog>
#include "customerinfo.h"
#include "customercost.h"


namespace Ui {
class dlgCustomerCostForHaveNotPaid;
}

class dlgCustomerCostForHaveNotPaid : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCustomerCostForHaveNotPaid(QWidget *parent = nullptr,customerInfo customerTemp = customerInfo());
    ~dlgCustomerCostForHaveNotPaid();

private slots:
    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

    void on_RaCard_clicked(bool checked);

    void on_RaWechat_clicked(bool checked);

    void on_RaTicket_clicked(bool checked);


    void on_RaCash_clicked(bool checked);


public:
        customerInfo customerTemp;

private:
    Ui::dlgCustomerCostForHaveNotPaid *ui;

    customerCost* mCustomerCost;
    QString PayWay;

signals:
    void PayForNotPaidSuccess();


};

#endif // DLGCUSTOMERCOSTFORHAVENOTPAID_H
