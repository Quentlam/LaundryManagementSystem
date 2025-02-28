#include "customercost.h"
#include "pulic.h"
#include <QDebug>
#include <QSqlError>

customerCost::customerCost(customerInfo currentCustomer):
    temp(currentCustomer)
{

}

customerCost::~customerCost()
{

}

void customerCost::cardCost(customerInfo currentCustomer,double money,QString OrderID)//客户充值卡消费
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;

    currentCustomer.Count ++;
    currentCustomer.Spend = currentCustomer.Spend + money;
    currentCustomer.CardMoney = currentCustomer.CardMoney - money;//充值卡花了多少钱
    operate.operate = "客户消费";
    //因为创建的时候，当前客户的当前的消费额和消费次数没有受影响，只有订单受影响了，所以后面这里要加上
    auto status = sqlPtr->exec(QString("UPDATE Customer SET ID = '%1',Gender = '%2',Name = '%3',Phone = '%4',CardID = '%5',Spend = %6,Count = %7 ,CardType = '%8',HaveNotPaid = '%9',HaveNotPaidMoney = '%10' ,CardMoney = %11 ,Address = '%12',Credit = '%13',Notes = '%14' where ID = '%15';")
                       .arg(currentCustomer.ID).arg(currentCustomer.Gender).arg(currentCustomer.Name).arg(currentCustomer.Phone).arg(currentCustomer.CardID).arg(currentCustomer.Spend)
                       .arg(currentCustomer.Count).arg(currentCustomer.CardType).arg(currentCustomer.HaveNotPaid).arg(currentCustomer.HaveNotPaidMoney).arg(currentCustomer.CardMoney)
                       .arg(currentCustomer.Address).arg(currentCustomer.Credit).arg(currentCustomer.Notes).arg(currentCustomer.ID));
    if(true == status)
    {
        operate.target = QString("客户编号：%1,客户姓名：%2,客户消费：%3元,客户电话：%4,客户地址：%5,客户卡号：%6,客户卡余额：%7元,客户支付方式：%8,客户欠缴费：%9元,订单流水号：%10,订单费用：%11元")
                .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(money).arg(currentCustomer.Phone)
                .arg(currentCustomer.Address).arg(currentCustomer.CardID).arg(currentCustomer.CardMoney).arg("充值卡支付").arg(currentCustomer.HaveNotPaidMoney)
                .arg(OrderID).arg(money);
        LaundryManagementLogger::record(operate);
    }

    else
    {
        qDebug() << "消费失败！";
        qDebug() << sqlPtr->lastError().text();
    }

}

void customerCost::cardCostHaveNotPaid(customerInfo currentCustomer,double money,QString OrderID)//充值卡缴费
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;

    currentCustomer.Count ++;
    currentCustomer.Spend = currentCustomer.Spend + money;
    currentCustomer.CardMoney = currentCustomer.CardMoney - money;//充值卡花了多少钱，并且此时是一个负数，此时等于要欠缴的钱
    //currentCustomer.CardMoney = -currentCustomer.CardMoney;
    //currentCustomer.HaveNotPaidMoney = QString::number(currentCustomer.HaveNotPaidMoney.toDouble() + currentCustomer.CardMoney);//欠缴的钱要加上
    currentCustomer.CardMoney = 0;
    operate.operate = "客户消费";
    //因为创建的时候，当前客户的当前的消费额和消费次数没有受影响，只有订单受影响了，所以后面这里要加上
    auto status = sqlPtr->exec(QString("UPDATE Customer SET ID = '%1',Gender = '%2',Name = '%3',Phone = '%4',CardID = '%5',Spend = %6,Count = %7 ,CardType = '%8',HaveNotPaid = '%9',HaveNotPaidMoney = '%10' ,CardMoney = %11 ,Address = '%12',Credit = '%13',Notes = '%14' where ID = '%15';")
                       .arg(currentCustomer.ID).arg(currentCustomer.Gender).arg(currentCustomer.Name).arg(currentCustomer.Phone).arg(currentCustomer.CardID).arg(currentCustomer.Spend)
                       .arg(currentCustomer.Count).arg(currentCustomer.CardType).arg(currentCustomer.HaveNotPaid).arg(currentCustomer.HaveNotPaidMoney).arg(currentCustomer.CardMoney)
                       .arg(currentCustomer.Address).arg(currentCustomer.Credit).arg(currentCustomer.Notes).arg(currentCustomer.ID));
    if(true == status)
    {
        operate.target = QString("客户编号：%1,客户姓名：%2,客户消费：%3元,客户电话：%4,客户地址：%5,客户卡号：%6,客户卡余额：%7元,客户支付方式：%8,客户欠缴费：%9元,订单流水号：%10,订单费用：%11元")
                .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(money).arg(currentCustomer.Phone)
                .arg(currentCustomer.Address).arg(currentCustomer.CardID).arg(currentCustomer.CardMoney).arg("充值卡支付").arg(currentCustomer.HaveNotPaidMoney)
                .arg(OrderID).arg(money);
        LaundryManagementLogger::record(operate);
    }

    else
    {
        qDebug() << "消费失败！";
        qDebug() << sqlPtr->lastError().text();
    }



}

