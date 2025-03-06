#include "dlgordersearch.h"
#include "ui_dlgordersearch.h"
#include "pulic.h"
#include "sqlmanager.h"


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
    Ref<QList<OrderInfo>> ordetInfoTempList = sqlManager::createOrderSql()->selectAllOrder();
    ui->LBCnt->setText(QString("显示订单总数为：%1").arg(ordetInfoTempList->size()));
    ui->tableWidget->setRowCount(ordetInfoTempList->size());
    ui->tableWidget->setColumnCount(OrderInfo::orderTittle.size());
    for(int i = 0 ; i < OrderInfo::orderTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(OrderInfo::orderTittle[i]));//这里是设置标题


    for(int i = 0 ; i < ordetInfoTempList->size(); i ++)
    {
        ui->tableWidget->setItem(i,0 ,new QTableWidgetItem((*ordetInfoTempList)[i].orderID));
        ui->tableWidget->setItem(i,1 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerID));
        ui->tableWidget->setItem(i,2 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerName));
        ui->tableWidget->setItem(i,3 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerPhone));
        ui->tableWidget->setItem(i,4 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerCount));
        ui->tableWidget->setItem(i,5 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerSpend));
        ui->tableWidget->setItem(i,6 ,new QTableWidgetItem((*ordetInfoTempList)[i].customerCardID));
        ui->tableWidget->setItem(i,7 ,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Name));
        ui->tableWidget->setItem(i,8 ,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Color));
        ui->tableWidget->setItem(i,9 ,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Defect));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Brand));
        ui->tableWidget->setItem(i,11,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Treament));
        ui->tableWidget->setItem(i,12,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Effect));
        ui->tableWidget->setItem(i,13,new QTableWidgetItem((*ordetInfoTempList)[i].clothesTemp[i].Price));
        ui->tableWidget->setItem(i,14,new QTableWidgetItem((*ordetInfoTempList)[i].MoneyCount));
        ui->tableWidget->setItem(i,15,new QTableWidgetItem((*ordetInfoTempList)[i].Discount));
        ui->tableWidget->setItem(i,16,new QTableWidgetItem((*ordetInfoTempList)[i].AfterDiscountMoneyCount));
        ui->tableWidget->setItem(i,17,new QTableWidgetItem((*ordetInfoTempList)[i].ClothesCount));
        ui->tableWidget->setItem(i,18,new QTableWidgetItem((*ordetInfoTempList)[i].CustomerCardMoney));
        ui->tableWidget->setItem(i,19,new QTableWidgetItem((*ordetInfoTempList)[i].InputMoney));
        ui->tableWidget->setItem(i,20,new QTableWidgetItem((*ordetInfoTempList)[i].OutputMoney));
        ui->tableWidget->setItem(i,21,new QTableWidgetItem((*ordetInfoTempList)[i].PayWay));
        ui->tableWidget->setItem(i,22,new QTableWidgetItem((*ordetInfoTempList)[i].HaveNotPaid));
        ui->tableWidget->setItem(i,23,new QTableWidgetItem((*ordetInfoTempList)[i].GetClothesDate));
        ui->tableWidget->setItem(i,24,new QTableWidgetItem((*ordetInfoTempList)[i].CustomerAddress));
        ui->tableWidget->setItem(i,25,new QTableWidgetItem((*ordetInfoTempList)[i].ShelfID));
        ui->tableWidget->setItem(i,26,new QTableWidgetItem((*ordetInfoTempList)[i].thisOrderNotPaid));
        ui->tableWidget->setItem(i,27,new QTableWidgetItem((*ordetInfoTempList)[i].customerCardMoneyBeforePay));
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
