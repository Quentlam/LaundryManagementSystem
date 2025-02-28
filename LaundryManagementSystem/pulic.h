#ifndef PULIC_H
#define PULIC_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "userinfo.h"

class pulic : public QObject
{
    Q_OBJECT
public:
    explicit pulic(QObject *parent = nullptr);


    static pulic* getInstance()
    {
        if(nullptr == instance)
        {
           instance = new pulic();
        }
          return instance;
    }

    QSqlDatabase getDB()
    {
        return DB;
    }

    QSqlQuery* sql;
    static userInfo* currentUser;
    static QString* currentAddress;
    static bool login;

    static int shelfCount;


private:
    static pulic* instance;
    QSqlDatabase DB;



};

#endif // PULIC_H
