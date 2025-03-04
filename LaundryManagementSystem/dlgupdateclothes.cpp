#include "dlgupdateclothes.h"
#include "ui_dlgupdateclothes.h"
#include <QMessageBox>
#include "pulic.h"
#include "sqlmanager.h"


dlgUpdateClothes::dlgUpdateClothes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUpdateClothes)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

}

dlgUpdateClothes::dlgUpdateClothes(QWidget *parent, clothesInfo Temp):
    QDialog(parent),
    clothesTemp(Temp),
    ui(new Ui::dlgUpdateClothes)
{
    ui->setupUi(this);
    ui->LeID->setText(Temp.ID);
    ui->LeName->setText(Temp.Name);
    ui->LePrice->setText(QString::number(Temp.Price));
    updateClothesOperate.operate = QString("修改了衣服的数据");
    if("普通" ==clothesTemp.Type)
    {
        ui->CBType->setCurrentIndex(0);
    }
    if("高档" ==clothesTemp.Type)
    {
        ui->CBType->setCurrentIndex(1);
    }
    if("其他" ==clothesTemp.Type)
    {
        ui->CBType->setCurrentIndex(2);
    }


    if("水洗" ==clothesTemp.WashWay)
    {
        ui->CBWashWay->setCurrentIndex(0);
    }
    if("干洗" ==clothesTemp.WashWay)
    {
        ui->CBWashWay->setCurrentIndex(1);
    }
    if("皮衣" ==clothesTemp.WashWay)
    {
        ui->CBWashWay->setCurrentIndex(2);
    }
    if("单烫" ==clothesTemp.WashWay)
    {
        ui->CBWashWay->setCurrentIndex(3);
    }
    if("其他" ==clothesTemp.WashWay)
    {
        ui->CBWashWay->setCurrentIndex(4);
    }

}

dlgUpdateClothes::~dlgUpdateClothes()
{
    delete ui;
}

void dlgUpdateClothes::on_BtnEnter_clicked()
{
    clothesInfo currentClothesTemp;

    currentClothesTemp.ID = ui->LeID->text();
    currentClothesTemp.Price = ui->LePrice->text().toInt();
    currentClothesTemp.Type = ui->CBType->currentText();
    currentClothesTemp.Name = ui->LeName->text();
    currentClothesTemp.ID = ui->LeID->text();
    currentClothesTemp.WashWay = ui->CBWashWay->currentText();
    auto status = sqlManager::createClothesSql()->updateClothesById(currentClothesTemp,clothesTemp.ID);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        updateClothesOperate.target = QString("原先衣服ID：%1，原先衣服名称：%2，原先衣服价格：%3，原先衣服类型：%4，原先衣服处理方式：%5-----现在衣服ID：%6，现在衣服名称：%7，现在衣服价格：%8，现在衣服类型：%9，现在衣服处理方式：%10")
                .arg(clothesTemp.ID).arg(clothesTemp.Name).arg(clothesTemp.Price).arg(clothesTemp.Type).arg(clothesTemp.WashWay)
                .arg(currentClothesTemp.ID).arg(currentClothesTemp.Name).arg(currentClothesTemp.Price).arg(currentClothesTemp.Type).arg(currentClothesTemp.WashWay);
        LaundryManagementLogger::record(updateClothesOperate);
        this->close();
    }
    else
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        sqlManager::createClothesSql()->getError();
    }


}

void dlgUpdateClothes::on_BtnCancel_clicked()
{
    deleteLater();
    this->close();
}
