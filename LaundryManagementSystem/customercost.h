#ifndef CUSTOMERCOST_H
#define CUSTOMERCOST_H

#include "customerinfo.h"
#include "laundrymanagementlogger.h"


class customerCost
{
public:
    customerCost(customerInfo currentCustomer);
    ~customerCost();


    customerInfo temp;
    double moneyTemp;
    Operate operate;//记录一下消费操作

    void cardCost(customerInfo currentCustomer,double money,QString OrderID);                                           //会员客户用卡支付
    void ortherCost(customerInfo currentCustomer,double money,QString payway,QString OrderID);                          //会员客户其他支付方式
    void normalCost(QString Name,QString Phone,QString Payway,double money,QString OrderID);                            //临时客户给钱
    void cardRecharge(customerInfo currentCustomer,double money);                                                       //卡充值
    void cardCostHaveNotPaid(customerInfo currentCustomer, double money, QString OrderID);                              //卡给一部分，其他作为欠缴
    bool customerPayForNotPaid(customerInfo& currentCustomer, double money,QString payWay);                             //交缴费
    void ortherCostHaveNotPaid(customerInfo currentCustomer, double money, QString way, QString OrderID);               //其他方式欠缴了
};

#endif // CUSTOMERCOST_H
