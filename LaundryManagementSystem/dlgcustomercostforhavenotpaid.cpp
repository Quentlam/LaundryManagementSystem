#include "dlgcustomercostforhavenotpaid.h"
#include "ui_dlgcustomercostforhavenotpaid.h"

#include <QMessageBox>
#include "pulic.h"


dlgCustomerCostForHaveNotPaid::dlgCustomerCostForHaveNotPaid(QWidget *parent,customerInfo customerTemp):
    QDialog(parent),
    customerTemp(customerTemp),
    ui(new Ui::dlgCustomerCostForHaveNotPaid),
    PayWay("未选择")
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    if("欠缴" == customerTemp.HaveNotPaid)
    {
         ui->LeHaveNotPaidMoney->setText(customerTemp.HaveNotPaidMoney);
    }
    else
    {
         ui->LeHaveNotPaidMoney->setText("该用户未欠缴！");
    }
    ui->LeHaveNotPaidMoney->setEnabled(false);

    ui->LeCardMoney->setText(QString::number(customerTemp.CardMoney));
    ui->LeCardMoney->setEnabled(false);
    //回显一下客户有多少钱，并且欠了多少钱


}

dlgCustomerCostForHaveNotPaid::~dlgCustomerCostForHaveNotPaid()
{
    delete ui;
}

void dlgCustomerCostForHaveNotPaid::on_BtnEnter_clicked()
{
    bool isNumber;
    double money = ui->LePay->text().toDouble(&isNumber);

    if(0.0 == customerTemp.HaveNotPaidMoney.toDouble())
    {
        QMessageBox::warning(nullptr,"警告","该用户未欠缴！");
        this->close();
        return;
    }
    if("未选择" == PayWay)
    {
        QMessageBox::warning(nullptr,"警告","至少选择一种缴费方式！");
        return;
    }

    if(!isNumber)
    {
        QMessageBox::warning(nullptr,"警告","缴费请只输入数字!");
        return;
    }

    if(money > customerTemp.HaveNotPaidMoney.toDouble())
    {
        QMessageBox::warning(nullptr,"警告","缴费不可超过欠缴费用!");
        return;
    }

    if("充值卡支付" == PayWay && customerTemp.CardMoney < customerTemp.HaveNotPaidMoney.toDouble())
    {
        QMessageBox::warning(nullptr,"警告","客户充值卡剩余的钱不够支付欠缴费！");
        return;
    }



    auto answer = QMessageBox::question(nullptr,"信息",QString("您确定要给%1,使用%2,缴费%3吗？").arg(customerTemp.Name).arg(PayWay).arg(money),QMessageBox::Yes,QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
         mCustomerCost = new customerCost(customerTemp);
         if(mCustomerCost->customerPayForNotPaid(customerTemp,money,PayWay))
         {
             QMessageBox::information(nullptr,"信息","缴费成功！");
             emit PayForNotPaidSuccess();
             this->close();
         }

         else
         {
             QMessageBox::information(nullptr,"信息","缴费失败！");
             return;
         }

    }


    else if(answer == QMessageBox::No)
    {
        QMessageBox::information(nullptr,"信息","缴费失败！");
        return;
    }






}

void dlgCustomerCostForHaveNotPaid::on_BtnCancel_clicked()
{
    this->close();
}

void dlgCustomerCostForHaveNotPaid::on_RaCard_clicked(bool checked)
{
    if(checked)
    PayWay = "充值卡支付";
    else PayWay = "未选择";
}

void dlgCustomerCostForHaveNotPaid::on_RaWechat_clicked(bool checked)
{
    if(checked)
    PayWay = "微信支付";
    else PayWay = "未选择";
}

void dlgCustomerCostForHaveNotPaid::on_RaTicket_clicked(bool checked)
{
    if(checked)
    PayWay = "用券支付";
    else PayWay = "未选择";
}

void dlgCustomerCostForHaveNotPaid::on_RaCash_clicked(bool checked)
{
    if(checked)
    PayWay = "现金支付";
    else PayWay = "未选择";
}
