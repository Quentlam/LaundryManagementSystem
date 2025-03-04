#ifndef SHELFSQL_H
#define SHELFSQL_H

#include <QObject>
#include <QSqlQuery>
#include "shelfinfo.h"
#include <QSqlError>
#include <QDebug>

class shelfSql
{
public:
    ~shelfSql();
    static shelfSql* getInstance()
    {
        if(nullptr == Instance)
        {
            return new shelfSql();
        }
        else
        {
            return Instance;
        }
    }

public:
    int selectShelfClothesCount();
    std::unique_ptr<QList<shelfInfo>> selectAllShelves(shelfInfo::shelfSet type);
    bool setShelfOccupy(QString shelfNumber,shelfInfo::shelfSet type);
    bool setShelfOccupy(QString shelfNumber,QString set);
    bool setShelfNotOccupy(QString shelfNumber,shelfInfo::shelfSet type);
    bool setShelfNotOccupy(QString shelfNumber,QString set);

    void getError()
    {
        qDebug() << sql->lastError().text();
    }
private:
    shelfSql();
    QSqlQuery* sql;
    static shelfSql* Instance;
};

#endif // SHELFSQL_H
