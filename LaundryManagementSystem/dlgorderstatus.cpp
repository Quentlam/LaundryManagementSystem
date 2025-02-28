#include "dlgorderstatus.h"
#include "ui_dlgorderstatus.h"
#include "pulic.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>



dlgOrderStatus::dlgOrderStatus(QWidget *parent) :
    QDialog(parent),
    currentOrderID("未选择"),
    ui(new Ui::dlgOrderStatus)
{
    ui->setupUi(this);
    ui->DateStart->hide();
    ui->DateEnd->hide();
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reFresh();
}

dlgOrderStatus::~dlgOrderStatus()
{
    delete ui;
}


void dlgOrderStatus::reFresh()
{
    ui->tableWidget->clear();
    OrdetStatusTempList.clear();
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select count(OrderID) from OrderStatus");
    sqlPtr->next();
    int orderCnt = sqlPtr->value(0).toInt();
    QList<QString> OrderStatusTittle;
    OrderStatusTittle << "订单流水号" << "订单状态" << "衣服收发情况" << "客户编号" << "客户姓名" << "架号";
    ui->LBCnt->setText(QString("显示订单总数：%1").arg(orderCnt));
    ui->tableWidget->setRowCount(orderCnt);
    ui->tableWidget->setColumnCount(OrderStatusTittle.size());
    for(int i = 0 ; i < OrderStatusTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(OrderStatusTittle[i]));

    OrderStatus temp;
    sqlPtr->exec("select * from OrderStatus");

    while(sqlPtr->next())
    {
        temp.orderID                = sqlPtr->value(0).toString();
        temp.orderStatus            = sqlPtr->value(1).toString();
        temp.ClothesSendStatus      = sqlPtr->value(2).toString();
        temp.customerID             = sqlPtr->value(3).toString();
        temp.customerName           = sqlPtr->value(4).toString();
        temp.shelfID                = sqlPtr->value(5).toString();
        OrdetStatusTempList.push_back(temp);
    }

    for(int i = 0 ; i < OrdetStatusTempList.size(); i ++)
    {
        ui->tableWidget->setItem(i,0 ,new QTableWidgetItem(OrdetStatusTempList[i].orderID));
        ui->tableWidget->setItem(i,1 ,new QTableWidgetItem(OrdetStatusTempList[i].orderStatus));
        if("未完成" == OrdetStatusTempList[i].orderStatus)
        {
            ui->tableWidget->item(i,1)->setForeground(QBrush(QColor("Red")));
        }

        ui->tableWidget->setItem(i,2 ,new QTableWidgetItem(OrdetStatusTempList[i].ClothesSendStatus));

        if("未发出" == OrdetStatusTempList[i].ClothesSendStatus)
        {
            ui->tableWidget->item(i,2)->setForeground(QBrush(QColor("Red")));
        }

        ui->tableWidget->setItem(i,3 ,new QTableWidgetItem(OrdetStatusTempList[i].customerID));
        ui->tableWidget->setItem(i,4 ,new QTableWidgetItem(OrdetStatusTempList[i].customerName));
        ui->tableWidget->setItem(i,5 ,new QTableWidgetItem(OrdetStatusTempList[i].shelfID));
    }
    ui->tableWidget->update();

}

void dlgOrderStatus::on_tableWidget_cellClicked(int row, int column)
{
    currentOrderID = ui->tableWidget->item(row,0)->text().right(10);
    ui->LBCurrentOrderID->setText(QString("选中的订单流水号：%1").arg(currentOrderID));
    ui->LBCurrentCustomerName->setText(QString("选中的客户姓名：%2").arg(ui->tableWidget->item(row,4)->text()));
}

void dlgOrderStatus::on_LeSearch_textChanged(const QString &arg1)
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

void dlgOrderStatus::on_RaDateSearch_clicked()
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



void dlgOrderStatus::on_BtnOrderNotFinished_clicked()
{
    if("未选择" == currentOrderID)
    {
        QMessageBox::information(nullptr,"信息","请选择要修改的订单！");
        return;
    }
    auto answer = QMessageBox::question(nullptr,"修改订单","你确定要给此订单修改为未完成吗？",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == answer)
    {
        return;
    }

    auto sqlPtr = pulic::getInstance()->sql;
    auto status = sqlPtr->exec(QString("UPDATE OrderStatus SET OrderStatus = '未完成' where OrderID = '%1';").arg(currentOrderID));
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        //ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("未完成");
        reFresh();
        return;
    }
    if(false == status)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastError().text();
        return;
    }



}

