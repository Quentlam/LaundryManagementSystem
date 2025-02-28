#include "dlgupdateclothesotherattributes.h"
#include "ui_dlgupdateclothesotherattributes.h"
#include "pulic.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>


dlgUpdateClothesOtherAttributes::dlgUpdateClothesOtherAttributes(QWidget *parent,int chosenRadio,QString currentID,QString currentText) :
    QDialog(parent),
    chosenRadio(chosenRadio),
    currentID(currentID),
    currentText(currentText),
    ui(new Ui::dlgUpdateClothesOtherAttributes)
{
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    operate.operate = "修改了衣服的其他属性";
    switch (chosenRadio)
    {
        case 1:
        {
        ui->LbText->setText("衣服颜色：");
        break;
        }
        case 2:
        {
        ui->LbText->setText("衣服瑕疵：");
        break;
        }
        case 3:
        {
        ui->LbText->setText("衣服品牌：");
        break;
        }
        case 4:
        {
        ui->LbText->setText("衣服特殊处理：");
        break;
        }
        case 5:
        {
        ui->LbText->setText("洗后效果：");
        break;
        }

    }
    ui->LeID->setText(currentID);
    ui->LeText->setText(currentText);


}

dlgUpdateClothesOtherAttributes::~dlgUpdateClothesOtherAttributes()
{
    delete ui;
}

void dlgUpdateClothesOtherAttributes::on_BtnEnter_clicked()
{
    auto sqlPtr = pulic::getInstance()->sql;
    bool status = false;
    if(ui->LeID->text().isEmpty() || ui->LeText->text().isEmpty())
    {
        QMessageBox::information(nullptr,"警告","ID或者属性不可为空！");
        return;
    }




    switch(chosenRadio)
    {
         case 1://如果选的是衣服颜色
        {
            status = sqlPtr->exec(QString("update ClothesColor set ID = '%1',Color = '%2' where ID = '%3';").arg(ui->LeID->text()).arg(ui->LeText->text()).arg(currentID));
            operate.target = QString("修改了衣服颜色，原本是：%1,ID为%2,现在是：%3,ID为%4").arg(currentText).arg(currentID).arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
        }
        case 2://如果选的是衣服瑕疵
       {
           status = sqlPtr->exec(QString("update ClothesDefect set ID = '%1',Defect = '%2' where ID = '%3';").arg(ui->LeID->text()).arg(ui->LeText->text()).arg(currentID));
           operate.target = QString("修改了衣服瑕疵，原本是：%1,ID为%2,现在是：%3,ID为%4").arg(currentText).arg(currentID).arg(ui->LeText->text()).arg(ui->LeID->text());
           break;
       }
        case 3://如果选的是衣服品牌
       {
           status = sqlPtr->exec(QString("update ClothesBrand set ID = '%1',Brand = '%2' where ID = '%3';").arg(ui->LeID->text()).arg(ui->LeText->text()).arg(currentID));
           operate.target = QString("修改了衣服品牌，原本是：%1,ID为%2,现在是：%3,ID为%4").arg(currentText).arg(currentID).arg(ui->LeText->text()).arg(ui->LeID->text());
           break;
       }
        case 4://如果选的是特殊处理
       {
           status = sqlPtr->exec(QString("update SpecialTreatment set ID = '%1',Treatment = '%2' where ID = '%3';").arg(ui->LeID->text()).arg(ui->LeText->text()).arg(currentID));
           operate.target = QString("修改了特殊处理，原本是：%1,ID为%2,现在是：%3,ID为%4").arg(currentText).arg(currentID).arg(ui->LeText->text()).arg(ui->LeID->text());
           break;
       }
        case 5://如果选的是洗后效果
       {
           status = sqlPtr->exec(QString("update WashingEffect set ID = '%1',Effect = '%2' where ID = '%3';").arg(ui->LeID->text()).arg(ui->LeText->text()).arg(currentID));
           operate.target = QString("修改了洗后效果，原本是：%1,ID为%2,现在是：%3,ID为%4").arg(currentText).arg(currentID).arg(ui->LeText->text()).arg(ui->LeID->text());
           break;
       }
        default:
        {
            QMessageBox::information(nullptr,"信息","你圈了个什么玩意儿？？？");
            break;
        }

    }



    if(status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        LaundryManagementLogger::record(operate);
        this->close();
    }
    else
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        qDebug() << sqlPtr->lastQuery();
        qDebug() << sqlPtr->lastError().text();

    }



}
