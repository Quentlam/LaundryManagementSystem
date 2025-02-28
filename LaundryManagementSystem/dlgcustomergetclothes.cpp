#include "dlgcustomergetclothes.h"
#include "ui_dlgcustomergetclothes.h"
#include <QDebug>
#include "pulic.h"
#include "orderinfo.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QCheckBox>
#include <QScrollArea>

dlgCustomerGetClothes::dlgCustomerGetClothes(QWidget *parent) :
    QDialog(parent),
    searchStatus(false),
    ui(new Ui::dlgCustomerGetClothes)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    operate.operate = "客户取衣";
}

dlgCustomerGetClothes::~dlgCustomerGetClothes()
{
    delete ui;
}

void dlgCustomerGetClothes::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key::Key_Asterisk == event->key())
    {
        ui->LEOrderID->setFocus();
    }

    if((Qt::Key::Key_Enter == event->key() && false == searchStatus) || (Qt::Key::Key_Return == event->key() && false == searchStatus))
    {
        QString text = ui->LEOrderID->text();
        qDebug() << "text:" << text;
        if(text.isNull() || text.size() < 10)
        {
            QMessageBox::information(nullptr,"警告","请输入正常的订单号！");
            return;
        }

        if(text.contains('*'))
        {
            text.remove('*');
        }
        ui->LEOrderID->setText(text);
        search(text);
    }

}

void dlgCustomerGetClothes::search(QString OrderID)
{
    QString scannedData = OrderID; // 获取输入的文本
    if(OrderID.contains('*'))
    {
        OrderID.remove('*');
    }
    ui->LEOrderID->setText(OrderID);
    qDebug() << "Scanned Data:" << OrderID; // 打印扫描的数据
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec(QString("select * from OrderStatus where OrderID = '%1'").arg(OrderID));
    OrderStatus temp;
    while(sqlPtr->next())
    {
         temp.orderID = OrderID;
         temp.orderStatus       = sqlPtr->value(1).toString();
         temp.ClothesSendStatus = sqlPtr->value(2).toString();
         temp.customerID        = sqlPtr->value(3).toString();
         temp.customerName      = sqlPtr->value(4).toString();
         temp.shelfID           = sqlPtr->value(5).toString();
    }
    if(temp.customerID.isNull())
    {
        QMessageBox::information(nullptr,"信息","找不到该订单！");
        qDebug() << sqlPtr->lastError().text();
        return;
    }
    if(temp.shelfID.isNull() || temp.shelfID.size() < 2)
    {
        searchStatus = false;
        QMessageBox::information(nullptr,"信息","该订单已经取走全部衣服！");
        return;
    }
    QList<QString> ShelfCount = temp.shelfID.split(" ");
    ShelfCount.removeLast();
    for(int i = 0; i < ShelfCount.size() ; i++)
    {
        auto checkBox = new QCheckBox(ShelfCount[i],this);
        checkBox->setMinimumHeight(30);
        ui->verticalLayout->addWidget(checkBox);
        if(ShelfCount[i].contains("A"))
        {
            ui->PTASet->appendPlainText(ShelfCount[i]);
        }
        if(ShelfCount[i].contains("B"))
        {
            ui->PTBSet->appendPlainText(ShelfCount[i]);
        }
        //qDebug() << "已经检测到当前架号为：" << ShelfCount[i];
    }
    ui->LEOrderID->setEnabled(false);
    ui->LACustomerName->setText(QString("客户姓名：%1").arg(temp.customerName));
    ui->LAClothesCount->setText(QString("总架号数：%1").arg(ShelfCount.size()));
    ui->LACurrentOrderID->setText(QString("当前流水号：%1").arg(OrderID));
    searchStatus = true;
}


void dlgCustomerGetClothes::on_dlgCustomerGetClothes_finished(int result)
{
    //qDebug() << "该窗口已经关闭！";
    deleteLater();
}

void dlgCustomerGetClothes::on_BtnCancel_clicked()
{
    this->close();
}

void dlgCustomerGetClothes::on_BtnCusotmerGetClothes_clicked()
{
    if(false == searchStatus)
    {
        QMessageBox::information(nullptr,"警告","请先输入订单号！");
        return;
    }

    auto answer = QMessageBox::information(nullptr,"信息","您确定客户拿走了以下选中的架号的衣服了吗？",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == answer)
    {
        return;
    }
    if(QMessageBox::Yes == answer)
    {
        auto sqlPtr = pulic::getInstance()->sql;
        QList<QCheckBox *> checkBoxes = this->findChildren<QCheckBox *>();
        QList<QString> checkedShelfs;
        QString checkedShelvesString;
        QString unCheckedShelfs;
        for (QCheckBox *checkBox : checkBoxes)
        {
            if (checkBox->isChecked())
            {
                //qDebug() << checkBox->text() << "is checked";
                checkedShelfs.push_back(checkBox->text());
                checkedShelvesString += checkBox->text() + " ";
            }
            else
            {
                unCheckedShelfs += checkBox->text() + " ";
            }
        }
        int Successcount = 0;
        for(int i = 0 ; i < checkedShelfs.size() ; i ++ )
        {
             auto ShelfOccupy = sqlPtr->exec(QString("update Shelf%1 set ShelfStatus = '空' where ShelfID = '%2'; ").arg(checkedShelfs[i].at(4)).arg(checkedShelfs[i]));
             auto updateOrderStatus = sqlPtr->exec(QString("update OrderStatus set ShelfID = '%1' where OrderID = '%2'").arg(unCheckedShelfs).arg(ui->LEOrderID->text()));
             if(false == ShelfOccupy || false == updateOrderStatus)
             {
                 qDebug() << sqlPtr->lastError().text();
                 return;
             }
             else
             {
                Successcount++;
             }
        }
        QMessageBox::information(nullptr,"信息",QString("成功下架并取衣,架号数量为：%1！").arg(Successcount));
        operate.target = QString("客户已经取走衣服的架号为：%1").arg(checkedShelvesString);
        LaundryManagementLogger::record(operate);
        this->close();
    }

}

void dlgCustomerGetClothes::on_BtnSelectAll_clicked()
{
    QList<QCheckBox *> checkBoxes = this->findChildren<QCheckBox *>();
    for (QCheckBox *checkBox : checkBoxes)
    {
        checkBox->setChecked(true);
    }
}
