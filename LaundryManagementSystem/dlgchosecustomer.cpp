#include "dlgchosecustomer.h"
#include "ui_dlgchosecustomer.h"
#include "pulic.h"
#include <QDebug>
dlgChoseCustomer::dlgChoseCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgChoseCustomer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
//设置模式
    ui->TWCustomer->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->TWCustomer->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->TWCustomer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWCustomer->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->TWCustomer->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮



//以下用于数据的回显
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   reFresh();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






}

dlgChoseCustomer::~dlgChoseCustomer()
{
    delete ui;
}

void dlgChoseCustomer::on_BtnEnter_clicked()
{
    if(-1 == ui->TWCustomer->currentRow())
    {
        return;
    }
    auto row = ui->TWCustomer->currentRow();
    chosedCustomer.ID = ui->TWCustomer->item(row,0)->text();
    chosedCustomer.Gender = ui->TWCustomer->item(row,1)->text();
    chosedCustomer.Name = ui->TWCustomer->item(row,2)->text();
    chosedCustomer.Phone = ui->TWCustomer->item(row,3)->text();
    chosedCustomer.CardID = ui->TWCustomer->item(row,4)->text();
    chosedCustomer.Spend = ui->TWCustomer->item(row,5)->text().toDouble();
    chosedCustomer.Count = ui->TWCustomer->item(row,6)->text().toDouble();
    chosedCustomer.CardType = ui->TWCustomer->item(row,7)->text();
    chosedCustomer.HaveNotPaid = ui->TWCustomer->item(row,8)->text();
    chosedCustomer.HaveNotPaidMoney = ui->TWCustomer->item(row,9)->text();
    chosedCustomer.CardMoney = ui->TWCustomer->item(row,10)->text().toDouble();//通过第9列来获取当前有多少钱
    chosedCustomer.Address = ui->TWCustomer->item(row,11)->text();//第11列是客户住址
    chosedCustomer.Credit = ui->TWCustomer->item(row,12)->text();//第12列是客户信用
    chosedCustomer.Notes = ui->TWCustomer->item(row,13)->text();//第13列是Notes
//    qDebug() <<  chosedCustomer.ID;
//    qDebug() <<  chosedCustomer.Gender;
//    qDebug() <<  chosedCustomer.Name;
//    qDebug() <<  chosedCustomer.Phone;
//    qDebug() <<  chosedCustomer.CardID;
//    qDebug() <<  chosedCustomer.Spend;
//    qDebug() <<  chosedCustomer.Count;
//    qDebug() <<  chosedCustomer.CardType;
//    qDebug() <<  chosedCustomer.HaveNotPaid;
//    qDebug() <<  chosedCustomer.HaveNotPaidMoney;
//    qDebug() <<  chosedCustomer.CardMoney;
//    qDebug() <<  chosedCustomer.Address;
//    qDebug() <<  chosedCustomer.Credit;
//    qDebug() <<  chosedCustomer.Notes;

    this->close();
    emit chosedSuccess();

}

void dlgChoseCustomer::on_BtnCancel_clicked()
{
    this->close();
}

void dlgChoseCustomer::on_LeSearch_textChanged(const QString &arg1)
{
    for (int row = 0; row < ui->TWCustomer->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->TWCustomer->columnCount(); ++column) {
            QTableWidgetItem *item = ui->TWCustomer->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text().contains(arg1,Qt::CaseInsensitive)) {
                    rowMatches = true;
                    break;
                }
            }
        }
        // 根据是否匹配来显示或隐藏行
        ui->TWCustomer->setRowHidden(row, !rowMatches);
    }
}


