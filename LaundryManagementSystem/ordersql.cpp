#include "ordersql.h"
#include <QMessageBox>
#include "pulic.h"

Scope<orderSql> orderSql::Instance = nullptr;



orderSql::~orderSql()
{
    delete  sql;
}

Ref<OrderStatus> orderSql::selectOrderStatusByOrderID(QString OrderID)
{
    Ref<OrderStatus> orderStatusTemp = std::make_unique<OrderStatus>();
    sql->exec(QString("select * from OrderStatus where OrderID = '%1'").arg(OrderID));
    while(sql->next())
    {
       (*orderStatusTemp).orderID           = sql->value(0).toString();
       (*orderStatusTemp).orderStatus       = sql->value(1).toString();
       (*orderStatusTemp).ClothesSendStatus = sql->value(2).toString();
       (*orderStatusTemp).customerID        = sql->value(3).toString();
       (*orderStatusTemp).customerName      = sql->value(4).toString();
       (*orderStatusTemp).shelfID           = sql->value(5).toString();
    }
    return orderStatusTemp;
}

Ref<QList<OrderInfo> > orderSql::selectAllOrder()
{
    Ref<QList<OrderInfo>> orderInfoTempList = std::make_unique<QList<OrderInfo>>();
    sql->exec("select * from OrderLog");
    SelectClothesInfo temp;
    OrderInfo orderTemp;
    while(sql->next())
    {
        orderTemp.orderID                           = sql->value(0).toString();
        orderTemp.customerID                        = sql->value(1).toString();
        orderTemp.customerName                      = sql->value(2).toString();
        orderTemp.customerPhone                     = sql->value(3).toString();
        orderTemp.customerCount                     = sql->value(4).toString();
        orderTemp.customerSpend                     = sql->value(5).toString();
        orderTemp.customerCardID                    = sql->value(6).toString();
        temp.Name                                   = sql->value(7).toString();
        temp.Color                                  = sql->value(8).toString();
        temp.Defect                                 = sql->value(9).toString();
        temp.Brand                                  = sql->value(10).toString();
        temp.Treament                               = sql->value(11).toString();
        temp.Effect                                 = sql->value(12).toString();
        temp.Price                                  = sql->value(13).toString();
        orderTemp.clothesTemp.push_back(temp);
        orderTemp.MoneyCount                        = sql->value(14).toString();
        orderTemp.Discount                          = sql->value(15).toString();
        orderTemp.AfterDiscountMoneyCount           = sql->value(16).toString();
        orderTemp.ClothesCount                      = sql->value(17).toString();
        orderTemp.CustomerCardMoney                 = sql->value(18).toString();
        orderTemp.InputMoney                        = sql->value(19).toString();
        orderTemp.OutputMoney                       = sql->value(20).toString();
        orderTemp.PayWay                            = sql->value(21).toString();
        orderTemp.HaveNotPaid                       = sql->value(22).toString();
        orderTemp.GetClothesDate                    = sql->value(23).toString();
        orderTemp.CustomerAddress                   = sql->value(24).toString();
        orderTemp.ShelfID                           = sql->value(25).toString();
        orderTemp.thisOrderNotPaid                  = sql->value(26).toString();
        orderTemp.customerCardMoneyBeforePay        = sql->value(27).toString();
        orderTemp.OrderCreateDate                   = sql->value(28).toString();
        orderInfoTempList->push_back(orderTemp);
    }
    return orderInfoTempList;

}

Ref<QList<OrderStatus>> orderSql::selectAllOrderStatus()
{
    Ref<QList<OrderStatus>> orderStatusTempList = std::make_unique<QList<OrderStatus>>();
    OrderStatus temp;
    sql->exec("select * from OrderStatus");
    while(sql->next())
    {
        temp.orderID                = sql->value(0).toString();
        temp.orderStatus            = sql->value(1).toString();
        temp.ClothesSendStatus      = sql->value(2).toString();
        temp.customerID             = sql->value(3).toString();
        temp.customerName           = sql->value(4).toString();
        temp.shelfID                = sql->value(5).toString();
        orderStatusTempList->push_back(temp);
    }
    return orderStatusTempList;
}

