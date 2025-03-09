#ifndef PRINTERSQL_H
#define PRINTERSQL_H

#include "printerinfo.h"
#include "qdebug.h"
#include "qsqlerror.h"
#include <QObject>
#include <QSqlQuery>

class printerSql
{
public:
    printerSql();
    ~printerSql();

    static Scope<printerSql> getInstance()
    {
        if(nullptr == Instance)
        {
            Instance = std::make_shared<printerSql>();
            return Instance;
        }
        else
        {
            return Instance;
        }
    }

public:
    Ref<printerInfo> selectPrinterInfo();
    bool savePrinterInfo(printerInfo printerInfotemp);
    void getError()
    {
        qDebug() << sql->lastError().text();
    }

private:
    QSqlQuery* sql;
    static Scope<printerSql> Instance;

};

#endif // PRINTERSQL_H
