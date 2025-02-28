#ifndef DLGGETCLOTHES_H
#define DLGGETCLOTHES_H

#include <QDialog>
#include <QTableWidget>
#include "dlggetmoney.h"
#include "swpage00.h"
#include "stselectclothestypeandprice.h"
#include "stselectclothes04.h"
#include "stselectclothes03.h"
#include "stselectclothes02.h"
#include "stselectclothes01.h"
#include "stselectclothes00.h"
#include "dlgchosecustomer.h"
#include "ordernumbergenerator.h"
#include "dlgdiscount.h"
#include "orderinfo.h"
#include "dlgcustomerrecharge.h"
#include "dlgneworder.h"
#include "clothesinfo.h"
#include "customercost.h"



namespace Ui {
class dlgGetClothes;
}

class dlgGetClothes : public QDialog
{
    Q_OBJECT
public:
    bool selectCustomer;//看看有没有选择客户
    bool discount;//填写收入前，要先填写折扣
    bool selectClothes;//每次进来前都要检查一下现在的订单是不是有衣服的暂存
public:
    explicit dlgGetClothes(QWidget *parent = nullptr);
    ~dlgGetClothes();

    void getMoneyFunc();
    void chosedCustomerInfoFunc();
    void putChosenMessageIntoTable00();
    void putChosenMessageIntoTable01();
    void putChosenMessageIntoTable02();
    void putChosenMessageIntoTable03();
    void putChosenMessageIntoTable04();
    void putChosenTypeIntoTable();
    void putDiscountIntoTable();
    void putChosenTypePage();
    void show();
    int  CalClothesMoney();
    int  CalClothesCount();
    void reFresh();
    void calFinalMoney();
    void createNewOrderSuccess();
    void rechargeSuccessFuc();
    void setLineFocus();
private slots:
    void on_BtnCancel_clicked();

    void on_BtnGetMoney_clicked();

    void on_BtnChoseCustomer_clicked();

    void on_BtnCustomerTemp_clicked();

    void on_TWClothes_cellClicked(int row, int column);

    void on_BtnEnter_clicked();

    void on_TWClothes_cellChanged(int row, int column);

    void on_TWCal_cellChanged(int row, int column);

    void on_TWMoney_cellChanged(int row, int column);

    void on_TWCal_cellClicked(int row, int column);

private:
    dlgGetMoney dlgGetMon;
    dlgChoseCustomer dlgChoseCus;
    dlgCustomerRecharge* customerReCharge;
    dlgNewOrder* dlgEnterOrder;
    SelectClothesInfo selectClothesTemp;
    customerInfo customerTemp;//暂时把客户给存下来，不然可能点太多次确定，会影响到dlgChoseCus
    double money;//衣服总价格
    double afterDiscountMoney;
    QString payWay;//支付方式
    double input;//收银
    double output;//找零
    int ClothesCount;
    customerCost currentCustomerCost;

    Ui::dlgGetClothes *ui;





    OrderNumberGenerator orderNumberGenrator;//产生流水号
    dlgDiscount dlgdiscount;//点击折扣率出现折扣率选择
    swpage00 clothesSelectPage00;//SW的第0页，也就是选择界面
    STSelectClothesTypeAndPrice Selectclothes;//正式选择衣服
    STSelectClothes04 selectPage04;//选衣服的第4页，洗后效果
    STSelectClothes03 selectPage03;//选衣服的第3页，特殊处理
    STSelectClothes02 selectPage02;//选衣服的第2页，衣服品牌
    STSelectClothes01 selectPage01;//选衣服的第1页，衣服瑕疵
    STSelectClothes00 selectPage00;//选衣服的第0页，衣服颜色



    OrderInfo currentOrder;//现在的订单

signals:
    void backToMainWindow();
    void backToGetMoney();
};

#endif // DLGGETCLOTHES_H
