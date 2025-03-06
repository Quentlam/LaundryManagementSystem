#ifndef ORDERSQL_H
#define ORDERSQL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "orderinfo.h"
#define CLOTHES_NOT_SEND             "未发出"
#define CLOTHES_HAVE_BEEN_SEND       "已发出"
#define ORDER_FINISHED_STATUS        "已完成"
#define ORDER_NOT_FINISHED_STATUS    "未完成"




class orderSql
{
public:
    ~orderSql();
    static orderSql* getInstance()
    {
        if(nullptr == Instance)
        {
            Instance = new orderSql();
            return Instance;
        }
        else
        {
            return Instance;
        }

    }
public:
    Ref<OrderStatus> selectOrderStatusByOrderID(QString OrderID);
    Ref<QList<OrderInfo>> selectAllOrder();
    Ref<QList<OrderStatus>> selectAllOrderStatus();
    Ref<QString> getCustomerHaveNotPayMoneyForTheOrderByOrderId(QString OrderId);
    bool createNewOrder(OrderInfo& orderInfoTemp,OrderClothesAttributeMessage& clothesInfoTempList);
    bool createNewOrderStatus(OrderInfo orderStatusTemp);
    bool updateCurrentOrderID(QString OrderID);
    bool updateOrderStatusByOrderId(QString OrderId, QString status);
    bool updateClothesStatusByOrderId(QString OrderId,QString status);
    bool clothesHaveBeenSendOut(QString OrderId);
    void getError()
    {
        qDebug() << sql->lastError().text();
    }



    double selectOrderAfterDiscountCountMoneyByOrderId(QString id);
    bool judegOrderCustomerHaveNotPaidByOrderId(QString id);
private:
    orderSql();
    QSqlQuery* sql;
    static orderSql* Instance;
};

#endif // ORDERSQL_H
