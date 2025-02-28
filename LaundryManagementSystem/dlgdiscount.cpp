#include "dlgdiscount.h"
#include "ui_dlgdiscount.h"
#include <QMessageBox>

dlgDiscount::dlgDiscount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDiscount)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

dlgDiscount::~dlgDiscount()
{
    delete ui;
}

void dlgDiscount::setCurrentIndex(int index)
{
    ui->comboBox->setCurrentIndex(index);
}

void dlgDiscount::on_BtnEnter_clicked()
{
    Message = ui->comboBox->currentText();
    QMessageBox::information(nullptr,"信息","选择成功！");
    emit sentDiscount();
    this->close();
}

void dlgDiscount::on_BtnCancel_clicked()
{
    this->close();
}
