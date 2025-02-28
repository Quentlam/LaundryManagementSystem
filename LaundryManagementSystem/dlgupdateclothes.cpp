#include "dlgupdateclothes.h"
#include "ui_dlgupdateclothes.h"
#include <QMessageBox>
#include "pulic.h"



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


}

dlgUpdateClothes::~dlgUpdateClothes()
{
    delete ui;
}

void dlgUpdateClothes::on_BtnEnter_clicked()
{
    auto sqlPtr = pulic::getInstance()->sql;
    QString sql = QString("UPDATE Clothes SET ID = '%1',Name = '%2',Price = %3,Type = '%4' where ID = '%5'")
            .arg(ui->LeID->text()).arg(ui->LeName->text()).arg(ui->LePrice->text()).arg(ui->CBType->currentText()).arg(clothesTemp.ID);

    auto status = sqlPtr->exec(sql);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        updateClothesOperate.target = QString("原先衣服ID：%1，原先衣服名称：%2，原先衣服价格：%3，原先衣服类型：%4-----现在衣服ID：%5，现在衣服名称：%6，现在衣服价格：%7，现在衣服类型：%8")
                .arg(clothesTemp.ID).arg(clothesTemp.Name).arg(clothesTemp.Price).arg(clothesTemp.Type)
                .arg(ui->LeID->text()).arg(ui->LeName->text()).arg(ui->LePrice->text()).arg(ui->CBType->currentText());
        LaundryManagementLogger::record(updateClothesOperate);
        this->close();
    }
    else
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
    }


}
