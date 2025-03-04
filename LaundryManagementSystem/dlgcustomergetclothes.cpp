#include "dlgcustomergetclothes.h"
#include "ui_dlgcustomergetclothes.h"
#include "dlgcustomercostforhavenotpaid.h"
#include <QDebug>
#include "pulic.h"
#include "orderinfo.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QCheckBox>
#include <QScrollArea>
#include "dlgcustomergetclothes.h"
#include "sqlmanager.h"



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


void dlgCustomerGetClothes::keyPressEvent(QKeyEvent *event)//为了处理机枪，如果是输入数字，就要及时输入到输入框里
{
    NUMBER_KEY_EVENT(setFocus(text));
    if((Qt::Key::Key_Enter == event->key() && false == searchStatus) || (Qt::Key::Key_Return == event->key() && false == searchStatus))
    {
        QString text = ui->LEOrderID->text();
        qDebug() << "text:" << text;
        if(text.isNull() || text.size() < 10)
        {
            QMessageBox::information(nullptr,"警告","请输入正常的订单号！");
            return;
        }
        ui->LEOrderID->setText(text);
        search(text);
    }

}

void dlgCustomerGetClothes::search(QString OrderID)
{
    QString scannedData = OrderID; // 获取输入的文本
    ui->LEOrderID->setText(OrderID);
    qDebug() << "Scanned Data:" << OrderID; // 打印扫描的数据
    std::unique_ptr<OrderStatus> temp = sqlManager::createOrderSql()->selectOrderStatusByOrderID(OrderID);

    if((*temp).customerID.isNull())
    {
        QMessageBox::information(nullptr,"信息","找不到该订单！");
        sqlManager::createOrderSql()->getError();
        return;
    }
    if((*temp).shelfID.isNull() || (*temp).shelfID.size() < 2)
    {
        searchStatus = false;
        QMessageBox::information(nullptr,"信息","该订单已经取走全部衣服！");
        return;
    }
    QList<QString> ShelfCount = (*temp).shelfID.split(" ");
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
    ui->LACustomerName->setText(QString("客户姓名：%1").arg((*temp).customerName));
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
//        auto OrderStatus = sqlPtr->exec(QString("select HaveNotPaid from OrderLog where OrderID = '%1'").arg(ui->LEOrderID->text()));
//        if(false == OrderStatus)
//        {
//            QMessageBox::information(nullptr,"警告","请先输入订单号！");
//            return;
//        }
        //以下功能先不开发了
//        sqlPtr->next();
//        QString HaveNotPaid = sqlPtr->value(0).toString();
//        QString unKnow = HaveNotPaid.right(1);
//        bool isNumber = false;
//        unKnow.toInt(&isNumber);
//        if(isNumber)
//        {
//            auto answer = QMessageBox::question(nullptr,"欠缴信息","此订单未缴费！客户是否当场缴费？",QMessageBox::Yes | QMessageBox::No);
//            if(QMessageBox::Yes == answer)
//            {
//                sqlPtr->exec(QString("select CustomerID from OrderLog where OrderID = '%1'").arg(ui->LEOrderID->text()));//先用订单号把客户ID查出来
//                sqlPtr->next();
//                QString CustomerID = sqlPtr->value(0).toString();
//                sqlPtr->exec(QString("select * from Customer where ID = '%1'").arg(CustomerID));//再用客户ID查出客户信息
//                customerInfo customerInfoTemp;
//                while(sqlPtr->next())
//                {
//                    customerInfoTemp.ID = sqlPtr->value(0).toString();
//                    qDebug() << customerInfoTemp.ID;
//                    customerInfoTemp.Gender = sqlPtr->value(1).toString();
//                    qDebug() << customerInfoTemp.Gender;
//                    customerInfoTemp.Name = sqlPtr->value(2).toString();
//                    qDebug() << customerInfoTemp.Name;
//                    customerInfoTemp.Phone = sqlPtr->value(3).toString();
//                    qDebug() << customerInfoTemp.Phone;
//                    customerInfoTemp.CardID = sqlPtr->value(4).toString();
//                    qDebug() << customerInfoTemp.CardID;
//                    customerInfoTemp.Spend = sqlPtr->value(5).toDouble();
//                    qDebug() << customerInfoTemp.Spend;
//                    customerInfoTemp.Count = sqlPtr->value(6).toDouble();
//                    qDebug() << customerInfoTemp.Count;
//                    customerInfoTemp.CardType = sqlPtr->value(7).toString();
//                    qDebug() << customerInfoTemp.CardType;
//                    customerInfoTemp.HaveNotPaid = sqlPtr->value(8).toString();
//                    qDebug() << customerInfoTemp.HaveNotPaid;
//                    customerInfoTemp.HaveNotPaidMoney = sqlPtr->value(9).toString();
//                    qDebug() << customerInfoTemp.HaveNotPaidMoney;
//                    customerInfoTemp.CardMoney = sqlPtr->value(10).toDouble();
//                    qDebug() << customerInfoTemp.CardMoney;
//                    customerInfoTemp.Address = sqlPtr->value(11).toString();
//                    qDebug() << customerInfoTemp.Address;
//                    customerInfoTemp.Credit = sqlPtr->value(12).toString();
//                    qDebug() << customerInfoTemp.Credit;
//                    customerInfoTemp.Notes = sqlPtr->value(13).toString();
//                    qDebug() << customerInfoTemp.Notes;
//                }
//                dlgCustomerCostForHaveNotPaid dlgPayForNotPaid(nullptr,customerInfoTemp);
//                if(QDialog::Rejected == dlgPayForNotPaid.exec())
//                {
//                    QMessageBox::information(nullptr,"信息","缴费失败！");
//                    return;
//                }

//         }
//            if(QMessageBox::No == answer)
//            {
//                QMessageBox::information(nullptr,"信息","该客户此订单费用已经计入数据库！");
//            }
//        }
        QList<QCheckBox *> checkBoxes = this->findChildren<QCheckBox *>();
        QList<QString> checkedShelfs;
        QString checkedShelvesString;
        QString unCheckedShelfs;
        for (QCheckBox *checkBox : checkBoxes)
        {
            if (checkBox->isChecked())
            {
                checkedShelfs.push_back(checkBox->text());
                checkedShelvesString += checkBox->text() + " ";
            }
            else
            {
                unCheckedShelfs += checkBox->text() + " ";
            }
        }
        int Successcount = 0;
        auto db = sqlManager::createSqlManager()->getDB();
        auto sqlPtr = GET_SQL_POINTER;
        db->transaction();
        for(int i = 0 ; i < checkedShelfs.size() ; i ++ )
        {
             auto ShelfOccupy = sqlPtr->exec(QString("update Shelf%1 set ShelfStatus = '空' where ShelfID = '%2'; ").arg(checkedShelfs[i].at(4)).arg(checkedShelfs[i]));
             auto updateOrderStatus = sqlPtr->exec(QString("update OrderStatus set ShelfID = '%1' where OrderID = '%2'").arg(unCheckedShelfs).arg(ui->LEOrderID->text()));
             if(false == ShelfOccupy || false == updateOrderStatus)
             {
                 qDebug() << sqlPtr->lastError().text();
                 db->rollback();
                 return;
             }
             else
             {
                Successcount++;
             }
        }
        if(checkedShelfs.size() == Successcount)//如果全部取完，就要把留下一个A或者B
        {
            auto getAllClothes = sqlPtr->exec(QString("update OrderStatus set ShelfID = '%1' where OrderID = '%2'").arg(checkedShelvesString.right(1)).arg(ui->LEOrderID->text()));
            if(false == getAllClothes)
            {
                qDebug() << sqlPtr->lastError().text();
                db->rollback();
                return;
            }
        }
        db->commit();
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

void dlgCustomerGetClothes::setFocus(QString text)
{
    ui->LEOrderID->setFocus();
    ui->LEOrderID->setText(text);
}
