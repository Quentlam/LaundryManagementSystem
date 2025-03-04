#include "dlggetclothes.h"
#include "ui_dlggetclothes.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "sqlmanager.h"

dlgGetClothes::dlgGetClothes(QWidget *parent) :
    QDialog(parent),
    discount(false),
    payWay("未选择"),
    currentCustomerCost(customerCost(customerInfo())),
    ui(new Ui::dlgGetClothes)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->Time->setDate(QDate::currentDate().addDays(3));
    connect(&dlgGetMon,&dlgGetMoney::finshGetMoney,this,&dlgGetClothes::getMoneyFunc);
    connect(&dlgChoseCus,&dlgChoseCustomer::chosedSuccess,this,&dlgGetClothes::chosedCustomerInfoFunc);
    connect(&selectPage00,&STSelectClothes00::chosenMessage,this,&dlgGetClothes::putChosenMessageIntoTable00);
    connect(&selectPage01,&STSelectClothes01::chosenMessage,this,&dlgGetClothes::putChosenMessageIntoTable01);
    connect(&selectPage02,&STSelectClothes02::chosenMessage,this,&dlgGetClothes::putChosenMessageIntoTable02);
    connect(&selectPage03,&STSelectClothes03::chosenMessage,this,&dlgGetClothes::putChosenMessageIntoTable03);
    connect(&selectPage04,&STSelectClothes04::chosenMessage,this,&dlgGetClothes::putChosenMessageIntoTable04);
    connect(&clothesSelectPage00,&swpage00::chosenType,this,&dlgGetClothes::putChosenTypePage);//五种类型的衣服的选择页面
    connect(&Selectclothes,&STSelectClothesTypeAndPrice::chosenClothesType,this,&dlgGetClothes::putChosenTypeIntoTable);//正式选择
    connect(&dlgdiscount,&dlgDiscount::sentDiscount,this,&dlgGetClothes::putDiscountIntoTable);

    ui->Time->setMinimumDate(QDate::currentDate());

    ui->SW->addWidget(&clothesSelectPage00);//首先先选择对衣物的处理 0
    ui->SW->addWidget(&selectPage00);//选择衣服颜色                1
    ui->SW->addWidget(&selectPage01);//选择衣服瑕疵                2
    ui->SW->addWidget(&selectPage02);//选择衣服品牌                3
    ui->SW->addWidget(&selectPage03);//选择特殊处理                4
    ui->SW->addWidget(&selectPage04);//选择洗后效果                5
    ui->SW->addWidget(&Selectclothes);//正式选择衣服               6
    ui->SW->setCurrentIndex(0);


    for (int i = 0; i < ui->TWClothes->rowCount(); ++i)
    {
        for (int j = 0; j < ui->TWClothes->columnCount() + 1; ++j) {
            ui->TWClothes->setItem(i, j, new QTableWidgetItem(""));
        }
    }

    ui->TWMoney->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWMoney->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->TWMoney->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWMoney->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWMoney->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮


    ui->TWCal->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWCal->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->TWCal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWCal->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWCal->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮


    ui->TWClothes->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWClothes->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWClothes->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮

    reFresh();//初始化一些参数


}

