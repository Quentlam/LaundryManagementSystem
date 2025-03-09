#include "printersql.h"
#include <memory>

Scope<printerSql> printerSql::Instance = nullptr;


printerSql::~printerSql()
{
    delete sql;
}

std::unique_ptr<printerInfo> printerSql::selectPrinterInfo()
{
    sql->exec(QString("select * from Printer;"));
    Ref<printerInfo> temp = std::make_unique<printerInfo>();
    while(sql->next())
    {
        temp->id           = sql->value(0).toInt();
        temp->printerName  = sql->value(1).toString();
        temp->paperWidth   = sql->value(2).toString();
        temp->paperCount   = sql->value(3).toString();
        temp->Head1        = sql->value(4).toString();
        temp->Head2        = sql->value(5).toString();
        temp->Head3        = sql->value(6).toString();
    }
    return temp;
}

bool printerSql::savePrinterInfo(printerInfo printerInfotemp)
{
    return sql->exec(QString("update Printer set PrinterName = '%1',PaperWidth = '%2',PaperCount = '%3',Head1 = '%4',Head2 = '%5',Head3 = '%6' where PrinterID = 1 ;")
              .arg(printerInfotemp.printerName).arg(printerInfotemp.paperWidth)
              .arg(printerInfotemp.paperCount).arg(printerInfotemp.Head1)
              .arg(printerInfotemp.Head2).arg(printerInfotemp.Head3)
              );
}

printerSql::printerSql():
    sql(new QSqlQuery)
{

}
