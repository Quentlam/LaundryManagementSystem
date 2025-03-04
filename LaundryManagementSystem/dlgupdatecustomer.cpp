#include "dlgupdatecustomer.h"
#include "ui_dlgupdatecustomer.h"
#include "pulic.h"
#include <QMessageBox>


dlgUpdateCustomer::dlgUpdateCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUpdateCustomer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

}

dlgUpdateCustomer::dlgUpdateCustomer(QWidget *parent, customerInfo Temp):
    QDialog(parent),
    customerTemp(Temp),
    ui(new Ui::dlgUpdateCustomer)
{
    ui->setupUi(this);//用于数据的回显
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->LeID->setText(customerTemp.ID);
    if("男" == Temp.Gender)
    {
        ui->CBGender->setCurrentIndex(0);
    }
    else
    {
        ui->CBGender->setCurrentIndex(1);
    }
    ui->LeName->setText(QString(customerTemp.Name));
    ui->LePhone->setText(QString(customerTemp.Phone));
    ui->LeCardID->setText(QString(customerTemp.CardID));
    ui->LeSpend->setText(QString::number(customerTemp.Spend));
    ui->LeCount->setText(QString::number(customerTemp.Count));
    ui->LeAddress->setText(customerTemp.Address);
    if("良好" == customerTemp.Credit)
    {
        ui->CBCredit->setCurrentIndex(0);
    }
    else if("一般" == customerTemp.Credit)
    {
        ui->CBCredit->setCurrentIndex(1);
    }
    else if("较差" == customerTemp.Credit)
    {
        ui->CBCredit->setCurrentIndex(2);
    }

    if("未欠缴" == customerTemp.HaveNotPaid)
    {
        ui->LeHaveNotPaid->setText("0");
    }
    else
    {
        ui->LeHaveNotPaid->setText(customerTemp.HaveNotPaidMoney);
    }


    ui->LeCardMoney->setText(QString::number(customerTemp.CardMoney));
    ui->PTENotes->setPlainText(QString(customerTemp.Notes));

    updateCustomerOperate.operate = QString("修改了客户数据");

    if("1.0" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(0);
    }

    if("0.9" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(1);
    }

    if("0.8" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(2);
    }

    if("0.7" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(3);
    }

    if("0.6" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(4);
    }

    if("0.5" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(5);
    }

    if("0.4" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(6);
    }

    if("0.3" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(7);
    }

    if("0.2" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(8);
    }

    if("0.1" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(9);
    }

    if("0.0" == customerTemp.CardType)
    {
        ui->CBCardType->setCurrentIndex(10);
    }


}

dlgUpdateCustomer::~dlgUpdateCustomer()
{
    delete ui;
}

