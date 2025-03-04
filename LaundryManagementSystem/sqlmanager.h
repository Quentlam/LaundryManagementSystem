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

class sqlManager
{
public:
    virtual ~sqlManager();
    static sqlManager* createSqlManager()
    {
        if(nullptr == Instance)
        {
            Instance = new sqlManager();
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
private:
    sqlManager();
    static sqlManager* Instance;
    QSqlDatabase* DB;
    QSqlQuery* sql;

};

#endif // SQLMANAGER_H
