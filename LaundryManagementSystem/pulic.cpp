#include "pulic.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>


Scope<pulic> pulic::instance     = nullptr;
userInfo* pulic::currentUser    = nullptr;
QString* pulic::currentAddress  = nullptr;
QSqlDatabase* pulic::DB         = nullptr;
bool pulic::login               = false;
int pulic::shelfCount           = 0;


pulic::pulic(QObject *parent) : QObject(parent)
{
    currentUser = new userInfo();
    currentAddress = new QString("UnKnow");
    shelfCount = sqlManager::createShelfSql()->getInstance()->selectShelfClothesCount();//初始化一下这个每个架子放多少个衣服
    DB = sqlManager::createSqlManager()->getDB();
}



