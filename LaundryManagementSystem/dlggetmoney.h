#ifndef DLGGETMONEY_H
#define DLGGETMONEY_H

#include <QDialog>

namespace Ui {
class dlgGetMoney;
}

class dlgGetMoney : public QDialog
{
    Q_OBJECT

public:
    explicit dlgGetMoney(QWidget *parent = nullptr);
    ~dlgGetMoney();
    QString payWay;
    double Money;


    void NormalCustomerMoneyFunc();
    void VIPCustomerMoneyFunc();
private slots:
    void on_BtnNumTwenty_clicked();

    void on_BtnNumOne_clicked();

    void on_BtnNumTwo_clicked();

    void on_BtnNumFive_clicked();

    void on_BtnNumTen_clicked();

    void on_BtnNumFifty_clicked();

    void on_BtnNumOneH_clicked();

    void on_BtnNumTwoH_clicked();

    void on_BtnEnter_clicked();


    void on_BtnCancel_clicked();

    void on_RaCard_clicked();

    void on_RaWechat_clicked();

    void on_RaTicket_clicked();

    void on_RaCash_clicked();

signals:
    void finshGetMoney();

private:
    Ui::dlgGetMoney *ui;
};

#endif // DLGGETMONEY_H