void dlgUpdateCustomer::on_BtnEnter_clicked()
{
    QString sql;
    bool isNumber;
    bool noPaid = false;
    ui->LeHaveNotPaid->text().toInt(&isNumber);//先见检查一下是不是数字，如果不是数字则返回
    if(!isNumber)
    {
        QMessageBox::information(nullptr,"信息","请在欠缴框里输入数字！");
        return;
    }
    customerInfo temp;
    temp.ID = ui->LeID->text();
    temp.Gender = ui->CBGender->currentText();
    temp.Name = ui->LeName->text();
    temp.Phone = ui->LePhone->text();
    temp.CardID = ui->LeCardID->text();
    temp.Spend = ui->LeSpend->text().toDouble(); // 假设 Spend 是 double 类型
    temp.Count = ui->LeCount->text().toInt(); // 假设 Count 是 int 类型
    temp.CardType = ui->CBCardType->currentText();
    temp.HaveNotPaid = "欠缴"; // 因为这个字段始终为 "欠缴"
    temp.HaveNotPaidMoney = ui->LeHaveNotPaid->text(); // 假设这是 double 类型
    temp.CardMoney = ui->LeCardMoney->text().toDouble(); // 假设 CardMoney 是 double 类型
    temp.Address = ui->LeAddress->text();
    temp.Credit = ui->CBCredit->currentText();
    temp.Notes = ui->PTENotes->toPlainText();
    bool status = false;
    if(0 != ui->LeHaveNotPaid->text().toInt())//如果输入框里不是0的话
    {
        noPaid = true;
        status = sqlManager::createCustomerSql()->updateCustomerById(temp,customerTemp.ID);
        if(false == status)
        {
            sqlManager::createCustomerSql()->getError();
        }
    }
    else//如果是0，则为未欠缴，并且写上欠缴0元
    {
        noPaid = false;
        //如果是0，则为未欠缴
        temp.HaveNotPaid = "未欠缴";
        status = sqlManager::createCustomerSql()->updateCustomerById(temp,customerTemp.ID);
    }
    ///////////////////////////////////////////以下是记录日志
    if(true == status)
    {
        if(true == noPaid)//如果欠缴了
        {
            QMessageBox::information(nullptr,"信息","修改成功！");
            updateCustomerOperate.target = QString("原先客户ID：%1,原先客户性别：%25,原先客户名字：%2，原先客户电话%3，原先客户卡号：%4，原先客户消费额：%5，原先客户消费次数：%6，原先卡种类：%7，原先欠缴情况：%8，原先欠缴费：%9，原先客户卡余额：%10，原先客户住址：%11，原先客户信用：%12----现在客户ID：%13,现在客户性别：%26,现在客户名字：%14，现在客户电话%15，现在客户卡号：%16，现在客户消费额：%17，现在客户消费次数：%18，现在卡种类：%19，现在欠缴情况：%20，现在欠缴费：%21，现在客户卡余额：%22,现在客户住址：%23，现在客户信用：%24")
                .arg(customerTemp.ID).arg(customerTemp.Name).arg(customerTemp.Phone).arg(customerTemp.CardID).arg(customerTemp.Spend).arg(customerTemp.Count).arg(customerTemp.CardType).arg(customerTemp.HaveNotPaid).arg(customerTemp.HaveNotPaidMoney).arg(customerTemp.CardMoney).arg(customerTemp.Address).arg(customerTemp.Credit)
                .arg(ui->LeID->text()).arg(ui->LeName->text()).arg(ui->LePhone->text()).arg(ui->LeCardID->text()).arg(ui->LeSpend->text()).arg(ui->LeCount->text()).arg(ui->CBCardType->currentText()).arg("欠缴").arg(ui->LeHaveNotPaid->text()).arg(ui->LeCardMoney->text()).arg(ui->LeAddress->text()).arg(ui->CBCredit->currentText())
                    .arg(customerTemp.Gender).arg(ui->CBGender->currentText());
            LaundryManagementLogger::record(updateCustomerOperate);
            this->close();
        }
        else//否则则未欠缴
        {
            QMessageBox::information(nullptr,"信息","修改成功！");
            updateCustomerOperate.target = QString("原先客户ID：%1,原先客户性别：%25,原先客户名字：%2，原先客户电话%3，原先客户卡号：%4，原先客户消费额：%5，原先客户消费次数：%6，原先卡种类：%7，原先欠缴情况：%8，原先欠缴费：%9，原先客户卡余额：%10，原先客户住址：%11，原先客户信用：%12----现在客户ID：%13,现在客户性别：%26,现在客户名字：%14，现在客户电话%15，现在客户卡号：%16，现在客户消费额：%17，现在客户消费次数：%18，现在卡种类：%19，现在欠缴情况：%20，现在欠缴费：%21，现在客户卡余额：%22,现在客户住址：%23，现在客户信用：%24")
                .arg(customerTemp.ID).arg(customerTemp.Name).arg(customerTemp.Phone).arg(customerTemp.CardID).arg(customerTemp.Spend).arg(customerTemp.Count).arg(customerTemp.CardType).arg(customerTemp.HaveNotPaid).arg(customerTemp.HaveNotPaidMoney).arg(customerTemp.CardMoney).arg(customerTemp.Address).arg(customerTemp.Credit)
                .arg(ui->LeID->text()).arg(ui->LeName->text()).arg(ui->LePhone->text()).arg(ui->LeCardID->text()).arg(ui->LeSpend->text()).arg(ui->LeCount->text()).arg(ui->CBCardType->currentText()).arg("未欠缴").arg("0").arg(ui->LeCardMoney->text()).arg(ui->LeAddress->text()).arg(ui->CBCredit->currentText()).arg(customerTemp.Gender).arg(ui->CBGender->currentText());
            LaundryManagementLogger::record(updateCustomerOperate);
            this->close();
        }

    }
    else
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
    }



}

void dlgUpdateCustomer::on_BtnCancel_clicked()
{
    deleteLater();
    this->close();
}
