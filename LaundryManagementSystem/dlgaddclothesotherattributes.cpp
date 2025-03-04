#include "dlgaddclothesotherattributes.h"
#include "ui_dlgaddclothesotherattributes.h"
#include "pulic.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "sqlmanager.h"


dlgAddClothesOtherAttributes::dlgAddClothesOtherAttributes(QWidget *parent,int chosenRadio) :
    QDialog(parent),
    chosenRadio(chosenRadio),
    ui(new Ui::dlgAddClothesOtherAttributes)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    operate.operate = "添加了衣服的其他属性";
    switch (chosenRadio)
    {
        case 1:
        {
        ui->LBText->setText("衣服颜色：");
        break;
        }
        case 2:
        {
        ui->LBText->setText("衣服瑕疵：");
        break;
        }
        case 3:
        {
        ui->LBText->setText("衣服品牌：");
        break;
        }
        case 4:
        {
        ui->LBText->setText("衣服特殊处理：");
        break;
        }
        case 5:
        {
        ui->LBText->setText("洗后效果：");
        break;
        }

    }


}

dlgAddClothesOtherAttributes::~dlgAddClothesOtherAttributes()
{
    delete ui;
}

int dlgAddClothesOtherAttributes::exec()
{
    QDialog::exec();
    ui->LeID->clear();
    ui->LeText->clear();
    return 1;
}

void dlgAddClothesOtherAttributes::on_BtnEnter_clicked()
{
    bool status = false;
    if(ui->LeText->text().isEmpty() || ui->LeID->text().isEmpty())
    {
        QMessageBox::information(nullptr,"警告","添加衣物其他属性时，要填写完整！");
        return;
    }
    clothesAttributeInfo clothesAttributeInfoTemp;
    clothesAttributeInfoTemp.ID = ui->LeID->text();
    clothesAttributeInfoTemp.Name = ui->LeText->text();
    clothesAttributeInfo::AttributeType type;
    switch(chosenRadio)
    {
         case 1://如果选的是衣服颜色
        {
            type = clothesAttributeInfo::AttributeType::Color;
            status = sqlManager::createClothesSql()->addClothesAttribute(clothesAttributeInfoTemp,type);
            operate.target = QString("添加了衣服颜色：%1,ID为：%2").arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
        }
        case 2://如果选的是衣服瑕疵
       {
            type = clothesAttributeInfo::AttributeType::Defect;
            status = sqlManager::createClothesSql()->addClothesAttribute(clothesAttributeInfoTemp,type);
            operate.target = QString("添加了衣服颜色：%1,ID为：%2").arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
       }
        case 3://如果选的是衣服品牌
       {
            type = clothesAttributeInfo::AttributeType::Brand;
            status = sqlManager::createClothesSql()->addClothesAttribute(clothesAttributeInfoTemp,type);
            operate.target = QString("添加了衣服颜色：%1,ID为：%2").arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
       }
        case 4://如果选的是特殊处理
       {
            type = clothesAttributeInfo::AttributeType::SpecialTreatment;
            status = sqlManager::createClothesSql()->addClothesAttribute(clothesAttributeInfoTemp,type);
            operate.target = QString("添加了衣服颜色：%1,ID为：%2").arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
       }
        case 5://如果选的是洗后效果
       {
            type = clothesAttributeInfo::AttributeType::WashingEffect;
            status = sqlManager::createClothesSql()->addClothesAttribute(clothesAttributeInfoTemp,type);
            operate.target = QString("添加了衣服颜色：%1,ID为：%2").arg(ui->LeText->text()).arg(ui->LeID->text());
            break;
       }

        default:
        {   
            QMessageBox::information(nullptr,"信息","你圈了个什么玩意儿？？？");
            break;
        }

    }

    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","添加成功！");
        LaundryManagementLogger::record(operate);
        this->close();
    }
    else
    {
        sqlManager::createClothesSql()->getError();
        QMessageBox::information(nullptr,"信息","添加失败！");
    }



}