std::unique_ptr<QList<OrderInfo> > orderSql::selectAllOrderForOneCustomerByCustomerIdAndDate(QString startDate, QString endDate, QString CustomerId)
{
    Ref<QList<OrderInfo>> orderInfoTempList = std::make_unique<QList<OrderInfo>>();
    sql->exec(QString("select * from OrderLog where OrderCreateDate BETWEEN '%1' AND '%2' AND CustomerID = '%3';").arg(startDate).arg(endDate).arg(CustomerId));
    SelectClothesInfo temp;
    OrderInfo orderTemp;
    while(sql->next())
    {
        orderTemp.orderID                           = sql->value(0).toString();
        orderTemp.customerID                        = sql->value(1).toString();
        orderTemp.customerName                      = sql->value(2).toString();
        orderTemp.customerPhone                     = sql->value(3).toString();
        orderTemp.customerCount                     = sql->value(4).toString();
        orderTemp.customerSpend                     = sql->value(5).toString();
        orderTemp.customerCardID                    = sql->value(6).toString();
        temp.Name                                   = sql->value(7).toString();
        temp.Color                                  = sql->value(8).toString();
        temp.Defect                                 = sql->value(9).toString();
        temp.Brand                                  = sql->value(10).toString();
        temp.Treament                               = sql->value(11).toString();
        temp.Effect                                 = sql->value(12).toString();
        temp.Price                                  = sql->value(13).toString();
        orderTemp.clothesTemp.push_back(temp);
        orderTemp.MoneyCount                        = sql->value(14).toString();
        orderTemp.Discount                          = sql->value(15).toString();
        orderTemp.AfterDiscountMoneyCount           = sql->value(16).toString();
        orderTemp.ClothesCount                      = sql->value(17).toString();
        orderTemp.CustomerCardMoney                 = sql->value(18).toString();
        orderTemp.InputMoney                        = sql->value(19).toString();
        orderTemp.OutputMoney                       = sql->value(20).toString();
        orderTemp.PayWay                            = sql->value(21).toString();
        orderTemp.HaveNotPaid                       = sql->value(22).toString();
        orderTemp.GetClothesDate                    = sql->value(23).toString();
        orderTemp.CustomerAddress                   = sql->value(24).toString();
        orderTemp.ShelfID                           = sql->value(25).toString();
        orderTemp.thisOrderNotPaid                  = sql->value(26).toString();
        orderTemp.customerCardMoneyBeforePay        = sql->value(27).toString();
        orderTemp.OrderCreateDate                   = sql->value(28).toString();
        orderInfoTempList->push_back(orderTemp);
    }
    return orderInfoTempList;
}

std::unique_ptr<QList<OrderStatus> > orderSql::selectAllOrderStatusForOneCustomerByCustomerIdAndDate(QString startDate, QString endDate, QString CustomerId)
{
    Ref<QList<OrderStatus>> orderStatusTempList = std::make_unique<QList<OrderStatus>>();
    OrderStatus temp;
    sql->exec(QString("SELECT * FROM OrderStatus INNER JOIN OrderLog  ON OrderLog.OrderID = OrderStatus.OrderID WHERE OrderLog.OrderCreateDate BETWEEN '%1' AND '%2' AND OrderLog.CustomerID = '%3';").arg(startDate).arg(endDate).arg(CustomerId));
    while(sql->next())
    {
        temp.orderID                = sql->value(0).toString();
        temp.orderStatus            = sql->value(1).toString();
        temp.ClothesSendStatus      = sql->value(2).toString();
        temp.customerID             = sql->value(3).toString();
        temp.customerName           = sql->value(4).toString();
        temp.shelfID                = sql->value(5).toString();
        orderStatusTempList->push_back(temp);
    }
    return orderStatusTempList;
}


