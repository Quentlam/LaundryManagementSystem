#include "pulic.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

#define test
#ifdef test
#define Path "Z:\\study-z\\C++\\QtTest\\LaundryManagementSystem\\LaundryManagementSystem.db"
#endif

#ifdef release
#define Path "Z:\\study-z\\C++\\QtTest\\LaundryManagementSystem\\LaundryManagementSystem.db"
#endif



pulic* pulic::instance = nullptr;
userInfo* pulic::currentUser = nullptr;
QString* pulic::currentAddress = nullptr;
bool pulic::login = false;
int pulic::shelfCount = 0;


pulic::pulic(QObject *parent) : QObject(parent)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    #ifdef test
    DB.setDatabaseName(Path);
    #endif

    QString applicationPath = QCoreApplication::applicationDirPath() + "/data/LaundryManagementSystem.db";
    qDebug() << applicationPath;

    #ifdef release
        DB.setDatabaseName(applicationPath);
    #endif

    if (!DB.open())//判断是不是打开了
        QMessageBox::warning(nullptr, tr("信息"),tr("打不开数据库"));
    else qDebug() << "Success";

    sql = new QSqlQuery(DB);
    currentUser = new userInfo();
    currentAddress = new QString("UnKnow");
    sql->exec("select ShelfClothesCount from ShelfStatus");
    sql->next();
    shelfCount = sql->value(0).toInt();//初始化一下这个每个架子放多少个衣服



}



