#include "customersql.h"
#include <memory>
#include <QVariant>


customerSql* customerSql::Instance = nullptr;

std::unique_ptr<QList<customerInfo>> customerSql::selectAllCustomerInfo()
{
    std::unique_ptr<QList<customerInfo>> customerListTemp = std::make_unique<QList<customerInfo>>();
    customerInfo customerTemp;
    sql->exec("select * from Customer;");
    while(sql->next())//从数据库里把所有的客户查出来
    {
        customerTemp.ID               = sql->value(0).toString();
        customerTemp.Gender           = sql->value(1).toString();
        customerTemp.Name             = sql->value(2).toString();
        customerTemp.Phone            = sql->value(3).toString();
        customerTemp.CardID           = sql->value(4).toString();
        customerTemp.Spend            = sql->value(5).toDouble();
        customerTemp.Count            = sql->value(6).toDouble();
        customerTemp.CardType         = sql->value(7).toString();
        customerTemp.HaveNotPaid      = sql->value(8).toString();
        customerTemp.HaveNotPaidMoney = sql->value(9).toString();
        customerTemp.CardMoney        = sql->value(10).toDouble();
        customerTemp.Address          = sql->value(11).toString();
        customerTemp.Credit           = sql->value(12).toString();
        customerTemp.Notes            = sql->value(13).toString();
        customerListTemp->push_back(customerTemp);
    }
    return customerListTemp;
}

std::unique_ptr<customerInfo> customerSql::selectCusotmerById(QString id)
{
    std::unique_ptr<customerInfo> customerTemp = std::make_unique<customerInfo>();
    sql->exec(QString("select * from Customer where ID = '%1'").arg(id));
    while(sql->next())
    {
    (*customerTemp).ID               = sql->value(0).toString();
    (*customerTemp).Gender           = sql->value(1).toString();
    (*customerTemp).Name             = sql->value(2).toString();
    (*customerTemp).Phone            = sql->value(3).toString();
    (*customerTemp).CardID           = sql->value(4).toString();
    (*customerTemp).Spend            = sql->value(5).toDouble();
    (*customerTemp).Count            = sql->value(6).toDouble();
    (*customerTemp).CardType         = sql->value(7).toString();
    (*customerTemp).HaveNotPaid      = sql->value(8).toString();
    (*customerTemp).HaveNotPaidMoney = sql->value(9).toString();
    (*customerTemp).CardMoney        = sql->value(10).toDouble();
    (*customerTemp).Address          = sql->value(11).toString();
    (*customerTemp).Credit           = sql->value(12).toString();
    (*customerTemp).Notes            = sql->value(13).toString();
    }
    return customerTemp;
}

std::unique_ptr<customerInfo> customerSql::selectCusotmerByCardId(QString cardID)
{
    std::unique_ptr<customerInfo> customerTemp = std::make_unique<customerInfo>();
    sql->exec(QString("select * from Customer where CardID = '%1'").arg(cardID));
    while(sql->next())
    {
    (*customerTemp).ID               = sql->value(0).toString();
    (*customerTemp).Gender           = sql->value(1).toString();
    (*customerTemp).Name             = sql->value(2).toString();
    (*customerTemp).Phone            = sql->value(3).toString();
    (*customerTemp).CardID           = sql->value(4).toString();
    (*customerTemp).Spend            = sql->value(5).toDouble();
    (*customerTemp).Count            = sql->value(6).toDouble();
    (*customerTemp).CardType         = sql->value(7).toString();
    (*customerTemp).HaveNotPaid      = sql->value(8).toString();
    (*customerTemp).HaveNotPaidMoney = sql->value(9).toString();
    (*customerTemp).CardMoney        = sql->value(10).toDouble();
    (*customerTemp).Address          = sql->value(11).toString();
    (*customerTemp).Credit           = sql->value(12).toString();
    (*customerTemp).Notes            = sql->value(13).toString();
    }
    return customerTemp;
}

bool customerSql::deleteCustomerByID(QString id)
{
    return sql->exec(QString("delete from Customer where ID = '%1'").arg(id));
}

bool customerSql::addCustomer(customerInfo customerInfoTemp)
{
    return sql->exec(QString("insert into Customer values('%1','%2','%3','%4','%5',0,0,'%6','%7','%8',%9,'%10','%11','%12');")
                                   .arg(customerInfoTemp.ID).arg(customerInfoTemp.Gender).arg(customerInfoTemp.Name).arg(customerInfoTemp.Phone).arg(customerInfoTemp.CardID).arg(customerInfoTemp.CardType).arg(customerInfoTemp.HaveNotPaid)
                     .arg(customerInfoTemp.HaveNotPaidMoney).arg(customerInfoTemp.CardMoney).arg(customerInfoTemp.Address).arg(customerInfoTemp.Credit).arg(customerInfoTemp.Notes));
}

bool customerSql::updateCustomerById(customerInfo customerInfoTemp,QString id)
{
  return sql->exec(QString("UPDATE Customer SET ID = '%1', Gender = '%2', Name = '%3', Phone = '%4', CardID = '%5', Spend = %6, Count = %7, CardType = '%8', HaveNotPaid = '%9', HaveNotPaidMoney = '%10', CardMoney = %11, Address = '%12', Credit = '%13', Notes = '%14' WHERE ID = '%15';")
                            .arg(customerInfoTemp.ID)
                            .arg(customerInfoTemp.Gender)
                            .arg(customerInfoTemp.Name)
                            .arg(customerInfoTemp.Phone)
                            .arg(customerInfoTemp.CardID)
                            .arg(customerInfoTemp.Spend)
                            .arg(customerInfoTemp.Count)
                            .arg(customerInfoTemp.CardType)
                            .arg(customerInfoTemp.HaveNotPaid)
                            .arg(customerInfoTemp.HaveNotPaidMoney)
                            .arg(customerInfoTemp.CardMoney)
                            .arg(customerInfoTemp.Address)
                            .arg(customerInfoTemp.Credit)
                            .arg(customerInfoTemp.Notes)
                            .arg(id));
}

customerSql::customerSql():
    sql(new QSqlQuery())
{

}