void dlgChoseCustomer::reFresh()
{
    auto sqlPtr = pulic::getInstance()->sql;
    ui->TWCustomer->clear();
    QList<QString> customerTittle;
    QList<customerInfo> customerListTemp;
    customerInfo customerTemp;
    customerTittle << "客户编号" << "客户性别"  << "客户姓名"  << "客户电话" << "客户卡号" << "消费额" << "消费次数" << "消费卡种类" << "欠缴情况" << "欠缴余额" << "客户卡剩余余额" << "客户住址" << "客户信用" << "备注";


    sqlPtr->exec("select count(ID) from Customer");
    sqlPtr->next();
    int Cnt = sqlPtr->value(0).toInt();
    ui->LbCount->setText(QString("当前总客户人数:%1").arg(Cnt));
    ui->TWCustomer->setRowCount(Cnt);
    ui->TWCustomer->setColumnCount(customerTittle.size());


    for(int i = 0; i < customerTittle.size() ; i ++)
    ui->TWCustomer->setHorizontalHeaderItem(i,new QTableWidgetItem (customerTittle[i]));//设置tittle


    sqlPtr->exec("select * from Customer");
    while(sqlPtr->next())//从数据库里把所有的客户查出来
    {
        customerTemp.ID = sqlPtr->value(0).toString();
        customerTemp.Gender = sqlPtr->value(1).toString();
        customerTemp.Name = sqlPtr->value(2).toString();
        customerTemp.Phone = sqlPtr->value(3).toString();
        customerTemp.CardID = sqlPtr->value(4).toString();
        customerTemp.Spend = sqlPtr->value(5).toDouble();
        customerTemp.Count = sqlPtr->value(6).toDouble();
        customerTemp.CardType = sqlPtr->value(7).toString();
        customerTemp.HaveNotPaid = sqlPtr->value(8).toString();
        customerTemp.HaveNotPaidMoney = sqlPtr->value(9).toString();
        customerTemp.CardMoney = sqlPtr->value(10).toDouble();
        customerTemp.Address = sqlPtr->value(11).toString();
        customerTemp.Credit = sqlPtr->value(12).toString();
        customerTemp.Notes = sqlPtr->value(13).toString();
        customerListTemp.push_back(customerTemp);
    }

    for(int i = 0; i < customerListTemp.size(); i ++ )//客户的数据回显
    {
        ui->TWCustomer->setItem(i,0,new QTableWidgetItem(customerListTemp[i].ID));
        ui->TWCustomer->setItem(i,1,new QTableWidgetItem(customerListTemp[i].Gender));
        ui->TWCustomer->setItem(i,2,new QTableWidgetItem(customerListTemp[i].Name));
        ui->TWCustomer->setItem(i,3,new QTableWidgetItem(customerListTemp[i].Phone));
        ui->TWCustomer->setItem(i,4,new QTableWidgetItem(customerListTemp[i].CardID));
        ui->TWCustomer->setItem(i,5,new QTableWidgetItem(QString::number(customerListTemp[i].Spend)));
        ui->TWCustomer->setItem(i,6,new QTableWidgetItem(QString::number(customerListTemp[i].Count)));
        ui->TWCustomer->setItem(i,7,new QTableWidgetItem(customerListTemp[i].CardType));
        ui->TWCustomer->setItem(i,8,new QTableWidgetItem(customerListTemp[i].HaveNotPaid));
        ui->TWCustomer->setItem(i,9,new QTableWidgetItem(customerListTemp[i].HaveNotPaidMoney));
        ui->TWCustomer->setItem(i,10,new QTableWidgetItem(QString::number(customerListTemp[i].CardMoney)));
        ui->TWCustomer->setItem(i,11,new QTableWidgetItem(customerListTemp[i].Address));
        ui->TWCustomer->setItem(i,12,new QTableWidgetItem(customerListTemp[i].Credit));
        ui->TWCustomer->setItem(i,13,new QTableWidgetItem(customerListTemp[i].Notes));
    }
     ui->TWCustomer->update();
}

int dlgChoseCustomer::exec()
{
    reFresh();
    QDialog::exec();
    reFresh();
    return 1;
}

void dlgChoseCustomer::show()
{
    reFresh();
    QWidget::show();
    reFresh();
}

void dlgChoseCustomer::updateChosenCustomerById(customerInfo& customer,QString id)
{
    auto sqlPtr = pulic::getInstance()->sql;

    sqlPtr->exec(QString("select * from Customer where ID = '%1'").arg(id));
    sqlPtr->next();

    customer.ID = sqlPtr->value(0).toString();
    customer.Gender = sqlPtr->value(1).toString();
    customer.Name = sqlPtr->value(2).toString();
    customer.Phone = sqlPtr->value(3).toString();
    customer.CardID = sqlPtr->value(4).toString();
    customer.Spend = sqlPtr->value(5).toDouble();
    customer.Count = sqlPtr->value(6).toDouble();
    customer.CardType = sqlPtr->value(7).toString();
    customer.HaveNotPaid = sqlPtr->value(8).toString();
    customer.HaveNotPaidMoney = sqlPtr->value(9).toString();
    customer.CardMoney = sqlPtr->value(10).toDouble();
    customer.Address = sqlPtr->value(11).toString();
    customer.Credit = sqlPtr->value(12).toString();
    customer.Notes = sqlPtr->value(13).toString();
}
