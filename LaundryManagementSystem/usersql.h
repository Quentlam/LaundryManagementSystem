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
    userSql();
    static Scope<userSql> Instance;
    ~userSql();
    static Scope<userSql> getInstance()
    {
        if(nullptr == Instance)
        {
            Instance = std::make_shared<userSql>();
            return Instance;
        }
        else
        {
            return Instance;
        }
    }
    Ref<QList<userInfo>> showAllUser();
    Ref<ShopData> showShopData();
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
    QSqlQuery* sql;

};

#endif // USERSQL_H
