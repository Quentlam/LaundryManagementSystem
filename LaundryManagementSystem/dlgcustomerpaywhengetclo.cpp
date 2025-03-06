#include "dlgcustomerpaywhengetclo.h"
#include "ui_dlgcustomerpaywhengetclo.h"
#include "customercost.h"
#include <QIntValidator>
#include <QMessageBox>


dlgCustomerPayWhenGetClo::dlgCustomerPayWhenGetClo(QWidget *parent, customerInfo customer, QString money)
    : QDialog(parent),
    currentCustomer(customer),
    thisOrderNotPaidMoney(money)
    , ui(new Ui::dlgCustomerPayWhenGetClo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->LACustomerNotPaidForThisOrder->setText(QString("客户本单欠缴：%1").arg(money));
    ui->LACustomerBeforeHaveNotPaid->setText(QString("提示：此客户一共欠缴%1元！").arg(currentCustomer.HaveNotPaidMoney));
    QDoubleValidator *intValidator = new QDoubleValidator(ui->LeInputMoney);
    ui->LeInputMoney->setValidator(intValidator);
}

dlgCustomerPayWhenGetClo::~dlgCustomerPayWhenGetClo()
{
    delete ui;
}

void dlgCustomerPayWhenGetClo::on_BtnEnter_clicked()
{
    auto money = ui->LeInputMoney->text().toDouble();
    if(!ui->RaCard->isChecked() && !ui->RaCash->isChecked() && !ui->RaTicket->isChecked() && !ui->RaWechat->isChecked())
    {
        QMessageBox::information(nullptr,"信息","请至少选择一个支付方式！");
        return;
    }
    if(money > thisOrderNotPaidMoney.toDouble())
    {
        QMessageBox::information(nullptr,"信息","客户此次缴费不能超过本单欠的钱！");
        return;
    }
    QString payWay;
    if(ui->RaCard->isChecked())
    {
        payWay = "充值卡支付";
    }
    if(ui->RaCash->isChecked())
    {
        payWay = "现金支付";
    }
    if(ui->RaTicket->isChecked())
    {
        payWay = "收券支付";
    }
    if(ui->RaWechat->isChecked())
    {
        payWay = "微信支付";
    }
    if(payWay == "充值卡支付" && money > this->currentCustomer.CardMoney)
    {
        QMessageBox::information(nullptr,"信息","客户卡余额不足！");
        return;
    }
    if(money < thisOrderNotPaidMoney.toDouble())
    {
        QMessageBox::information(nullptr,"信息","此订单未能缴清付款！");
        return;
    }



    customerCost coster = customerCost(this->currentCustomer);
    coster.customerPayForNotPaid(this->currentCustomer,money,payWay);

    accept();
}


void dlgCustomerPayWhenGetClo::on_BtnNumOne_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 1;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumTwo_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 2;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumFive_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 5;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumTen_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 10;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumTwenty_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 20;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumFifty_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 15;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumOneH_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 100;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnNumTwoH_clicked()
{
    auto Money = ui->LeInputMoney->text().toDouble();
    Money += 200;
    ui->LeInputMoney->setText(QString::number(Money));
}


void dlgCustomerPayWhenGetClo::on_BtnCancel_clicked()
{
    reject();
}

