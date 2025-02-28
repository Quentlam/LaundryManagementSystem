#ifndef DLGNEWORDER_H
#define DLGNEWORDER_H

#include <QDialog>
#include "orderinfo.h"
#include "dlgselectclothesinfo.h"
#include "customerinfo.h"
#include "dlgchoseshelf.h"
#include "printer.h"
namespace Ui {
class dlgNewOrder;
}

class dlgNewOrder : public QDialog
{
    Q_OBJECT

public:
    dlgNewOrder(QWidget *parent = nullptr,int CustomerType = 0,OrderInfo currentOrder = OrderInfo());//type用来选择哪种客户，并且0代表临时客户，1代表会员客户
    ~dlgNewOrder();
    dlgSelectClothesInfo* dlgSelectClothes;
    OrderInfo currentOrder;
    dlgChoseShelf choseShelf;
    bool orderFinished;


    Printer orderPrinter;
    bool createNewOrder();

    void setShelfNumber();
    void HaveNotPaidSituation(QString money);
private slots:
    void on_BtnCancel_clicked();

    void on_BtnClothesTemp_clicked();




    void on_BtnEnterOrder_clicked();


    void on_BtnChoseShelf_clicked();

signals:
    void CreateNewOrderSuccess();
private:
    Ui::dlgNewOrder *ui;
};

#endif // DLGNEWORDER_H
