#include "shelfsql.h"
#include <QVariant>

shelfSql* shelfSql::Instance = nullptr;
shelfSql::~shelfSql()
{
    delete  sql;
    delete  Instance;
}

int shelfSql::selectShelfClothesCount()
{
    sql->exec("select ShelfClothesCount from ShelfStatus");
    sql->next();
    int count = sql->value(0).toInt();
    return count;
}

std::unique_ptr<QList<shelfInfo>> shelfSql::selectAllShelves(shelfInfo::shelfSet type)
{
    std::unique_ptr<QList<shelfInfo>> shelfInfoTempList = std::make_unique<QList<shelfInfo>>();
    shelfInfo temp;
    switch (type) {
    case shelfInfo::A:
        sql->exec("select * from ShelfA");
        break;
    case shelfInfo::B:
        sql->exec("select * from ShelfB");
        break;
         }
    while(sql->next())
    {
        temp.ID      = sql->value(0).toString();
        temp.status  = sql->value(1).toString();
        shelfInfoTempList->push_back(temp);
    }
    return shelfInfoTempList;
}

bool shelfSql::setShelfOccupy(QString shelfNumber, shelfInfo::shelfSet type)
{
    switch (type)
    {
    case shelfInfo::A:
        return sql->exec(QString("update ShelfA set ShelfStatus = '已上架' where ShelfID = '%1'; ").arg(shelfNumber));
    case shelfInfo::B:
        return sql->exec(QString("update ShelfB set ShelfStatus = '已上架' where ShelfID = '%1'; ").arg(shelfNumber));
    }

}

bool shelfSql::setShelfOccupy(QString shelfNumber, QString set)
{
    if("A" == set)
    {
        return sql->exec(QString("update ShelfA set ShelfStatus = '已上架' where ShelfID = '%1'; ").arg(shelfNumber));
    }
    else
    {
        return sql->exec(QString("update ShelfB set ShelfStatus = '已上架' where ShelfID = '%1'; ").arg(shelfNumber));
    }
}

bool shelfSql::setShelfNotOccupy(QString shelfNumber, shelfInfo::shelfSet type)
{
    switch (type)
    {
    case shelfInfo::A:
        return sql->exec(QString("update ShelfA set ShelfStatus = '空' where ShelfID = '%1'; ").arg(shelfNumber));
    case shelfInfo::B:
        return sql->exec(QString("update ShelfB set ShelfStatus = '空' where ShelfID = '%1'; ").arg(shelfNumber));
    }

}

bool shelfSql::setShelfNotOccupy(QString shelfNumber, QString set)
{
    if("A" == set)
    {
        return sql->exec(QString("update ShelfA set ShelfStatus = '空' where ShelfID = '%1'; ").arg(shelfNumber));
    }
    else
    {
        return sql->exec(QString("update ShelfB set ShelfStatus = '空' where ShelfID = '%1'; ").arg(shelfNumber));
    }
}



shelfSql::shelfSql():
    sql(new QSqlQuery())
{

}
