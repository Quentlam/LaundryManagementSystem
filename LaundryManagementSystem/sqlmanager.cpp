#include "sqlmanager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>

#define test
#ifdef test
#define Path "Z:\\study-z\\C++\\QtTest\\LaundryManagementSystem\\LaundryManagementSystem.db"
#endif


sqlManager* sqlManager::Instance = nullptr;
sqlManager::sqlManager():
    DB(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    sql(new QSqlQuery())
{
    #ifdef test
    DB->setDatabaseName(Path);
    #endif

    QString applicationPath = QCoreApplication::applicationDirPath() + "/data/LaundryManagementSystem.db";
    qDebug() << applicationPath;

    #ifdef release
        DB.setDatabaseName(applicationPath);
    #endif

    if (!DB->open())//判断是不是打开了
        QMessageBox::warning(nullptr,"信息","打不开数据库");
    else qDebug() << "Success";
}



sqlManager::~sqlManager()
{
    delete  sql;
    delete  Instance;
}

clotheSql *sqlManager::createClothesSql()
{
    return clotheSql::getInstance();
}

orderSql *sqlManager::createOrderSql()
{
    return orderSql::getInstance();
}

customerSql *sqlManager::createCustomerSql()
{
    return customerSql::getInstance();
}

userSql *sqlManager::createUserSql()
{
    return userSql::getInstance();
}

shelfSql *sqlManager::createShelfSql()
{
    return shelfSql::getInstance();
}

