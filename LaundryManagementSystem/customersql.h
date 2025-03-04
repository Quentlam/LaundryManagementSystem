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
            return new customerSql();
        }
        else
        {
            return Instance;
        }
    }
public:
    std::unique_ptr<QList<customerInfo>> selectAllCustomerInfo();
    std::unique_ptr<customerInfo> selectCusotmerById(QString id);
    std::unique_ptr<customerInfo> selectCusotmerByCardId(QString cardID);
    bool deleteCustomerByID(QString id);
    bool addCustomer(customerInfo customerInfoTemp);
    bool updateCustomerById(customerInfo customerInfoTemp,QString id);


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