void dlgOrderStatus::on_BtnClothesNotBeSent_clicked()
{
    if("未选择" == currentOrderID)
    {
        QMessageBox::information(nullptr,"信息","请选择要修改的订单！");
        return;
    }
    auto answer = QMessageBox::question(nullptr,"修改订单","你确定要给此订单的衣物修改为未发出吗？",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == answer)
    {
        return;
    }

    auto sqlPtr = pulic::getInstance()->sql;
    auto status = sqlPtr->exec(QString("UPDATE OrderStatus SET ClothesSendStatus = '未发出' where OrderID = '%1';").arg(currentOrderID));
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        //ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("未发出");
        reFresh();
        return;
    }
    if(false == status)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastError().text();
        return;
    }

}

void dlgOrderStatus::on_BtnOrderFinished_clicked()
{
    if("未选择" == currentOrderID)
    {
        QMessageBox::information(nullptr,"信息","请选择要修改的订单！");
        return;
    }
    auto answer = QMessageBox::question(nullptr,"修改订单","你确定要给此订单修改为已完成吗？",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == answer)
    {
        return;
    }

    auto sqlPtr = pulic::getInstance()->sql;
    auto status = sqlPtr->exec(QString("UPDATE OrderStatus SET OrderStatus = '已完成' where OrderID = '%1';").arg(currentOrderID));
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        //ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("已完成");
        reFresh();
        return;
    }
    if(false == status)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastError().text();
        return;
    }
}

void dlgOrderStatus::on_BtnClothesSent_clicked()
{
    if("未选择" == currentOrderID)
    {
        QMessageBox::information(nullptr,"信息","请选择要修改的订单！");
        return;
    }
    auto answer = QMessageBox::question(nullptr,"修改订单","你确定要给此订单的衣物修改为已发出吗？",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == answer)
    {
        return;
    }

    auto sqlPtr = pulic::getInstance()->sql;
    auto db = pulic::getInstance()->getDB();
    db.transaction();
    auto status = sqlPtr->exec(QString("UPDATE OrderStatus SET ClothesSendStatus = '已发出' where OrderID = '%1';").arg(currentOrderID));
    auto shelfStatus = sqlPtr->exec(QString("UPDATE Shelf%1 SET ShelfStatus = '%2' where ShelfID = '%3';")//要把架号还原
    .arg(ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text().right(1))
    .arg("空").arg(ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text()));

    if(false == status || false == shelfStatus)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastError().text();
        db.rollback();
        return;
    }


    if(true == status && true == shelfStatus)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        db.commit();
        reFresh();
        return;
    }
}

void dlgOrderStatus::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0://如果是全部
        {
            reFresh();
            for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                  ui->tableWidget->setRowHidden(i,false);
            }

            break;
        }
        case 1://如果是已完成
        {
            for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
            {
                bool rowMatches = false;
                for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = ui->tableWidget->item(row, column);
                    if (item) {
                        if (item->text().contains("已完成")) {
                            rowMatches = true;
                            break;
                        }
                    }
                }
                // 根据是否匹配来显示或隐藏行
                ui->tableWidget->setRowHidden(row, !rowMatches);
            }
            break;
        }
        case 2://如果是未完成
        {
            for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
            {
                bool rowMatches = false;
                for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = ui->tableWidget->item(row, column);
                    if (item) {
                        if (item->text().contains("未完成")) {
                            rowMatches = true;
                            break;
                        }
                    }
                }
                // 根据是否匹配来显示或隐藏行
                ui->tableWidget->setRowHidden(row, !rowMatches);
            }
            break;
        }
        case 3://如果是已发出
        {
            for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
            {
                bool rowMatches = false;
                for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = ui->tableWidget->item(row, column);
                    if (item) {
                        if (item->text().contains("已发出")) {
                            rowMatches = true;
                            break;
                        }
                    }
                }
                // 根据是否匹配来显示或隐藏行
                ui->tableWidget->setRowHidden(row, !rowMatches);
            }
            break;
        }
        case 4://如果是未发出
        {
            for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
            {
                bool rowMatches = false;
                for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = ui->tableWidget->item(row, column);
                    if (item) {
                        if (item->text().contains("未发出")) {
                            rowMatches = true;
                            break;
                        }
                    }
                }
                // 根据是否匹配来显示或隐藏行
                ui->tableWidget->setRowHidden(row, !rowMatches);
            }
            break;
        }
    }

}
