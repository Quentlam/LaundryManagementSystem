#include "dlgaddcustomer.h"
#include "ui_dlgaddcustomer.h"
#include <QMessageBox>
#include <customerinfo.h>
#include "pulic.h"
#include "sqlmanager.h"


dlgAddCustomer::dlgAddCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAddCustomer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    addCustomerOperate.target = QString("客户");
    ui->LeHaveNotPaid->hide();

}

dlgAddCustomer::~dlgAddCustomer()
{
    delete ui;
}

int dlgAddCustomer::exec()
{
    QDialog::exec();
    ui->LeID->clear();
    ui->LeName->clear();
    ui->LePhone->clear();
    ui->LeCardID->clear();
    ui->LeAddress->clear();
    ui->LeCardMoney->clear();
    ui->LeHaveNotPaid->clear();
    ui->CBCredit->setCurrentIndex(0);
    ui->CBGender->setCurrentIndex(0);
    ui->CBCardType->setCurrentIndex(0);
    return 1;
}

void dlgAddCustomer::on_BtnEnter_clicked()
{
    if(ui->LeName->text().isEmpty() || ui->LePhone->text().isEmpty() ||ui->LeCardID->text().isEmpty() ||ui->LeCardMoney->text().isEmpty() || (!ui->RaHaveNotPaid->isChecked() && !ui->RaHavePaid->isChecked()))
    {
        QMessageBox::information(nullptr,"信息","添加客户要把必要信息填写完整");
        return;
    }


    customerInfo temp;
    temp.ID = ui->LeID->text();
    temp.Gender = ui->CBGender->currentText();
    temp.Name = ui->LeName->text();
    temp.Phone = ui->LePhone->text();
    temp.CardID = ui->LeCardID->text();
    temp.CardMoney = ui->LeCardMoney->text().toDouble();
    temp.CardType = ui->CBCardType->currentText();
    temp.Address = ui->LeAddress->text();
    temp.Credit = ui->CBCredit->currentText();
    if(ui->RaHaveNotPaid->isChecked())//如果点击了欠缴
    {
        if(ui->LeHaveNotPaid->text().isEmpty())//如果欠缴信息是空的！
        {
            QMessageBox::information(nullptr,"信息","添加欠缴信息时，要填写完整!");
            return;
        }
        bool isNumber;//如果不是空的，就要判断一下是不是数字，如果不是数字则返回
        ui->LeHaveNotPaid->text().toInt(&isNumber);
        if(!isNumber)
        {
            QMessageBox::information(nullptr,"信息","添加欠缴信息时，请填写数字!");
            return;
        }

        temp.HaveNotPaid = "欠缴";
        temp.HaveNotPaidMoney = ui->LeHaveNotPaid->text();

    }
    if(ui->RaHavePaid->isChecked())//如果点击了未欠缴
    {
        temp.HaveNotPaid = "未欠缴";
        temp.HaveNotPaidMoney = "0";
    }

    temp.Notes = ui->TeNotes->toPlainText();


    auto status = sqlManager::createCustomerSql()->addCustomer(temp);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","添加成功！");
        addCustomerOperate.operate = QString("添加%1客户，性别：%2电话：%3,卡号：%4,欠缴信息：%5,欠缴费：%6,住址：%7，信用：%8，充值金额：%9")
                .arg(temp.Name).arg(temp.Gender).arg(temp.Phone).arg(temp.CardID).arg(temp.HaveNotPaid).arg(temp.HaveNotPaidMoney).arg(temp.Address)
                .arg(temp.Credit).arg(temp.CardMoney);
        LaundryManagementLogger::record(addCustomerOperate);
    }
    else
    {
        sqlManager::createCustomerSql()->getError();
        QMessageBox::information(nullptr,"信息","添加失败！");
    }
    this->close();

}

void dlgAddCustomer::on_BtnCancel_clicked()
{
    this->close();
}

void dlgAddCustomer::on_RaHaveNotPaid_clicked()
{
     ui->LeHaveNotPaid->show();
}

void dlgAddCustomer::on_RaHavePaid_clicked()
{
     ui->LeHaveNotPaid->hide();
}