void customerCost::ortherCost(customerInfo currentCustomer, double money,QString way,QString OrderID)//客户其他方式消费
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;
    operate.operate = "客户消费";
    currentCustomer.Count ++;
    currentCustomer.Spend = currentCustomer.Spend + money;
    auto status = sqlPtr->exec(QString("UPDATE Customer SET ID = '%1',Gender = '%2',Name = '%3',Phone = '%4',CardID = '%5',Spend = %6,Count = %7 ,CardType = '%8',HaveNotPaid = '%9',HaveNotPaidMoney = '%10' ,CardMoney = %11 ,Address = '%12',Credit = '%13',Notes = '%14' where ID = '%15';")
                       .arg(currentCustomer.ID).arg(currentCustomer.Gender).arg(currentCustomer.Name).arg(currentCustomer.Phone).arg(currentCustomer.CardID).arg(currentCustomer.Spend)
                       .arg(currentCustomer.Count).arg(currentCustomer.CardType).arg(currentCustomer.HaveNotPaid).arg(currentCustomer.HaveNotPaidMoney).arg(currentCustomer.CardMoney)
                       .arg(currentCustomer.Address).arg(currentCustomer.Credit).arg(currentCustomer.Notes).arg(currentCustomer.ID));

    operate.target = QString("客户编号：%1,客户姓名：%2,客户消费：%3元,客户电话：%4,客户地址：%5,客户卡号：%6,客户卡余额：%7元,客户支付方式：%8,客户欠缴费：%9元,订单流水号：%10,订单费用：%11元")
            .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(money).arg(currentCustomer.Phone)
            .arg(currentCustomer.Address).arg(currentCustomer.CardID).arg(currentCustomer.CardMoney).arg(way).arg(currentCustomer.HaveNotPaidMoney)
            .arg(OrderID).arg(money);
    LaundryManagementLogger::record(operate);
}




void customerCost::normalCost(QString Name, QString Phone,QString Payway, double money,QString OrderID)//临时客户消费
{
    operate.operate = "临时客户消费";
    operate.target = QString("临时客户姓名：%1,临时客户消费：%2元,临时客户电话：%3,临时客户支付方式：%4,订单流水号：%5,订单费用：%6元")
            .arg(Name).arg(money).arg(Phone).arg(Payway).arg(OrderID).arg(money);
    LaundryManagementLogger::record(operate);
}




void customerCost::cardRecharge(customerInfo currentCustomer, double money)//客户充值
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;
    currentCustomer.CardMoney = currentCustomer.CardMoney + money;//充值卡冲了多少钱

    operate.operate = "客户充值";
    auto status = sqlPtr->exec(QString("UPDATE Customer SET CardMoney = %1 where ID = '%2';")
                             .arg(currentCustomer.CardMoney).arg(currentCustomer.ID));
    if(true == status)
    {
        operate.target = QString("客户编号：%1,客户姓名：%2,客户充值：%3元,客户电话：%4,客户地址：%5,客户卡号：%6,客户卡余额：%7元")
                .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(money).arg(currentCustomer.Phone)
                .arg(currentCustomer.Address).arg(currentCustomer.CardID).arg(currentCustomer.CardMoney);
        LaundryManagementLogger::record(operate);
    }

    else
    {
        qDebug() << "充值失败！";
        qDebug() << sqlPtr->lastError().text();
    }
}


