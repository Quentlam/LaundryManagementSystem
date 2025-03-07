﻿#include "dlgaddclothes.h"
#include "ui_dlgaddclothes.h"
#include <QMessageBox>
#include <clothesinfo.h>
#include "pulic.h"
#include "sqlmanager.h"


dlgAddClothes::dlgAddClothes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAddClothes)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    addClothesOperate.operate = QString("添加了新的衣服种类");
}

dlgAddClothes::~dlgAddClothes()
{
    delete ui;
}

int dlgAddClothes::exec()
{
    QDialog::exec();
    ui->LeID->clear();
    ui->LeName->clear();
    ui->LePrice->clear();
    ui->CBType->setCurrentIndex(0);
    return 1;
}


void dlgAddClothes::on_BtnEnter_clicked()
{
    if(ui->LeID->text().isEmpty() || ui->LeName->text().isEmpty() || ui->LePrice->text().isEmpty() || 0 == ui->CBType->currentIndex())
    {
        QMessageBox::information(nullptr,"警告","添加衣服种类时，要填写完整！");
        return;
    }
    clothesInfo temp;
    temp.ID = ui->LeID->text();
    temp.Name = ui->LeName->text();
    temp.Price = ui->LePrice->text().toInt();
    temp.Type = ui->CBType->currentText();
    temp.WashWay = ui->CBWashWay->currentText();

    bool status = sqlManager::createClothesSql()->addClothes(temp);
    if(true == status)
    {
        QMessageBox::information(nullptr,"信息","添加成功！");
        addClothesOperate.target = QString("添加了%1衣服,编号为:%2").arg(temp.Name).arg(temp.ID);
        LaundryManagementLogger::record(addClothesOperate);
        this->close();
    }
    else
    {
        sqlManager::createClothesSql()->getError();
        QMessageBox::information(nullptr,"信息","添加失败！");
    }

}

void dlgAddClothes::on_BtnCancel_clicked()
{
    this->close();
}