dlgGetClothes::~dlgGetClothes()
{
    delete ui;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是收银了之后
void dlgGetClothes::getMoneyFunc()
{
    payWay = dlgGetMon.payWay;
    if("充值卡支付" == payWay)
    {
        ui->TWMoney->item(0,0)->setText("充值卡支付不收银");//收银多少钱
        ui->TWMoney->item(1,0)->setText("充值卡支付不找零");//收银多少钱
        return;
    }
    ui->TWMoney->item(0,0)->setText(QString::number(dlgGetMon.Money));//收银多少钱
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dlgGetClothes::on_BtnCancel_clicked()
{
    this->close();
    emit backToMainWindow();
}

void dlgGetClothes::on_BtnGetMoney_clicked()
{
    if(false == discount)
    {
        QMessageBox::information(nullptr,"信息","输入收银前，请先点击折扣率并且设置！");
        ui->TWMoney->clearSelection();
        return;
    }
    if(false == selectCustomer)
    {
        dlgGetMon.NormalCustomerMoneyFunc();
    }
    else
    {
        dlgGetMon.VIPCustomerMoneyFunc();
    }

    dlgGetMon.exec();
}


void dlgGetClothes::on_BtnChoseCustomer_clicked()
{
    dlgChoseCus.exec();
}


void dlgGetClothes::chosedCustomerInfoFunc()
{
    customerTemp = dlgChoseCus.chosedCustomer;
    ui->LeName->setReadOnly(true);//首先先让输入框不可编辑，因为客户信息选择好之后就不能改了
    ui->LePhone->setReadOnly(true);
    ui->LeCardID->setReadOnly(true);
    ui->LeCost->setReadOnly(true);
    ui->LeCount->setReadOnly(true);

    ui->LeName->setText(dlgChoseCus.chosedCustomer.Name);//选择好客户之后，就让数据回显
    ui->LePhone->setText(dlgChoseCus.chosedCustomer.Phone);
    ui->LeCardID->setText(dlgChoseCus.chosedCustomer.CardID);
    ui->LeCost->setText(QString::number(dlgChoseCus.chosedCustomer.Spend));
    ui->LeCount->setText(QString::number(dlgChoseCus.chosedCustomer.Count));
    if(!dlgChoseCus.chosedCustomer.CardType.isEmpty())
    {
        ui->TWCal->item(1,0)->setText(dlgChoseCus.chosedCustomer.CardType);
        discount = true;
    }


    ui->TWCal->setItem(4,0,new QTableWidgetItem(QString::number(dlgChoseCus.chosedCustomer.CardMoney)));//表里的卡余额
    selectCustomer = true;
}


void dlgGetClothes::show()
{
    QWidget::show();
    reFresh();
}




void dlgGetClothes::on_BtnCustomerTemp_clicked()
{
    selectCustomer = false;
    ui->LeName->setReadOnly(false);//首先先让输入框可编辑，因为客户信息选择好之后就不能改了，但是可能会有临时客户
    ui->LePhone->setReadOnly(false);
    ui->LeCardID->setReadOnly(false);
    ui->LeCost->setReadOnly(false);
    ui->LeCount->setReadOnly(false);
    ui->LeName->clear();
    ui->LePhone->clear();
    ui->LeCardID->clear();
    ui->LeCost->clear();
    ui->LeCount->clear();
    ui->TWCal->item(4,0)->setText("0");//临时客户的卡余额没有钱
}



void dlgGetClothes::on_TWClothes_cellClicked(int row, int column)
{
    ui->LESearch->setFocus();
    if(ClothesCount < row)
    {
        QMessageBox::information(nullptr,"警告","请按顺序选择衣服！");
        ui->TWClothes->clearSelection();
        return;
    }
    if(0 == column || 6 == column)
    {
        ui->SW->setCurrentIndex(0);
        return;
    }
    ui->SW->setCurrentIndex(column);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////选择好了，放item上
void dlgGetClothes::putChosenMessageIntoTable00()//以下函数都是把衣服的其他属性放到现在的item上
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }

    if(ui->TWClothes->currentRow() != -1)
    {
    ui->TWClothes->currentItem()->setText(selectPage00.message);
    }
    ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    ui->SW->setCurrentIndex(ui->SW->currentIndex() + 1);
}

void dlgGetClothes::putChosenMessageIntoTable01()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    if(ui->TWClothes->currentRow() != -1)
    {
    ui->TWClothes->currentItem()->setText(selectPage01.message);
    }
    ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    ui->SW->setCurrentIndex(ui->SW->currentIndex() + 1);
}

void dlgGetClothes::putChosenMessageIntoTable02()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    if(ui->TWClothes->currentRow() != -1)
    {
    ui->TWClothes->currentItem()->setText(selectPage02.message);
    }
    ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    ui->SW->setCurrentIndex(ui->SW->currentIndex() + 1);
}

void dlgGetClothes::putChosenMessageIntoTable03()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    if(ui->TWClothes->currentRow() != -1)
    {
    ui->TWClothes->currentItem()->setText(selectPage03.message);
    }
    ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    ui->SW->setCurrentIndex(ui->SW->currentIndex() + 1);
}

void dlgGetClothes::putChosenMessageIntoTable04()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    if(ui->TWClothes->currentRow() != -1)
    {
    ui->TWClothes->currentItem()->setText(selectPage04.message);
    }
    ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    ui->SW->setCurrentIndex(ui->SW->currentIndex() + 1);
}

