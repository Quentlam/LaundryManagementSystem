#include "dlgordersearch.h"
#include "ui_dlgordersearch.h"
#include "pulic.h"


dlgOrderSearch::dlgOrderSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgOrderSearch)
{
    ui->setupUi(this);
    ui->DateStart->hide();
    ui->DateEnd->hide();
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reFresh();
}

dlgOrderSearch::~dlgOrderSearch()
{
    delete ui;
}

void dlgOrderSearch::on_LeSearch_textChanged(const QString &arg1)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                if (item->text().contains(arg1,Qt::CaseInsensitive)) {
                    rowMatches = true;
                    break;
                }
            }
        }
        // 根据是否匹配来显示或隐藏行
        ui->tableWidget->setRowHidden(row, !rowMatches);
    }
}

void dlgOrderSearch::on_RaDateSearch_clicked()
{
    if(ui->RaDateSearch->isChecked())
    {
        ui->DateStart->show();
        ui->DateEnd->show();
    }
    else
    {
        ui->DateStart->hide();
        ui->DateEnd->hide();
    }
}

void dlgOrderSearch::reFresh()
{
    ui->tableWidget->clear();
    allOrder.clear();
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select count(OrderID) from OrderLog");
    sqlPtr->next();
    int orderCnt = sqlPtr->value(0).toInt();
    QList<QString> OrderTittle;
    OrderTittle << "订单流水号" << "客户编号" << "客户姓名" << "客户电话" << "客户消费次数" << "客户消费额" << "客户卡号" << "衣服名称" << "衣服颜色";
    OrderTittle << "衣服瑕疵" << "衣服品牌" << "特殊处理" << "洗后效果" << "价格" << "订单总金额" << "折扣率" << "订单折后价" << "衣服总数" << "客户卡余额" << "收银" << "找零";
    OrderTittle << "支付方式" << "客户当时欠缴情况" << "取衣日期" << "客户地址" << "架号";
    ui->LBCnt->setText(QString("显示订单总数为：%1").arg(orderCnt));
    ui->tableWidget->setRowCount(orderCnt);
    ui->tableWidget->setColumnCount(OrderTittle.size());
    for(int i = 0 ; i < OrderTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(OrderTittle[i]));//这里是设置标题


    sqlPtr->exec("select * from OrderLog");
    SelectClothesInfo temp;
    OrderInfo orderTemp;

    while(sqlPtr->next())
    {
        orderTemp.orderID                = sqlPtr->value(0).toString();
        orderTemp.customerID             = sqlPtr->value(1).toString();
        orderTemp.customerName           = sqlPtr->value(2).toString();
        orderTemp.customerPhone          = sqlPtr->value(3).toString();
        orderTemp.customerCount          = sqlPtr->value(4).toString();
        orderTemp.customerSpend          = sqlPtr->value(5).toString();
        orderTemp.customerCardID         = sqlPtr->value(6).toString();
        temp.Name                        = sqlPtr->value(7).toString();
        temp.Color                       = sqlPtr->value(8).toString();
        temp.Defect                      = sqlPtr->value(9).toString();
        temp.Brand                       = sqlPtr->value(10).toString();
        temp.Treament                    = sqlPtr->value(11).toString();
        temp.Effect                      = sqlPtr->value(12).toString();
        temp.Price                       = sqlPtr->value(13).toString();
        orderTemp.clothesTemp.push_back(temp);
        orderTemp.MoneyCount             = sqlPtr->value(14).toString();
        orderTemp.Discount               = sqlPtr->value(15).toString();
        orderTemp.AfterDiscountMoneyCount= sqlPtr->value(16).toString();
        orderTemp.ClothesCount           = sqlPtr->value(17).toString();
        orderTemp.CustomerCardMoney      = sqlPtr->value(18).toString();
        orderTemp.InputMoney             = sqlPtr->value(19).toString();
        orderTemp.OutputMoney            = sqlPtr->value(20).toString();
        orderTemp.PayWay                 = sqlPtr->value(21).toString();
        orderTemp.HaveNotPaid            = sqlPtr->value(22).toString();
        orderTemp.GetClothesDate         = sqlPtr->value(23).toString();
        orderTemp.CustomerAddress        = sqlPtr->value(24).toString();
        orderTemp.ShelfID        = sqlPtr->value(25).toString();
        allOrder.push_back(orderTemp);
    }

    for(int i = 0 ; i < allOrder.size(); i ++)
    {
        ui->tableWidget->setItem(i,0 ,new QTableWidgetItem(allOrder[i].orderID));
        ui->tableWidget->setItem(i,1 ,new QTableWidgetItem(allOrder[i].customerID));
        ui->tableWidget->setItem(i,2 ,new QTableWidgetItem(allOrder[i].customerName));
        ui->tableWidget->setItem(i,3 ,new QTableWidgetItem(allOrder[i].customerPhone));
        ui->tableWidget->setItem(i,4 ,new QTableWidgetItem(allOrder[i].customerCount));
        ui->tableWidget->setItem(i,5 ,new QTableWidgetItem(allOrder[i].customerSpend));
        ui->tableWidget->setItem(i,6 ,new QTableWidgetItem(allOrder[i].customerCardID));
        ui->tableWidget->setItem(i,7 ,new QTableWidgetItem(allOrder[i].clothesTemp[i].Name));
        ui->tableWidget->setItem(i,8 ,new QTableWidgetItem(allOrder[i].clothesTemp[i].Color));
        ui->tableWidget->setItem(i,9 ,new QTableWidgetItem(allOrder[i].clothesTemp[i].Defect));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem(allOrder[i].clothesTemp[i].Brand));
        ui->tableWidget->setItem(i,11,new QTableWidgetItem(allOrder[i].clothesTemp[i].Treament));
        ui->tableWidget->setItem(i,12,new QTableWidgetItem(allOrder[i].clothesTemp[i].Effect));
        ui->tableWidget->setItem(i,13,new QTableWidgetItem(allOrder[i].clothesTemp[i].Price));
        ui->tableWidget->setItem(i,14,new QTableWidgetItem(allOrder[i].MoneyCount));
        ui->tableWidget->setItem(i,15,new QTableWidgetItem(allOrder[i].Discount));
        ui->tableWidget->setItem(i,16,new QTableWidgetItem(allOrder[i].AfterDiscountMoneyCount));
        ui->tableWidget->setItem(i,17,new QTableWidgetItem(allOrder[i].ClothesCount));
        ui->tableWidget->setItem(i,18,new QTableWidgetItem(allOrder[i].CustomerCardMoney));
        ui->tableWidget->setItem(i,19,new QTableWidgetItem(allOrder[i].InputMoney));
        ui->tableWidget->setItem(i,20,new QTableWidgetItem(allOrder[i].OutputMoney));
        ui->tableWidget->setItem(i,21,new QTableWidgetItem(allOrder[i].PayWay));
        ui->tableWidget->setItem(i,22,new QTableWidgetItem(allOrder[i].HaveNotPaid));
        ui->tableWidget->setItem(i,23,new QTableWidgetItem(allOrder[i].GetClothesDate));
        ui->tableWidget->setItem(i,24,new QTableWidgetItem(allOrder[i].CustomerAddress));
        ui->tableWidget->setItem(i,25,new QTableWidgetItem(allOrder[i].ShelfID));
    }
    ui->tableWidget->update();

}

void dlgOrderSearch::show()
{
    QWidget::show();
    reFresh();
}

void dlgOrderSearch::on_tableWidget_cellClicked(int row, int column)
{
    ui->LBCurrentOrderID->setText(QString("选中的订单流水号：%1").arg(ui->tableWidget->item(row,0)->text()));
    ui->LBCurrentCustomerName->setText(QString("选中的客户姓名：%2").arg(ui->tableWidget->item(row,2)->text()));
}
