#ifndef CUSTOMERSQL_H
#define CUSTOMERSQL_H

#include <QObject>
#include <QSqlQuery>
#include "customerinfo.h"
#include <QSqlError>
#include <QDebug>


class customerSql
{
public:
    static customerSql* getInstance()
    {
        if(nullptr == Instance)
        {
            Instance =  new customerSql();
            return Instance;
        }
        else
        {
            return Instance;
        }
    }
public:
    Ref<QList<customerInfo>> selectAllCustomerInfo();
    Ref<customerInfo> selectCusotmerById(QString id);
    Ref<customerInfo> selectCusotmerByCardId(QString cardID);
    Ref<customerInfo> selectCusotmerByOrderId(QString OrderID);

    bool deleteCustomerByID(QString id);
    bool addCustomer(customerInfo customerInfoTemp);
    bool updateCustomerById(customerInfo customerInfoTemp,QString id);
    double selectCustomerHaveNotPaidById(QString id);

    void getError()
    {
        qDebug() << sql->lastError().text();
    }
private:
    customerSql();
    QSqlQuery* sql;
    static customerSql* Instance;
};

#endif // CUSTOMERSQL_H
