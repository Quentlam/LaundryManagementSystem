#include "dlgorderstatus.h"
#include "ui_dlgorderstatus.h"
#include "pulic.h"
#include "sqlmanager.h"
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
    Ref<QList<OrderStatus>> OrdetStatusTempList = sqlManager::createOrderSql()->selectAllOrderStatus();
    ui->LBCnt->setText(QString("显示订单总数：%1").arg(OrdetStatusTempList->size()));
    ui->tableWidget->setRowCount(OrdetStatusTempList->size());
    ui->tableWidget->setColumnCount(OrderStatus::orderStatusTittle.size());
    for(int i = 0 ; i < OrderStatus::orderStatusTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(OrderStatus::orderStatusTittle[i]));



    for(int i = 0 ; i < OrdetStatusTempList->size(); i ++)
    {
        ui->tableWidget->setItem(i,0 ,new QTableWidgetItem((*OrdetStatusTempList)[i].orderID));
        ui->tableWidget->setItem(i,1 ,new QTableWidgetItem((*OrdetStatusTempList)[i].orderStatus));
        if(ORDER_NOT_FINISHED_STATUS == (*OrdetStatusTempList)[i].orderStatus)
        {
            ui->tableWidget->item(i,1)->setForeground(QBrush(QColor("Red")));
        }

        ui->tableWidget->setItem(i,2 ,new QTableWidgetItem((*OrdetStatusTempList)[i].ClothesSendStatus));

        if(CLOTHES_NOT_SEND == (*OrdetStatusTempList)[i].ClothesSendStatus)
        {
            ui->tableWidget->item(i,2)->setForeground(QBrush(QColor("Red")));
        }

        ui->tableWidget->setItem(i,3 ,new QTableWidgetItem((*OrdetStatusTempList)[i].customerID));
        ui->tableWidget->setItem(i,4 ,new QTableWidgetItem((*OrdetStatusTempList)[i].customerName));
        ui->tableWidget->setItem(i,5 ,new QTableWidgetItem((*OrdetStatusTempList)[i].shelfID));
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

    auto status = sqlManager::createOrderSql()->updateOrderStatusByOrderId(currentOrderID,ORDER_NOT_FINISHED_STATUS);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        reFresh();
        return;
    }
    if(false == status)
    {
        sqlManager::createOrderSql()->getError();
        QMessageBox::information(nullptr,"信息","修改失败！");
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

    auto status = sqlManager::createOrderSql()->updateClothesStatusByOrderId(currentOrderID,CLOTHES_NOT_SEND);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        reFresh();
        return;
    }
    if(false == status)
    {
        sqlManager::createOrderSql()->getError();
        QMessageBox::information(nullptr,"信息","修改失败！");
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
    auto status = sqlManager::createOrderSql()->updateOrderStatusByOrderId(currentOrderID,ORDER_FINISHED_STATUS);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        reFresh();
        return;
    }
    if(false == status)
    {
        sqlManager::createOrderSql()->getError();
        QMessageBox::information(nullptr,"信息","修改失败！");
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

    auto status = sqlManager::createOrderSql()->clothesHaveBeenSendOut(currentOrderID);
    if(false == status)// || false == shelfStatus)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        return;
    }

    if(true == status)// && true == shelfStatus)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        reFresh();
        return;
    }

}

void dlgOrderStatus::on_comboBox_currentIndexChanged(int index)
{
    QString type;
    switch (index)
    {
    case 0:
    break;
    case 1:
        type = ORDER_FINISHED_STATUS;
    break;
    case 2:
        type = ORDER_NOT_FINISHED_STATUS;
    break;
    case 3:
        type = CLOTHES_HAVE_BEEN_SEND;
    break;
    case 4:
        type = CLOTHES_NOT_SEND;
    break;
    }
    if(index != 0)
    {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
        {
            bool rowMatches = false;
            for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                QTableWidgetItem *item = ui->tableWidget->item(row, column);
                if (item) {
                    if (item->text().contains(type)) {
                        rowMatches = true;
                        break;
                    }
                }
            }
            // 根据是否匹配来显示或隐藏行
            ui->tableWidget->setRowHidden(row, !rowMatches);
        }
    }
    else
    {
        reFresh();
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
              ui->tableWidget->setRowHidden(i,false);
        }

    }


}
