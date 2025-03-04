#include "dlgcustomerrecharge.h"
#include "ui_dlgcustomerrecharge.h"

#include <QMessageBox>
#include <QMessageBox>




dlgCustomerRecharge::dlgCustomerRecharge(QWidget *parent) :
    QDialog(parent),
    currentCustomerCostOrRecharge(customerCost(customerInfo())),
    ui(new Ui::dlgCustomerRecharge)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    connect(&chosenCustomer,&dlgChoseCustomer::chosedSuccess,this,&dlgCustomerRecharge::chosenSuccess);
}

dlgCustomerRecharge::dlgCustomerRecharge(QWidget *parent, customerInfo currentCustomer):
    QDialog(parent),
    currentCustomer(currentCustomer),
    currentCustomerCostOrRecharge(customerCost(customerInfo())),
    ui(new Ui::dlgCustomerRecharge)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    connect(&chosenCustomer,&dlgChoseCustomer::chosedSuccess,this,&dlgCustomerRecharge::chosenSuccess);


}

dlgCustomerRecharge::~dlgCustomerRecharge()
{
    delete ui;
}

int dlgCustomerRecharge::exec()
{
    QDialog::exec();
    ui->LeName->setText(currentCustomer.Name);
    ui->LeGender->setText(currentCustomer.Gender);
    ui->LeSpend->setText(currentCustomer.Gender);
    ui->LePhone->setText(currentCustomer.Phone);
    ui->LeAddress->setText(currentCustomer.Address);
    ui->LeCredit->setText(currentCustomer.Credit);
    ui->LeDiscount->setText(currentCustomer.CardType);
    ui->LeCardID->setText(currentCustomer.CardID);
    ui->LeCardMoney->setText(QString::number(currentCustomer.CardMoney));
    return 1;
}

void dlgCustomerRecharge::on_BtnSelectCustomer_clicked()
{
    chosenCustomer.exec();
}

void dlgCustomerRecharge::chosenSuccess()
{
    ui->LeName->setText(chosenCustomer.chosedCustomer.Name);
    ui->LeSpend->setText(QString::number(chosenCustomer.chosedCustomer.Spend));
    ui->LePhone->setText(chosenCustomer.chosedCustomer.Phone);
    ui->LeCardID->setText(chosenCustomer.chosedCustomer.CardID);
    ui->LeCredit->setText(chosenCustomer.chosedCustomer.Credit);
    ui->LeGender->setText(chosenCustomer.chosedCustomer.Gender);
    ui->LeAddress->setText(chosenCustomer.chosedCustomer.Address);
    ui->LeDiscount->setText(chosenCustomer.chosedCustomer.CardType);
    ui->LeCardMoney->setText(QString::number(chosenCustomer.chosedCustomer.CardMoney));
    currentCustomer = chosenCustomer.chosedCustomer;
    currentCustomerCostOrRecharge.temp = chosenCustomer.chosedCustomer;

}



void dlgCustomerRecharge::on_BtnRecharge_clicked()//如果点击了充值按钮
{
    if(ui->LeName->text().isEmpty() || ui->LeCardID->text().isEmpty())
    {
        QMessageBox::information(nullptr,"警告！","请至少选择一个会员客户！");
        return;
    }
    bool isNumer;
    double rechargeMoney = ui->LeRecharge->text().toDouble(&isNumer);
    if(!isNumer)//如果不是Number
    {
        QMessageBox::information(nullptr,"警告！","只能够输入数字！");
        return;
    }

    if(rechargeMoney < 0)
    {
        QMessageBox::information(nullptr,"警告！","只能充值大于0的数字！");
        return;
    }




    auto rechargeStatus = QMessageBox::question(nullptr,"确认充值",QString("你确定要给此会员客户充值：%1元吗？").arg(ui->LeRecharge->text()),QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == rechargeStatus)
    {
        QMessageBox::information(nullptr,"信息","充值成功！");
        currentCustomerCostOrRecharge = customerCost(chosenCustomer.chosedCustomer);
        currentCustomerCostOrRecharge.cardRecharge(currentCustomerCostOrRecharge.temp,rechargeMoney);
        currentCustomer.CardMoney = currentCustomer.CardMoney + ui->LeRecharge->text().toDouble();//更新一下有多少钱
        this->close();
        emit rechargeSuccess();

    }





}

void dlgCustomerRecharge::on_BtnPayForHaveNotPay_clicked()
{
    if(currentCustomer.Name.isNull())
    {
        QMessageBox::warning(nullptr,"警告","至少选择一个客户！");
        return;
    }

    dlgPayForNotPay = new dlgCustomerCostForHaveNotPaid(nullptr,currentCustomer);
    connect(dlgPayForNotPay,&dlgCustomerCostForHaveNotPaid::PayForNotPaidSuccess,this,&dlgCustomerRecharge::updateForPayForNotPaid);
    dlgPayForNotPay->exec();
}

void dlgCustomerRecharge::updateForPayForNotPaid()
{
    currentCustomer = dlgPayForNotPay->customerTemp;
    ui->LeCardMoney->setText(QString::number(currentCustomer.CardMoney));
}

void dlgCustomerRecharge::on_LeRecharge_textChanged(const QString &arg1)
{
    ui->LeInput->setText(arg1);
}



void dlgCustomerRecharge::on_pushButton_clicked()
{
    dlggetClothes = new dlgCustomerGetClothes();
    dlggetClothes->exec();
}
