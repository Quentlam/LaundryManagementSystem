#include "dlggetmoney.h"
#include "ui_dlggetmoney.h"
#include <QMessageBox>



dlgGetMoney::dlgGetMoney(QWidget *parent) :
    QDialog(parent),
    payWay("未选择"),
    ui(new Ui::dlgGetMoney)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

dlgGetMoney::~dlgGetMoney()
{
    delete ui;
}

void dlgGetMoney::on_BtnNumTwenty_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 20));
}

void dlgGetMoney::on_BtnNumOne_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 1));
}



void dlgGetMoney::on_BtnNumTwo_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 2));
}

void dlgGetMoney::on_BtnNumFive_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 5));
}



void dlgGetMoney::on_BtnNumTen_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 10));
}

void dlgGetMoney::on_BtnNumFifty_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 50));
}

void dlgGetMoney::on_BtnNumOneH_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 100));
}

void dlgGetMoney::on_BtnNumTwoH_clicked()
{
    auto t = ui->LeMoney->text().toInt();
    ui->LeMoney->setText(QString::number(t + 200));
}

void dlgGetMoney::on_BtnEnter_clicked()
{
    if(!ui->RaCash->isChecked() && !ui->RaTicket->isChecked() && !ui->RaWechat->isChecked() && !ui->RaCard->isChecked())
    {
        QMessageBox::information(nullptr,"信息","至少要选择一种支付方式！");
        return;
    }
    if(ui->RaCash->isChecked())
    {
        payWay = "现金支付";
    }
    if(ui->RaTicket->isChecked())
    {
        payWay = "用券支付";
    }
    if(ui->RaWechat->isChecked())
    {
        payWay = "微信支付";
    }


    if(ui->RaCard->isChecked())
    {
        payWay = "充值卡支付";
        ui->LeMoney->setText("0");
        ui->LeMoney->hide();
    }
    else
    {
        ui->LeMoney->show();
    }

    Money = ui->LeMoney->text().toDouble();
    this->close();
    emit finshGetMoney();
}

void dlgGetMoney::on_BtnCancel_clicked()
{
    this->close();
}

void dlgGetMoney::NormalCustomerMoneyFunc()
{
    ui->RaCard->hide();
}

void dlgGetMoney::VIPCustomerMoneyFunc()
{
    ui->RaCard->show();
}

void dlgGetMoney::on_RaCard_clicked()
{
    ui->LeMoney->setText("0");
    ui->LeMoney->hide();
}

void dlgGetMoney::on_RaWechat_clicked()
{
    ui->LeMoney->show();
}

void dlgGetMoney::on_RaTicket_clicked()
{
    ui->LeMoney->show();
}

void dlgGetMoney::on_RaCash_clicked()
{
    ui->LeMoney->show();
}
