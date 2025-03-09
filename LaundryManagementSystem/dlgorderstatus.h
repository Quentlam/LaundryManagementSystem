#ifndef DLGORDERSTATUS_H
#define DLGORDERSTATUS_H

#include <QDialog>
#include "dlgchosecustomer.h"
#include "orderinfo.h"
namespace Ui {
class dlgOrderStatus;
}

class dlgOrderStatus : public QDialog
{
    Q_OBJECT

public:
    explicit dlgOrderStatus(QWidget *parent = nullptr);
    ~dlgOrderStatus();
    bool selectCustomer;
    dlgChoseCustomer dlgChoseCus;
    void reFresh();
    QString currentOrderID;
private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_LeSearch_textChanged(const QString &arg1);

    void on_RaDateSearch_clicked();

    void on_BtnOrderNotFinished_clicked();

    void on_BtnClothesNotBeSent_clicked();

    void on_BtnOrderFinished_clicked();

    void on_BtnClothesSent_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_BtnDateSearch_clicked();

    void on_BtnChoseCustomer_clicked();

    void on_BtnCancel_clicked();

    void on_BtnSelectAll_clicked();

private:
    Ui::dlgOrderStatus *ui;
};

#endif // DLGORDERSTATUS_H
