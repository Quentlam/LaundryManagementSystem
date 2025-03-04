#ifndef USERSQL_H
#define USERSQL_H

#include <QObject>
#include <QSqlQuery>
#include "userinfo.h"
#include <QSqlError>
#include <QDebug>
#include <shopdata.h>

class userSql
{
public:
    ~userSql();
    static userSql* getInstance()
    {
        if(nullptr == Instance)
        {
            return new userSql();
        }
        else
        {
            return Instance;
        }
    }
    std::unique_ptr<QList<userInfo>> showAllUser();
    std::unique_ptr<ShopData> showShopData();
    bool deleteUserById(QString id);
    bool updateUserById(userInfo& userInfoTemp,QString ID);
    bool selectUserByAccount(QString account);
    bool selectUserByName(QString name);
    bool addUser(userInfo userInfoTemp);
    bool userLogin(QString account,QString password,QString address);
    bool saveShopData(ShopData& shopdata);

    void getError()
    {
        qDebug() << sql->lastError().text();
    }
private:
    userSql();
    QSqlQuery* sql;
    static userSql* Instance;
};

#endif // USERSQL_H
