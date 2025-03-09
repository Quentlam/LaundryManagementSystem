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
    static Scope<orderSql> Instance;
    orderSql();
    ~orderSql();
    static Scope<orderSql> getInstance()
    {
        if(nullptr == Instance)
        {
            Instance = std::make_shared<orderSql>();
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
    Ref<QList<OrderInfo>> selectAllOrderForOneCustomerByCustomerIdAndDate(QString startDate,QString endDate,QString CustomerId);
    Ref<QList<OrderStatus>> selectAllOrderStatusForOneCustomerByCustomerIdAndDate(QString startDate,QString endDate,QString CustomerId);
    Ref<QList<OrderInfo>> selectAllOrderBetweenDate(QString startDate,QString endDate);
    Ref<QList<OrderStatus>> selectAllOrderStatusBetweenDate(QString startDate,QString endDate);

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
    QSqlQuery* sql;
};

#endif // ORDERSQL_H