bool customerCost::customerPayForNotPaid(customerInfo& currentCustomer, double money,QString payWay)//客户缴费
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;
    operate.operate = "客户缴费";
    money = currentCustomer.HaveNotPaidMoney.toDouble() - money;//算一下缴费了多少钱
    currentCustomer.HaveNotPaidMoney = QString::number(money);
    if(0.0 == money)//如果缴清了
    {
        currentCustomer.HaveNotPaid = "未欠缴";
    }
    else
    {
        currentCustomer.HaveNotPaid = "欠缴";
    }

    if("充值卡支付" == payWay)
    {
        currentCustomer.CardMoney -= moneyTemp;//如果是充值卡支付，就减一下
    }
    auto status = sqlPtr->exec(QString("UPDATE Customer SET ID = '%1',Gender = '%2',Name = '%3',Phone = '%4',CardID = '%5',Spend = %6,Count = %7 ,CardType = '%8',HaveNotPaid = '%9',HaveNotPaidMoney = '%10' ,CardMoney = %11 ,Address = '%12',Credit = '%13',Notes = '%14' where ID = '%15';")
                       .arg(currentCustomer.ID).arg(currentCustomer.Gender).arg(currentCustomer.Name).arg(currentCustomer.Phone).arg(currentCustomer.CardID).arg(currentCustomer.Spend)
                       .arg(currentCustomer.Count).arg(currentCustomer.CardType).arg(currentCustomer.HaveNotPaid).arg(currentCustomer.HaveNotPaidMoney).arg(currentCustomer.CardMoney)
                       .arg(currentCustomer.Address).arg(currentCustomer.Credit).arg(currentCustomer.Notes).arg(currentCustomer.ID));

    operate.target = QString("客户编号：%1,客户姓名：%2,客户缴费：%3,客户支付方式：%4,客户剩余未缴费：%5元")
            .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(moneyTemp).arg(payWay).arg(money);
    LaundryManagementLogger::record(operate);
    return status;
}


void customerCost::ortherCostHaveNotPaid(customerInfo currentCustomer,double money,QString way,QString OrderID)//其他付款方式但是欠缴了
{
    auto sqlPtr = pulic::getInstance()->sql;
    moneyTemp = money;
    operate.operate = "客户消费";
    currentCustomer.Count ++;
    currentCustomer.Spend = currentCustomer.Spend + money;
    currentCustomer.HaveNotPaid = "欠缴";
    //这里不用加上欠缴费的原因是，在收衣服的那里已经添加上了，所以这里不用加了
    auto status = sqlPtr->exec(QString("UPDATE Customer SET ID = '%1',Gender = '%2',Name = '%3',Phone = '%4',CardID = '%5',Spend = %6,Count = %7 ,CardType = '%8',HaveNotPaid = '%9',HaveNotPaidMoney = '%10' ,CardMoney = %11 ,Address = '%12',Credit = '%13',Notes = '%14' where ID = '%15';")
                       .arg(currentCustomer.ID).arg(currentCustomer.Gender).arg(currentCustomer.Name).arg(currentCustomer.Phone).arg(currentCustomer.CardID).arg(currentCustomer.Spend)
                       .arg(currentCustomer.Count).arg(currentCustomer.CardType).arg(currentCustomer.HaveNotPaid).arg(currentCustomer.HaveNotPaidMoney).arg(currentCustomer.CardMoney)
                       .arg(currentCustomer.Address).arg(currentCustomer.Credit).arg(currentCustomer.Notes).arg(currentCustomer.ID));

    operate.target = QString("客户编号：%1,客户姓名：%2,客户消费：%3元,客户电话：%4,客户地址：%5,客户卡号：%6,客户卡余额：%7元,客户支付方式：%8,客户欠缴费：%9元,订单流水号：%10,订单费用：%11元")
            .arg(currentCustomer.ID).arg(currentCustomer.Name).arg(money).arg(currentCustomer.Phone)
            .arg(currentCustomer.Address).arg(currentCustomer.CardID).arg(currentCustomer.CardMoney).arg(way).arg(currentCustomer.HaveNotPaidMoney)
            .arg(OrderID).arg(money);
    LaundryManagementLogger::record(operate);
}
