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
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select * from ShopData");
    ShopData temp;
    while(sqlPtr->next())
    {
        temp.ShopID          = sqlPtr->value(0).toString();
        temp.ShopName        = sqlPtr->value(1).toString();
        temp.ShopAddress     = sqlPtr->value(2).toString();
        temp.SearchPhone     = sqlPtr->value(3).toString();
        temp.ComplaintsPhone = sqlPtr->value(4).toString();
        temp.AdvertiseMent   = sqlPtr->value(5).toString();
    }
    sqlPtr->exec("select * from ShelfStatus");
    sqlPtr->next();
    QString ShlefCount = sqlPtr->value(0).toString();
    ui->LEShopID->setText(temp.ShopID);
    ui->LEShopName->setText(temp.ShopName);
    ui->LEShopAddress->setText(temp.ShopAddress);
    ui->LESearchPhone->setText(temp.SearchPhone);
    ui->LEComplaintPhone->setText(temp.ComplaintsPhone);
    ui->PTAdvertisement->setPlainText(temp.AdvertiseMent);
    ui->LEEveryShelfClothesCount->setText(ShlefCount);
}

void dlgShopData::on_BtnSave_clicked()
{
    auto sqlPtr = pulic::getInstance()->sql;
    auto status = sqlPtr->exec(QString("UPDATE ShopData SET ShopID = '%1',ShopName = '%2',ShopAddress = '%3',SearchPhone = '%4',ComplaintsPhone = '%5',Advertisement = '%6'")
                 .arg(ui->LEShopID->text()).arg(ui->LEShopName->text()).arg(ui->LEShopAddress->text()).arg(ui->LESearchPhone->text())
                 .arg(ui->LEComplaintPhone->text()).arg(ui->PTAdvertisement->toPlainText())
                 );
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        pulic::getInstance()->shelfCount = ui->LEEveryShelfClothesCount->text().toInt();//更新一下现在架号能挂几个衣服
        return;
    }
    if(false == status)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastError().text();
        return;
    }
}