std::unique_ptr<QList<OrderInfo> > orderSql::selectAllOrderBetweenDate(QString startDate, QString endDate)
{
    Ref<QList<OrderInfo>> orderInfoTempList = std::make_unique<QList<OrderInfo>>();
    sql->exec(QString("select * from OrderLog where OrderCreateDate BETWEEN '%1' AND '%2';").arg(startDate).arg(endDate));
    SelectClothesInfo temp;
    OrderInfo orderTemp;
    while(sql->next())
    {
        orderTemp.orderID                           = sql->value(0).toString();
        orderTemp.customerID                        = sql->value(1).toString();
        orderTemp.customerName                      = sql->value(2).toString();
        orderTemp.customerPhone                     = sql->value(3).toString();
        orderTemp.customerCount                     = sql->value(4).toString();
        orderTemp.customerSpend                     = sql->value(5).toString();
        orderTemp.customerCardID                    = sql->value(6).toString();
        temp.Name                                   = sql->value(7).toString();
        temp.Color                                  = sql->value(8).toString();
        temp.Defect                                 = sql->value(9).toString();
        temp.Brand                                  = sql->value(10).toString();
        temp.Treament                               = sql->value(11).toString();
        temp.Effect                                 = sql->value(12).toString();
        temp.Price                                  = sql->value(13).toString();
        orderTemp.clothesTemp.push_back(temp);
        orderTemp.MoneyCount                        = sql->value(14).toString();
        orderTemp.Discount                          = sql->value(15).toString();
        orderTemp.AfterDiscountMoneyCount           = sql->value(16).toString();
        orderTemp.ClothesCount                      = sql->value(17).toString();
        orderTemp.CustomerCardMoney                 = sql->value(18).toString();
        orderTemp.InputMoney                        = sql->value(19).toString();
        orderTemp.OutputMoney                       = sql->value(20).toString();
        orderTemp.PayWay                            = sql->value(21).toString();
        orderTemp.HaveNotPaid                       = sql->value(22).toString();
        orderTemp.GetClothesDate                    = sql->value(23).toString();
        orderTemp.CustomerAddress                   = sql->value(24).toString();
        orderTemp.ShelfID                           = sql->value(25).toString();
        orderTemp.thisOrderNotPaid                  = sql->value(26).toString();
        orderTemp.customerCardMoneyBeforePay        = sql->value(27).toString();
        orderTemp.OrderCreateDate                   = sql->value(28).toString();
        orderInfoTempList->push_back(orderTemp);
    }
    return orderInfoTempList;
}

std::unique_ptr<QList<OrderStatus> > orderSql::selectAllOrderStatusBetweenDate(QString startDate, QString endDate)
{
    Ref<QList<OrderStatus>> orderStatusTempList = std::make_unique<QList<OrderStatus>>();
    OrderStatus temp;
    sql->exec(QString("SELECT * FROM OrderStatus INNER JOIN OrderLog  ON OrderLog.OrderID = OrderStatus.OrderID WHERE OrderLog.OrderCreateDate BETWEEN '%1' AND '%2';").arg(startDate).arg(endDate));
    while(sql->next())
    {
        temp.orderID                = sql->value(0).toString();
        temp.orderStatus            = sql->value(1).toString();
        temp.ClothesSendStatus      = sql->value(2).toString();
        temp.customerID             = sql->value(3).toString();
        temp.customerName           = sql->value(4).toString();
        temp.shelfID                = sql->value(5).toString();
        orderStatusTempList->push_back(temp);
    }
    return orderStatusTempList;
}

Ref<QString> orderSql::getCustomerHaveNotPayMoneyForTheOrderByOrderId(QString OrderId)
{
    sql->exec(QString("select ThisOrderNotPaid from OrderLog where OrderID = '%1'").arg(OrderId));
    sql->next();
    QString money = sql->value(0).toString();
    Ref<QString>moneyTemp = std::make_unique<QString>(money.remove(0,5));
    return moneyTemp;
}

double orderSql::selectOrderAfterDiscountCountMoneyByOrderId(QString id)
{
    sql->exec(QString("select AfterDiscountMoneyCount from OrderLog where OrderID = '%1'").arg(id));
    sql->next();
    return sql->value(0).toDouble();
}