void dlgGetClothes::putChosenTypeIntoTable()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    if(ui->TWClothes->currentRow() != -1)
    {
    int currentRow = ui->TWClothes->currentRow();
    ui->TWClothes->item(currentRow,0)->setText(Selectclothes.Name);
    ui->TWClothes->item(currentRow,6)->setText(Selectclothes.Price);
    }
    else
    {
        QMessageBox::information(nullptr,"警告","请先选择第几件衣服再选择种类！先点击方框，再选择种类哦！");
    }

    if(ui->TWClothes->currentColumn() <= 5)
    {
        ui->SW->setCurrentIndex(1);
        ui->TWClothes->setCurrentItem(ui->TWClothes->item(ui->TWClothes->currentRow(),ui->TWClothes->currentColumn() + 1));
    }
    else if(ui->TWClothes->currentColumn() == 6)
    {
        return;
    }

}


void dlgGetClothes::putChosenTypePage()
{
    if(ClothesCount < ui->TWClothes->currentRow())
    {
        return;
    }
    Selectclothes.choseClothes(clothesSelectPage00.type);
    ui->SW->setCurrentIndex(6);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是创建订单
void dlgGetClothes::on_BtnEnter_clicked()//创建订单了
{
    currentOrder.clothesTemp.clear();
    currentOrder.PayWay = "未选择";
    currentOrder.orderID = "无";
    currentOrder.Discount = "无折扣";
    currentOrder.InputMoney = "无收银";
    currentOrder.MoneyCount = "无总金额";
    currentOrder.customerID = "无客户编号";
    currentOrder.HaveNotPaid = "此单未欠缴";
    currentOrder.OutputMoney = "无找零";
    currentOrder.ClothesCount = "无衣服总数";
    currentOrder.customerName = "无客户姓名";
    currentOrder.customerCount = "无消费次数";
    currentOrder.customerPhone = "无客户电话";
    currentOrder.customerSpend = "无消费次数";
    currentOrder.GetClothesDate = "无取衣日期";
    currentOrder.customerCardID = "无卡号ID";
    currentOrder.CustomerAddress = "无客户地址";
    currentOrder.CustomerCardMoney = "无卡剩余余额";
    currentOrder.AfterDiscountMoneyCount = "无折后价";
    currentOrder.ShelfID = "无架号";


    if(ClothesCount <= 0)
    {
        QMessageBox::information(nullptr,"信息","请至少选择一件衣服！");
        return;
    }
    if(false == discount)
    {
        QMessageBox::information(nullptr,"信息","结算前请先选择折扣率！");
        return;
    }

    if("未选择" == dlgGetMon.payWay || "未选择" == payWay)
    {
        QMessageBox::information(nullptr,"信息","结算前请先选择结算方式！");
        return;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是临时客户
    if(false == selectCustomer)//临时客户
    {
        auto status = QMessageBox::question(nullptr, "未选择客户", "你确定要以临时客户确认订单吗？",QMessageBox::Yes | QMessageBox::No);
        if(status == QMessageBox::Yes)
        {
            currentOrder.orderID = ui->LBOrderNumber->text().right(10);
            currentOrder.customerID = "临时客户无卡";
            currentOrder.customerName = ui->LeName->text();
            currentOrder.customerPhone = ui->LePhone->text();
            currentOrder.customerCount = "临时客户无卡";
            currentOrder.customerSpend = "临时客户无卡";
            currentOrder.customerCardID = "临时客户无卡";

            for(int i = 0 ; i < ClothesCount;i ++)
            {
                selectClothesTemp.Name = ui->TWClothes->item(i,0)->text();
                selectClothesTemp.Color = ui->TWClothes->item(i,1)->text();
                selectClothesTemp.Defect = ui->TWClothes->item(i,2)->text();
                selectClothesTemp.Brand = ui->TWClothes->item(i,3)->text();
                selectClothesTemp.Treament = ui->TWClothes->item(i,4)->text();
                selectClothesTemp.Effect = ui->TWClothes->item(i,5)->text();
                selectClothesTemp.Price = ui->TWClothes->item(i,6)->text();
                currentOrder.clothesTemp.push_back(selectClothesTemp);
            }

            currentOrder.MoneyCount = QString::number(money);
            currentOrder.Discount =  ui->TWCal->item(1,0)->text();
            currentOrder.AfterDiscountMoneyCount = QString::number(afterDiscountMoney);
            currentOrder.ClothesCount = QString::number(ClothesCount);
            currentOrder.InputMoney = QString::number(input);
            currentOrder.OutputMoney = QString::number(output);
            currentOrder.PayWay = dlgGetMon.payWay;
            currentOrder.HaveNotPaid = "临时客户不可欠缴";
            currentOrder.GetClothesDate = ui->Time->text();
            currentOrder.CustomerCardMoney = "临时客户无卡";
            currentOrder.CustomerAddress = "临时客户无地址";

            dlgEnterOrder = new dlgNewOrder(nullptr,0,currentOrder);
            connect(dlgEnterOrder,&dlgNewOrder::CreateNewOrderSuccess,this,&dlgGetClothes::createNewOrderSuccess);
            QMessageBox::information(nullptr,"信息",QString("记录了%1件衣服的信息！").arg(ClothesCount));
            dlgEnterOrder->exec();
            if(true == dlgEnterOrder->orderFinished)
            {
                currentCustomerCost.normalCost(currentOrder.customerName,currentOrder.customerPhone,currentOrder.PayWay,currentOrder.AfterDiscountMoneyCount.toDouble(),currentOrder.orderID);
                return;
            }
            else
            {
                QMessageBox::information(nullptr,"信息","临时客户创建订单失败！");
                return;
            }
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是正式客户
    else//正式客户------以下是创建订单类之后，创建好信息
    {
        dlgChoseCus.chosedCustomer = customerTemp;
        currentOrder.orderID = ui->LBOrderNumber->text().right(10);
        currentOrder.customerID = dlgChoseCus.chosedCustomer.ID;
        currentOrder.customerName = dlgChoseCus.chosedCustomer.Name;
        currentOrder.customerPhone = dlgChoseCus.chosedCustomer.Phone;
        currentOrder.customerCount = QString::number(dlgChoseCus.chosedCustomer.Count + 1);//消费次数要加上
        currentOrder.customerSpend = QString::number(dlgChoseCus.chosedCustomer.Spend + afterDiscountMoney);//消费额要加上这次消费了多少
        currentOrder.customerCardID = dlgChoseCus.chosedCustomer.CardID;


        for(int i = 0 ; i < ClothesCount;i ++)
        {
            selectClothesTemp.Name = ui->TWClothes->item(i,0)->text();
            selectClothesTemp.Color = ui->TWClothes->item(i,1)->text();
            selectClothesTemp.Defect = ui->TWClothes->item(i,2)->text();
            selectClothesTemp.Brand = ui->TWClothes->item(i,3)->text();
            selectClothesTemp.Treament = ui->TWClothes->item(i,4)->text();
            selectClothesTemp.Effect = ui->TWClothes->item(i,5)->text();
            selectClothesTemp.Price = ui->TWClothes->item(i,6)->text();
            currentOrder.clothesTemp.push_back(selectClothesTemp);
        }
        currentOrder.MoneyCount = QString::number(money);
        currentOrder.Discount =  ui->TWCal->item(1,0)->text();
        currentOrder.AfterDiscountMoneyCount = QString::number(afterDiscountMoney);
        currentOrder.ClothesCount = QString::number(ClothesCount);
        currentOrder.InputMoney = QString::number(input);
        currentOrder.OutputMoney = QString::number(output);
        currentOrder.PayWay = dlgGetMon.payWay;
        currentOrder.GetClothesDate = ui->Time->text();
        currentOrder.CustomerAddress = dlgChoseCus.chosedCustomer.Address;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是查卡余额并且查看要不要充值
        if(dlgChoseCus.chosedCustomer.CardMoney >= afterDiscountMoney && payWay == "充值卡支付")//就是先检查一下钱够不够，如果卡余额大于折后价
        {
            currentOrder.InputMoney = QString::number(afterDiscountMoney);
            currentOrder.OutputMoney = QString::number(afterDiscountMoney);
            currentOrder.HaveNotPaid = "此单未欠缴";
        }
        else if(dlgChoseCus.chosedCustomer.CardMoney < afterDiscountMoney && payWay == "充值卡支付")//如果不够
        {
            auto ReChargeStatus = QMessageBox::question(nullptr,"警告！","客户卡上金额不够！是否充值！",QMessageBox::Yes | QMessageBox::No);
            if(ReChargeStatus == QMessageBox::Yes)
            {
                customerReCharge = new dlgCustomerRecharge(nullptr,dlgChoseCus.chosedCustomer);
                connect(customerReCharge,&dlgCustomerRecharge::rechargeSuccess,this,&dlgGetClothes::rechargeSuccessFuc);
                customerReCharge->exec();
                return;
            }

            else//如果不充值就看看是否欠缴
            {
             auto HaveNoPaid =  QMessageBox::question(nullptr,"警告！","客户是否欠缴！",QMessageBox::Yes | QMessageBox::No);
             if(HaveNoPaid == QMessageBox::Yes)
             {//如果充值卡不充钱的情况下，欠缴就是先把卡里的钱先花完，然后再加上剩余订单没给的钱，再加上客户之前欠的钱
                currentOrder.HaveNotPaid = QString("欠缴：%1").arg(QString::number(dlgChoseCus.chosedCustomer.HaveNotPaidMoney.toDouble() + afterDiscountMoney - dlgChoseCus.chosedCustomer.CardMoney));
                dlgChoseCus.chosedCustomer.HaveNotPaid = "欠缴";
                dlgChoseCus.chosedCustomer.HaveNotPaidMoney = QString::number(dlgChoseCus.chosedCustomer.HaveNotPaidMoney.toDouble() + afterDiscountMoney - dlgChoseCus.chosedCustomer.CardMoney);             
             }
             else
             {
                QMessageBox::information(nullptr,"信息","创建订单失败！");
                return;
             }
            }
        }

        if(currentOrder.InputMoney.toDouble() < currentOrder.AfterDiscountMoneyCount.toDouble() && payWay != "充值卡支付")//如果客户不选择用充值卡而是用的其他方式，但是又欠缴了
        {
            auto HaveNoPaid =  QMessageBox::question(nullptr,"警告！","客户是否欠缴！",QMessageBox::Yes | QMessageBox::No);
            if(HaveNoPaid == QMessageBox::Yes)
            {
                currentOrder.HaveNotPaid = QString("欠缴：%1").arg(QString::number(dlgChoseCus.chosedCustomer.HaveNotPaidMoney.toDouble() + afterDiscountMoney - currentOrder.InputMoney.toDouble()));
                dlgChoseCus.chosedCustomer.HaveNotPaid = "欠缴";
                dlgChoseCus.chosedCustomer.HaveNotPaidMoney = QString::number(dlgChoseCus.chosedCustomer.HaveNotPaidMoney.toDouble() + afterDiscountMoney - currentOrder.InputMoney.toDouble());
            }
            else
            {
               QMessageBox::information(nullptr,"信息","创建订单失败！");
               return;
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////以下是做订单的最后准备
        currentOrder.CustomerCardMoney = QString::number(dlgChoseCus.chosedCustomer.CardMoney);//这个是为了在结算之后，再写入订单里，防止钱不一样
        selectClothes = true;//已经选好衣服了
        dlgEnterOrder = new dlgNewOrder(nullptr,1,currentOrder);
        connect(dlgEnterOrder,&dlgNewOrder::CreateNewOrderSuccess,this,&dlgGetClothes::createNewOrderSuccess);
        dlgEnterOrder->HaveNotPaidSituation(dlgChoseCus.chosedCustomer.HaveNotPaidMoney);
        QMessageBox::information(nullptr,"信息",QString("记录了%1件衣服的信息！").arg(ClothesCount));
        dlgEnterOrder->exec();
        if(!dlgEnterOrder->choseShelf.shelfSelected)
        {
            QMessageBox::information(nullptr,"信息","请选择衣服架号！");
            return;
        }
        currentOrder.ShelfID = dlgEnterOrder->choseShelf.shelfNumber;
        currentCustomerCost = customerCost(dlgChoseCus.chosedCustomer);
        if(dlgChoseCus.chosedCustomer.CardMoney >= afterDiscountMoney && payWay == "充值卡支付" && true == dlgEnterOrder->orderFinished)
        {
            currentCustomerCost.cardCost(currentCustomerCost.temp,currentOrder.InputMoney.toDouble(),currentOrder.orderID);//最后才记录这个是记录谁用卡花了多少钱的，消费一个操作日志，订单一个日志
            return;
        }
        else if("此单未欠缴" == currentOrder.HaveNotPaid && payWay != "充值卡支付" && true == dlgEnterOrder->orderFinished)//如果不是卡支付们看看欠缴没有
        {
            currentCustomerCost.ortherCost(currentCustomerCost.temp,currentOrder.AfterDiscountMoneyCount.toDouble(),payWay,currentOrder.orderID);//如果是充值卡以外的支付
            return;
        }

        if(dlgChoseCus.chosedCustomer.CardMoney < afterDiscountMoney && payWay == "充值卡支付" && true == dlgEnterOrder->orderFinished)//如果充值卡算欠缴了，就是想优先用完卡内的钱
        {
           currentCustomerCost.cardCostHaveNotPaid(currentCustomerCost.temp,currentOrder.AfterDiscountMoneyCount.toDouble(),currentOrder.orderID);//如果用充值卡支付，并且钱不够了,先把卡里的钱花完，再算到欠缴去
           return;
        }

        if("此单未欠缴" != currentOrder.HaveNotPaid && payWay != "充值卡支付" && true == dlgEnterOrder->orderFinished)//如果客户其他方式欠缴了也算欠缴了，并且必须要加到欠缴费和消费额和消费次数里，并且要先花卡里的钱
        {
           currentCustomerCost.ortherCostHaveNotPaid(currentCustomerCost.temp,currentOrder.AfterDiscountMoneyCount.toDouble(),payWay,currentOrder.orderID);//如果不用充值卡支付，并且钱不够了，那么就要加到欠缴里面去
           return;
        }

        QMessageBox::information(nullptr,"信息","创建订单失败！");
        return;


    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

int dlgGetClothes::CalClothesMoney()//这个是数建议金额要多少钱
{
    int filledRowCount = 0;
    int costCount = 0;
    //qDebug() << "总共有 " <<ui->TWClothes->columnCount() << "列" ;
    for (int row = 0; row < ui->TWClothes->rowCount(); row ++)
    {
        bool hasValue = false;
        // 遍历该行的每一列
        for (int column = 0; column < ui->TWClothes->columnCount(); column ++)
        {
            QTableWidgetItem *item = ui->TWClothes->item(row, column);
            // 检查单元格是否有值
            if (item != nullptr && !item->text().isEmpty())
            {
                hasValue = true;
                costCount += ui->TWClothes->item(item->row(),6)->text().toInt();
                break; // 如果该行有任何一个单元格有值，则跳过检查其他单元格
            }
        }

        // 如果该行有值，计数加1
        if (hasValue)
        {
            ++filledRowCount;
        }
    }

    return costCount;
}

int dlgGetClothes::CalClothesCount()//这个是数有多少件衣服
{
    int filledRowCount = 0;
    //qDebug() << "总共有 " <<ui->TWClothes->columnCount() << "列" ;
    for (int row = 0; row < ui->TWClothes->rowCount(); row ++)
    {
        bool hasValue = false;
        // 遍历该行的每一列
        for (int column = 0; column < ui->TWClothes->columnCount(); column ++)
        {
            QTableWidgetItem *item = ui->TWClothes->item(row, column);

            // 检查单元格是否有值
            if (item != nullptr && !item->text().isEmpty())
            {
                //qDebug() << "当前元素：" << item->text();
                hasValue = true;
                break; // 如果该行有任何一个单元格有值，则跳过检查其他单元格
            }
        }

        // 如果该行有值，计数加1
        if (hasValue)
        {
            ++filledRowCount;
        }

    }



    return filledRowCount;
}


void dlgGetClothes::on_TWClothes_cellChanged(int row, int column)//如果衣服的表格有变化的话，那么就看看表格里是不是有钱要去计算，每次变化都触发这个函数
{
    ui->TWCal->item(0,0)->setText(QString::number(CalClothesMoney()));
    money = CalClothesMoney();//每次都要把衣服的总金额给到money
    ClothesCount = CalClothesCount();//并且把总共的衣服数量放好
    ui->TWCal->item(3,0)->setText(QString::number(CalClothesCount()));
}


void dlgGetClothes::on_TWCal_cellChanged(int row, int column)//如果计算表有变化的话，也就是已经点了折扣率之后，就会计算折后价
{
    calFinalMoney();
}


void dlgGetClothes::on_TWMoney_cellChanged(int row, int column)//如果点击了收银并且选了多少钱之后，就会触发结算找零多少钱
{
    if("充值卡支付" == payWay)
    {
        return;
    }
    calFinalMoney();
}

void dlgGetClothes::on_TWCal_cellClicked(int row, int column)//点击折扣率的时候会出现弹窗
{
    dlgdiscount.exec();
}

void dlgGetClothes::putDiscountIntoTable()//把折扣放到表里面
{
    discount = true;
    ui->TWCal->item(1,0)->setText(dlgdiscount.Message);
}

void dlgGetClothes::reFresh()//每次打开这个界面的时候，都刷新一遍,包括一些初始值的设定
{
    discount = false;
    selectCustomer = false;
    selectClothes = false;
    customerTemp = customerInfo();
    money = 0.0;
    payWay = "未选择";
    input = 0.0;//收银0元
    output = 0.0;//找零0元

    for (int i = 0; i < ui->TWClothes->rowCount(); ++i)
    {
        for (int j = 0; j < ui->TWClothes->columnCount() + 1; ++j) {
            ui->TWClothes->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    currentOrder = OrderInfo();
    dlgChoseCus.reFresh();
    dlgdiscount.setCurrentIndex(0);
    ui->Time->setDate(QDate::currentDate().addDays(3));
    ui->Time->setMinimumDate(QDate::currentDate());
    ui->LBOrderNumber->setText(QString("当前流水号：%1").arg(orderNumberGenrator.generateOrderNumber()));//设置当前流水号
    ui->TWMoney->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWMoney->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->TWMoney->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWMoney->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWMoney->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮


    ui->TWCal->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWCal->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->TWCal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWCal->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWCal->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮


    ui->TWClothes->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWClothes->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWClothes->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮
    ui->SW->setCurrentIndex(0);
    ui->LeName->setReadOnly(false);//首先先让输入框可编辑，因为客户信息选择好之后就不能改了，但是可能会有临时客户
    ui->LePhone->setReadOnly(false);
    ui->LeCardID->setReadOnly(false);
    ui->LeCost->setReadOnly(false);
    ui->LeCount->setReadOnly(false);
    ui->LeName->clear();
    ui->LePhone->clear();
    ui->LeCardID->clear();
    ui->LeCost->clear();
    ui->LeCount->clear();


    ui->TWCal->item(0,0)->setText("0");//初始化一下计算表
    ui->TWCal->item(1,0)->setText("0");
    ui->TWCal->item(2,0)->setText("0");
    ui->TWCal->item(3,0)->setText("0");
    ui->TWCal->item(4,0)->setText("0");


    ui->TWMoney->item(0,0)->setText("0");//初始化一下收银表
    ui->TWMoney->item(1,0)->setText("0");


    selectPage00.reFresh();
    selectPage01.reFresh();
    selectPage02.reFresh();
    selectPage03.reFresh();
    selectPage04.reFresh();
    Selectclothes.choseClothes(0);
}


void dlgGetClothes::calFinalMoney()//计算折后价
{
    QString input = QString::number(ui->TWCal->item(0,0)->text().toDouble() * ui->TWCal->item(1,0)->text().toDouble(),'f',2);//总金额 * 折扣率
    afterDiscountMoney = input.toDouble();
    ui->TWCal->item(2,0)->setText(input);//折后价

    QString finalInput = QString::number(ui->TWMoney->item(0,0)->text().toDouble() - ui->TWCal->item(2,0)->text().toDouble(),'f',2);//收进 - 折后价 = 找零
    this->output = finalInput.toDouble();//这个是找零
    this->input = ui->TWMoney->item(0,0)->text().toDouble();//这个是收银
    if(payWay == "充值卡支付")
    {
        ui->TWMoney->item(1,0)->setText("充值卡不支持找零");//计算出找零并且显示
        return;
    }
    ui->TWMoney->item(1,0)->setText(finalInput);//计算出找零并且显示
}

void dlgGetClothes::createNewOrderSuccess()
{
    selectClothes = false;
    ClothesCount = 0;
    this->close();
    emit backToMainWindow();
}


void dlgGetClothes::rechargeSuccessFuc()
{
    dlgChoseCus.reFresh();
    dlgChoseCus.updateChosenCustomerById(dlgChoseCus.chosedCustomer,dlgChoseCus.chosedCustomer.ID);
    customerTemp = dlgChoseCus.chosedCustomer;
    ui->TWCal->item(4,0)->setText(QString::number(dlgChoseCus.chosedCustomer.CardMoney));//再把卡金额放进去
    //qDebug() << "当前客户的钱为：" << dlgChoseCus.chosedCustomer.CardMoney;
}

void dlgGetClothes::keyPressEvent(QKeyEvent *event)
{
    if(
      Qt::Key::Key_0 == event->key()
    ||Qt::Key::Key_1 == event->key()
    ||Qt::Key::Key_2 == event->key()
    ||Qt::Key::Key_3 == event->key()
    ||Qt::Key::Key_4 == event->key()
    ||Qt::Key::Key_5 == event->key()
    ||Qt::Key::Key_6 == event->key()
    ||Qt::Key::Key_7 == event->key()
    ||Qt::Key::Key_8 == event->key()
    ||Qt::Key::Key_9 == event->key()
           )
    {
       QString text = event->text();
       ui->LESearch->setFocus();
       ui->LESearch->setText(text);
    }
    if(Qt::Key::Key_Enter == event->key())
    {
        int index = ui->SW->currentIndex();
        bool status = false;
        //qDebug() << index;
       if(0 == index || 6 == index)
       {
            status = Selectclothes.searchClothes(ui->LESearch->text());
            if(true == status)ui->SW->setCurrentIndex(1);
       }

       if(1 == index)
       {
           status = selectPage00 .searchClothes(ui->LESearch->text());
           if(true == status)ui->SW->setCurrentIndex(2);
       }
       if(2 == index)
       {
           status = selectPage01 .searchClothes(ui->LESearch->text());
           if(true == status)ui->SW->setCurrentIndex(3);
       }

       if(3 == index)
       {
           status = selectPage02 .searchClothes(ui->LESearch->text());
           if(true == status)ui->SW->setCurrentIndex(4);
       }

       if(4 == index)
       {
           status = selectPage03 .searchClothes(ui->LESearch->text());
           if(true == status)ui->SW->setCurrentIndex(5);
       }

       if(5 == index)
       {
           status = selectPage04 .searchClothes(ui->LESearch->text());
           if(true == status)ui->SW->setCurrentIndex(6);
       }



       ui->LESearch->clear();
    }


}

void dlgGetClothes::on_LESearch_textChanged(const QString &arg1)
{
    if(!arg1.isNull() && 0 == ui->SW->currentIndex())
    {
        ui->SW->setCurrentIndex(6);
    }

    if(ui->LESearch->text().size() == 14)
    {
        auto ptr = sqlManager::createCustomerSql()->selectCusotmerByCardId(ui->LESearch->text());
        if(!(*ptr).ID.isNull())
        {
            dlgChoseCus.chosedCustomer = *(ptr);
            customerTemp = dlgChoseCus.chosedCustomer;
            ui->LeName->setReadOnly(true);//首先先让输入框不可编辑，因为客户信息选择好之后就不能改了
            ui->LePhone->setReadOnly(true);
            ui->LeCardID->setReadOnly(true);
            ui->LeCost->setReadOnly(true);
            ui->LeCount->setReadOnly(true);

            ui->LeName->setText(dlgChoseCus.chosedCustomer.Name);//选择好客户之后，就让数据回显
            ui->LePhone->setText(dlgChoseCus.chosedCustomer.Phone);
            ui->LeCardID->setText(dlgChoseCus.chosedCustomer.CardID);
            ui->LeCost->setText(QString::number(dlgChoseCus.chosedCustomer.Spend));
            ui->LeCount->setText(QString::number(dlgChoseCus.chosedCustomer.Count));
            if(!dlgChoseCus.chosedCustomer.CardType.isEmpty())
            {
                ui->TWCal->item(1,0)->setText(dlgChoseCus.chosedCustomer.CardType);
                discount = true;
            }


            ui->TWCal->setItem(4,0,new QTableWidgetItem(QString::number(dlgChoseCus.chosedCustomer.CardMoney)));//表里的卡余额
            selectCustomer = true;
            ui->LESearch->clear();
        }
    }
}

void dlgGetClothes::on_LESearch_returnPressed()
{
    if(ui->LESearch->text().size() == 14)
    {
        auto ptr = sqlManager::createCustomerSql()->selectCusotmerByCardId(ui->LESearch->text());
        if(!(*ptr).ID.isNull())
        {
            dlgChoseCus.chosedCustomer = *(ptr);
            customerTemp = dlgChoseCus.chosedCustomer;
            ui->LeName->setReadOnly(true);//首先先让输入框不可编辑，因为客户信息选择好之后就不能改了
            ui->LePhone->setReadOnly(true);
            ui->LeCardID->setReadOnly(true);
            ui->LeCost->setReadOnly(true);
            ui->LeCount->setReadOnly(true);

            ui->LeName->setText(dlgChoseCus.chosedCustomer.Name);//选择好客户之后，就让数据回显
            ui->LePhone->setText(dlgChoseCus.chosedCustomer.Phone);
            ui->LeCardID->setText(dlgChoseCus.chosedCustomer.CardID);
            ui->LeCost->setText(QString::number(dlgChoseCus.chosedCustomer.Spend));
            ui->LeCount->setText(QString::number(dlgChoseCus.chosedCustomer.Count));
            if(!dlgChoseCus.chosedCustomer.CardType.isEmpty())
            {
                ui->TWCal->item(1,0)->setText(dlgChoseCus.chosedCustomer.CardType);
                discount = true;
            }


            ui->TWCal->setItem(4,0,new QTableWidgetItem(QString::number(dlgChoseCus.chosedCustomer.CardMoney)));//表里的卡余额
            selectCustomer = true;
        }
        if(nullptr == ptr)
        {
            QMessageBox::information(nullptr,"信息","找不到该客户！");
        }
    }
    ui->LESearch->clear();
}
