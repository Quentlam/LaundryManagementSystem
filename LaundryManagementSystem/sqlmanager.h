#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "clothesql.h"
#include "ordersql.h"
#include "customersql.h"
#include "usersql.h"
#include "shelfsql.h"

#define GET_SQL_POINTER sqlManager::createSqlManager()->getSqlPointer()
#define NUMBER_KEY_EVENT(action)     if(Qt::Key::Key_0 == event->key()\
||Qt::Key::Key_1 == event->key()\
||Qt::Key::Key_2 == event->key()\
||Qt::Key::Key_3 == event->key()\
||Qt::Key::Key_4 == event->key()\
||Qt::Key::Key_5 == event->key()\
||Qt::Key::Key_6 == event->key()\
||Qt::Key::Key_7 == event->key()\
||Qt::Key::Key_8 == event->key()\
||Qt::Key::Key_9 == event->key()\
       )\
{\
   QString text = event->text();\
   action;\
}\


#define CLOTHES_SQL  sqlManager::createClothesSql()
#define ORDER_SQL    sqlManager::createOrderSql()
#define CUSTOMER_SQL sqlManager::createCustomerSql()
#define SHELF_SQL    sqlManager::createShelfSql()
#define USER_SQL     sqlManager::createUserSql()
#define NOT_OWE "未欠缴"
#define OWE "欠缴"
class sqlManager
{
public:
    sqlManager();
    ~sqlManager();
    static Scope<sqlManager> createSqlManager()
    {
        if(nullptr == Instance)
        {
            Instance =  std::make_shared<sqlManager>();
            createClothesSql();
            createOrderSql();
            createCustomerSql();
            createUserSql();
            createShelfSql();
            return Instance;
        }
        else
        {
            return Instance;
        }
    }
    static clotheSql*   createClothesSql();
    static orderSql*    createOrderSql();
    static customerSql* createCustomerSql();
    static userSql*     createUserSql();
    static shelfSql*    createShelfSql();
    QSqlQuery* getSqlPointer()
    {
        return sql;
    }

    QSqlDatabase* getDB()
    {
        return DB;
    }
protected:

private:
    static Scope<sqlManager> Instance;
    QSqlDatabase* DB;
    QSqlQuery* sql;

};


#endif // SQLMANAGER_H
