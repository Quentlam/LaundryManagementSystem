﻿#ifndef ORDERINFO_H
#define ORDERINFO_H
#include <QList>
#include <QString>
#include "clothesinfo.h"


class OrderInfo
{
public:
    OrderInfo();
    ~OrderInfo();
    QString orderID;
    QString customerID;
    QString customerName;
    QString customerPhone;
    QString customerCount;
    QString customerSpend;
    QString customerCardID;
    QList<SelectClothesInfo> clothesTemp;
    QString MoneyCount;
    QString Discount;
    QString AfterDiscountMoneyCount;
    QString ClothesCount;
    QString CustomerCardMoney;
    QString InputMoney;
    QString OutputMoney;
    QString PayWay;
    QString HaveNotPaid;
    QString GetClothesDate;
    QString CustomerAddress;
    QString ShelfID;
};

class OrderStatus
{
public:
    OrderStatus();
    ~OrderStatus();
    QString orderID;
    QString orderStatus;
    QString ClothesSendStatus;
    QString customerID;
    QString customerName;
    QString shelfID;
};


#endif // ORDERINFO_H
