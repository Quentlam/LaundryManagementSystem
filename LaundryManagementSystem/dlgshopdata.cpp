#include "dlgshopdata.h"
#include "ui_dlgshopdata.h"
#include "pulic.h"
#include "shopdata.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
dlgShopData::dlgShopData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgShopData)
{
    ui->setupUi(this);
    reFresh();
}

dlgShopData::~dlgShopData()
{
    delete ui;
}

void dlgShopData::reFresh()
{
    std::unique_ptr<ShopData> temp = sqlManager::createUserSql()->showShopData();

    ui->LEShopID->setText((*temp).ShopID);
    ui->LEShopName->setText((*temp).ShopName);
    ui->LEShopAddress->setText((*temp).ShopAddress);
    ui->LESearchPhone->setText((*temp).SearchPhone);
    ui->LEComplaintPhone->setText((*temp).ComplaintsPhone);
    ui->PTAdvertisement->setPlainText((*temp).AdvertiseMent);
    ui->LEEveryShelfClothesCount->setText(QString::number(pulic::getInstance()->shelfCount));
}

void dlgShopData::on_BtnSave_clicked()
{
    ShopData shopData;
    shopData.ShopID = ui->LEShopID->text();
    shopData.ShopName = ui->LEShopName->text();
    shopData.SearchPhone = ui->LESearchPhone->text();
    shopData.ShopAddress = ui->LEShopAddress->text();
    shopData.AdvertiseMent = ui->PTAdvertisement->toPlainText();
    shopData.ComplaintsPhone = ui->LEComplaintPhone->text();

    auto status = sqlManager::createUserSql()->saveShopData(shopData);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        pulic::getInstance()->shelfCount = ui->LEEveryShelfClothesCount->text().toInt();//更新一下现在架号能挂几个衣服
        return;
    }
    if(false == status)
    {
        sqlManager::createUserSql()->getError();
        QMessageBox::information(nullptr,"信息","修改失败！");
        return;
    }
}
