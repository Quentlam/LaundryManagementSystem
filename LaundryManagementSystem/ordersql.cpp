#include "ordersql.h"
#include <QMessageBox>
#include "pulic.h"

orderSql* orderSql::Instance = nullptr;



orderSql::~orderSql()
{
    delete  sql;
    delete  Instance;
}

std::unique_ptr<OrderStatus> orderSql::selectOrderStatusByOrderID(QString OrderID)
{
    std::unique_ptr<OrderStatus> orderStatusTemp = std::make_unique<OrderStatus>();
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

std::unique_ptr<QList<OrderInfo> > orderSql::selectAllOrder()
{
    std::unique_ptr<QList<OrderInfo>> orderInfoTempList = std::make_unique<QList<OrderInfo>>();
    sql->exec("select * from OrderLog");
    SelectClothesInfo temp;
    OrderInfo orderTemp;
    while(sql->next())
    {
        orderTemp.orderID                = sql->value(0).toString();
        orderTemp.customerID             = sql->value(1).toString();
        orderTemp.customerName           = sql->value(2).toString();
        orderTemp.customerPhone          = sql->value(3).toString();
        orderTemp.customerCount          = sql->value(4).toString();
        orderTemp.customerSpend          = sql->value(5).toString();
        orderTemp.customerCardID         = sql->value(6).toString();
        temp.Name                        = sql->value(7).toString();
        temp.Color                       = sql->value(8).toString();
        temp.Defect                      = sql->value(9).toString();
        temp.Brand                       = sql->value(10).toString();
        temp.Treament                    = sql->value(11).toString();
        temp.Effect                      = sql->value(12).toString();
        temp.Price                       = sql->value(13).toString();
        orderTemp.clothesTemp.push_back(temp);
        orderTemp.MoneyCount             = sql->value(14).toString();
        orderTemp.Discount               = sql->value(15).toString();
        orderTemp.AfterDiscountMoneyCount= sql->value(16).toString();
        orderTemp.ClothesCount           = sql->value(17).toString();
        orderTemp.CustomerCardMoney      = sql->value(18).toString();
        orderTemp.InputMoney             = sql->value(19).toString();
        orderTemp.OutputMoney            = sql->value(20).toString();
        orderTemp.PayWay                 = sql->value(21).toString();
        orderTemp.HaveNotPaid            = sql->value(22).toString();
        orderTemp.GetClothesDate         = sql->value(23).toString();
        orderTemp.CustomerAddress        = sql->value(24).toString();
        orderTemp.ShelfID                = sql->value(25).toString();
        orderInfoTempList->push_back(orderTemp);
    }
    return orderInfoTempList;

}

std::unique_ptr<QList<OrderStatus>> orderSql::selectAllOrderStatus()
{
    std::unique_ptr<QList<OrderStatus>> orderStatusTempList = std::make_unique<QList<OrderStatus>>();
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

bool orderSql::createNewOrder(OrderInfo &orderInfoTemp,OrderClothesAttributeMessage& orderClothesAttributeMessageTempList)
{
    return sql->exec(QString("insert into OrderLog values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26');")
                 .arg(orderInfoTemp.orderID).arg(orderInfoTemp.customerID).arg(orderInfoTemp.customerName).arg(orderInfoTemp.customerPhone)
                 .arg(orderInfoTemp.customerCount).arg(orderInfoTemp.customerSpend).arg(orderInfoTemp.customerCardID).arg(orderClothesAttributeMessageTempList.ClothesNameMessage)
                 .arg(orderClothesAttributeMessageTempList.ClothesColorMessage).arg(orderClothesAttributeMessageTempList.ClothesDefectMessage).arg(orderClothesAttributeMessageTempList.ClothesBrandMessage).arg(orderClothesAttributeMessageTempList.ClothesTreatmentMessage)
                 .arg(orderClothesAttributeMessageTempList.ClothesEffectMessage).arg(orderClothesAttributeMessageTempList.ClothesPriceMessage).arg(orderInfoTemp.MoneyCount).arg(orderInfoTemp.Discount)
                 .arg(orderInfoTemp.AfterDiscountMoneyCount).arg(orderInfoTemp.ClothesCount).arg(orderInfoTemp.CustomerCardMoney).arg(orderInfoTemp.InputMoney)
                 .arg(orderInfoTemp.OutputMoney).arg(orderInfoTemp.PayWay).arg(orderInfoTemp.HaveNotPaid).arg(orderInfoTemp.GetClothesDate)
                 .arg(orderInfoTemp.CustomerAddress).arg(orderInfoTemp.ShelfID)
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
