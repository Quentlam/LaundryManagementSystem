#include "dlgneworder.h"
#include "ui_dlgneworder.h"
#include "pulic.h"
#include "printpreviewwidget.h"
#include "sqlmanager.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>



dlgNewOrder::dlgNewOrder(QWidget *parent, int CustomerType, OrderInfo currentOrder):
    QDialog(parent),
    dlgSelectClothes(new dlgSelectClothesInfo(nullptr,currentOrder.clothesTemp)),
    currentOrder(currentOrder),
    orderFinished(false),
    ui(new Ui::dlgNewOrder)
{
        ui->setupUi(this);
        this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
        connect(&choseShelf,&dlgChoseShelf::choseShelfSuccess,this,&dlgNewOrder::setShelfNumber);
        switch (CustomerType)
        {
            case 0://如果是临时客户
            {
                ui->LBInput->setText(QString("收银：%1").arg(currentOrder.InputMoney));
                ui->LBPhone->setText(QString("客户电话：%1").arg(currentOrder.customerPhone));
                ui->LBOutput->setText(QString("找零：%1").arg(currentOrder.OutputMoney));
                ui->LBAddress->setText(QString("客户住址：%1").arg(currentOrder.CustomerAddress));
                ui->LBOrderID->setText(QString("流水号：%1").arg(currentOrder.orderID));
                ui->LBDiscount->setText(QString("折扣率：%1").arg(currentOrder.Discount));
                ui->LBCustomerID->setText(QString("客户编号：%1").arg(currentOrder.customerID));
                ui->LBHaveNotPaid->setText(QString("客户现在欠缴情况：%1").arg(currentOrder.HaveNotPaid));
                ui->LBClothesCount->setText(QString("衣服总件数：%1").arg(currentOrder.ClothesCount));
                ui->LBCustomerName->setText(QString("客户姓名：%1").arg(currentOrder.customerName));
                ui->LBCustomerCount->setText(QString("客户消费次数：%1").arg(currentOrder.customerCount));
                ui->LBCustomerSpend->setText(QString("客户消费额：%1").arg(currentOrder.customerSpend));
                ui->LBCustomerCardID->setText(QString("客户卡号：%1").arg(currentOrder.customerCardID));
                ui->LBGetClothesDate->setText(QString("客户取衣日期：%1").arg(currentOrder.GetClothesDate));
                ui->LBMoneyAfterDiscount->setText(QString("折后价：%1").arg(currentOrder.AfterDiscountMoneyCount));
                ui->LBCustomerPayWay->setText(QString("支付方式：%1").arg(currentOrder.PayWay));
                ui->LBMoneyBeforeDiscount->setText(QString("折前价：%1").arg(currentOrder.MoneyCount));
                ui->LBCustomerCardMoneyAfterOrder->setText(QString("客户卡上余额：%1").arg(currentOrder.CustomerCardMoney));
                ui->LBShelfNumber->setText("当前还未选择架号！");
                break;


            }


            case 1://如果是会员客户
            {
                ui->LBInput->setText(QString("收银：%1").arg(currentOrder.InputMoney));
                ui->LBPhone->setText(QString("客户电话：%1").arg(currentOrder.customerPhone));
                ui->LBOutput->setText(QString("找零：%1").arg(currentOrder.OutputMoney));
                ui->LBAddress->setText(QString("客户住址：%1").arg(currentOrder.CustomerAddress));
                ui->LBOrderID->setText(QString("流水号：%1").arg(currentOrder.orderID));
                ui->LBDiscount->setText(QString("折扣率：%1").arg(currentOrder.Discount));
                ui->LBCustomerID->setText(QString("客户编号：%1").arg(currentOrder.customerID));
                ui->LBHaveNotPaid->setText(QString("客户现在欠缴情况：%1").arg(currentOrder.HaveNotPaid));
                ui->LBClothesCount->setText(QString("衣服总件数：%1").arg(currentOrder.ClothesCount));
                ui->LBCustomerName->setText(QString("客户姓名：%1").arg(currentOrder.customerName));
                ui->LBCustomerCount->setText(QString("客户消费次数：%1").arg(currentOrder.customerCount));
                ui->LBCustomerSpend->setText(QString("客户消费额：%1").arg(currentOrder.customerSpend));
                ui->LBCustomerCardID->setText(QString("客户卡号：%1").arg(currentOrder.customerCardID));
                ui->LBGetClothesDate->setText(QString("客户取衣日期：%1").arg(currentOrder.GetClothesDate));
                ui->LBMoneyAfterDiscount->setText(QString("折后价：%1").arg(currentOrder.AfterDiscountMoneyCount));
                ui->LBCustomerPayWay->setText(QString("支付方式：%1").arg(currentOrder.PayWay));
                ui->LBMoneyBeforeDiscount->setText(QString("折前价：%1").arg(currentOrder.MoneyCount));
                ui->LBCustomerCardMoneyAfterOrder->setText(QString("客户卡上余额：%1").arg(currentOrder.CustomerCardMoney));
                ui->LBShelfNumber->setText("当前还未选择架号！");
                if("此单未欠缴" != currentOrder.HaveNotPaid && "充值卡支付" == currentOrder.PayWay)//如果卡欠缴了
                {
                     ui->LBInput->setText("充值卡不支持收银");
                     ui->LBOutput->setText("充值卡不支持找零");
                     ui->LBFinalCardMoney->setText(QString("客户支付后卡上余额：0"));
                     this->currentOrder.CustomerCardMoney = "0";
                }
                else//否则就是没欠缴或者不是充值卡支付，就照常显示即可
                {
                     ui->LBFinalCardMoney->setText(QString("客户支付后卡上余额：%1").arg(currentOrder.CustomerCardMoney));
                }



                if("此单未欠缴" == currentOrder.HaveNotPaid && "充值卡支付" == currentOrder.PayWay)//如果卡未欠缴
                {
                    ui->LBInput->setText("充值卡不支持收银");
                    ui->LBOutput->setText("充值卡不支持找零");
                    currentOrder.InputMoney = "充值卡不支持收银";
                    currentOrder.OutputMoney = "充值卡不支持找零";
                    ui->LBFinalCardMoney->setText(QString("客户支付后卡上余额：%1").arg(currentOrder.CustomerCardMoney.toDouble() - currentOrder.AfterDiscountMoneyCount.toDouble()));
                    this->currentOrder.CustomerCardMoney = QString::number(currentOrder.CustomerCardMoney.toDouble() - currentOrder.AfterDiscountMoneyCount.toDouble());//卡给钱之后，更新一下
                }

                break;
            }
        }


}