bool orderSql::judegOrderCustomerHaveNotPaidByOrderId(QString id)
{
    sql->exec(QString("select ThisOrderNotPaid from OrderLog where OrderID = '%1'").arg(id));
    sql->next();
    QString value = sql->value(0).toString();
    if(value.contains("欠缴"))
    return true;
    else return false;
}

bool orderSql::createNewOrder(OrderInfo &orderInfoTemp,OrderClothesAttributeMessage& orderClothesAttributeMessageTempList)
{
    return sql->exec(QString("insert into OrderLog values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28','%29');")
                 .arg(orderInfoTemp.orderID).arg(orderInfoTemp.customerID).arg(orderInfoTemp.customerName).arg(orderInfoTemp.customerPhone)
                 .arg(orderInfoTemp.customerCount).arg(orderInfoTemp.customerSpend).arg(orderInfoTemp.customerCardID).arg(orderClothesAttributeMessageTempList.ClothesNameMessage)
                 .arg(orderClothesAttributeMessageTempList.ClothesColorMessage).arg(orderClothesAttributeMessageTempList.ClothesDefectMessage).arg(orderClothesAttributeMessageTempList.ClothesBrandMessage).arg(orderClothesAttributeMessageTempList.ClothesTreatmentMessage)
                 .arg(orderClothesAttributeMessageTempList.ClothesEffectMessage).arg(orderClothesAttributeMessageTempList.ClothesPriceMessage).arg(orderInfoTemp.MoneyCount).arg(orderInfoTemp.Discount)
                 .arg(orderInfoTemp.AfterDiscountMoneyCount).arg(orderInfoTemp.ClothesCount).arg(orderInfoTemp.CustomerCardMoney).arg(orderInfoTemp.InputMoney)
                 .arg(orderInfoTemp.OutputMoney).arg(orderInfoTemp.PayWay).arg(orderInfoTemp.HaveNotPaid).arg(orderInfoTemp.GetClothesDate)
                         .arg(orderInfoTemp.CustomerAddress).arg(orderInfoTemp.ShelfID).arg(orderInfoTemp.thisOrderNotPaid).arg(orderInfoTemp.customerCardMoneyBeforePay).arg(orderInfoTemp.OrderCreateDate)
                     );
}

bool orderSql::createNewOrderStatus(OrderInfo orderStatusTemp)
{
     return sql->exec(QString("insert into OrderStatus values ('%1','%2','%3','%4','%5','%6');").arg(orderStatusTemp.orderID).arg(ORDER_NOT_FINISHED_STATUS).arg(CLOTHES_NOT_SEND).arg(orderStatusTemp.customerID).arg(orderStatusTemp.customerName).arg(orderStatusTemp.ShelfID));
}

bool orderSql::updateCurrentOrderID(QString OrderID)
{
    return sql->exec(QString("update CurrentOrderID set CurrentOrderID = '%1';").arg(OrderID));
}

bool orderSql::updateOrderStatusByOrderId(QString OrderId, QString status)
{
    return sql->exec(QString("UPDATE OrderStatus SET OrderStatus = '%1' where OrderID = '%2';").arg(status).arg(OrderId));
}

bool orderSql::updateClothesStatusByOrderId(QString OrderId, QString status)
{
    return sql->exec(QString("UPDATE OrderStatus SET ClothesSendStatus = '%1' where OrderID = '%2';").arg(status).arg(OrderId));
}

bool orderSql::clothesHaveBeenSendOut(QString OrderId)
{
    auto db = pulic::getInstance()->DB;
    db->transaction();
    auto status = sql->exec(QString("UPDATE OrderStatus SET ClothesSendStatus = '%1' where OrderID = '%2';").arg(CLOTHES_HAVE_BEEN_SEND).arg(OrderId));
    if(false == status)// || false == shelfStatus)
    {
        getError();
        db->rollback();
        return false;
    }


    if(true == status)// && true == shelfStatus)
    {
        db->commit();
        return true;
    }
    return status;
}

orderSql::orderSql():
    sql(new QSqlQuery())
{

}