void dlgNewOrder::HaveNotPaidSituation(QString money)
{
    ui->LACustomerAgoHaveNotPaid->setText(QString("客户之前欠缴：%1").arg(money));
}


dlgNewOrder::~dlgNewOrder()
{
    delete ui;
}

bool dlgNewOrder::createNewOrder()
{
    OrderClothesAttributeMessage Message;
    for(int i = 0 ; i < currentOrder.clothesTemp.size(); i ++)
    {
        Message.ClothesNameMessage      += (dlgSelectClothes->temp[i].Name + " ")     ;
        Message.ClothesColorMessage     += (dlgSelectClothes->temp[i].Color+ " ")     ;
        Message.ClothesDefectMessage    += (dlgSelectClothes->temp[i].Defect+ " ")    ;
        Message.ClothesBrandMessage     += (dlgSelectClothes->temp[i].Brand+ " ")     ;
        Message.ClothesTreatmentMessage += (dlgSelectClothes->temp[i].Treament+ " ")  ;
        Message.ClothesEffectMessage    += (dlgSelectClothes->temp[i].Effect+ " ")    ;
        Message.ClothesPriceMessage     += (dlgSelectClothes->temp[i].Price + " ")    ;
    }

    if("充值卡支付" == currentOrder.PayWay)
    {
        ui->LBInput->setText("充值卡不支持收银");
        ui->LBOutput->setText("充值卡不支持找零");
        currentOrder.InputMoney = "充值卡不支持收银";
        currentOrder.OutputMoney = "充值卡不支持找零";
    }
    currentOrder.ShelfID = choseShelf.shelfNumber;//这里要更新一下这个架号
    auto status = sqlManager::createOrderSql()->createNewOrder(currentOrder,Message);
    if(false == status)
    {
        sqlManager::createOrderSql()->getError();
        QMessageBox::information(nullptr,"信息","创建订单失败！");
    }
    else
    {
        QMessageBox::information(nullptr,"信息","创建订单成功！");//首先先修改流水号
        auto orderIncrease = sqlManager::createOrderSql()->updateCurrentOrderID(currentOrder.orderID);
         if(false == orderIncrease)
        {
          sqlManager::createOrderSql()->getError();
        }
         auto orderStatus = sqlManager::createOrderSql()->createNewOrderStatus(currentOrder);//其次就是插入新的订单状态
         if(false == orderStatus)
        {
          sqlManager::createOrderSql()->getError();
        }
         bool ShelfOccupy = false;
         if(choseShelf.shelfNumber.right(1) == "A")
         {
             ShelfOccupy =  sqlManager::createShelfSql()->setShelfOccupy(currentOrder.ShelfID,shelfInfo::shelfSet::A);
         }

         if(choseShelf.shelfNumber.right(1) == "B")
         {
             ShelfOccupy = sqlManager::createShelfSql()->setShelfOccupy(currentOrder.ShelfID,shelfInfo::shelfSet::B);
         }
         //最后架号也修改为已上架
         if(false == ShelfOccupy)
         {
             sqlManager::createShelfSql()->getError();
         }

    }

    return status;
}

void dlgNewOrder::on_BtnCancel_clicked()
{
    deleteLater();
    this->close();
}

void dlgNewOrder::on_BtnClothesTemp_clicked()
{
    dlgSelectClothes->exec();
}


void dlgNewOrder::on_BtnEnterOrder_clicked()
{
    if(false == choseShelf.shelfSelected)
    {
        QMessageBox::information(nullptr,"信息","生成订单前，要先确认架号哦！");
        return;
    }
   auto status =  QMessageBox::question(nullptr,"确认订单","请检查无误再确认！",QMessageBox::Yes | QMessageBox::No);
   if(QMessageBox::Yes == status)
   {
       auto Success = createNewOrder();
       if(Success == true)
       {
           orderFinished = true;//此时订单成功创建了
           orderPrinter.printCustomerCurrentOrder(currentOrder);
           orderPrinter.printUserCurrentOrder(currentOrder);
           //orderPrinter.printTest();
           emit CreateNewOrderSuccess();
           this->close();
       }

   }




}

void dlgNewOrder::on_BtnChoseShelf_clicked()
{
    choseShelf.exec();
}


void dlgNewOrder::setShelfNumber()
{
    ui->LBShelfNumber->setText(QString("当前已选择架号：%1").arg(choseShelf.shelfNumber));
}
