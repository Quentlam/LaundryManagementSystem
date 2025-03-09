#include "swpage00.h"
#include "ui_swpage00.h"


swpage00::swpage00(QWidget *parent) :
    QDialog(parent),
    type(0),
    ui(new Ui::swpage00)
{
    ui->setupUi(this);

}

swpage00::~swpage00()
{
    delete ui;
}

void swpage00::on_BtnDry_clicked()
{
    type = 0;
    emit chosenType();
}

void swpage00::on_BtnWater_clicked()
{
    type = 1;
    emit chosenType();
}

void swpage00::on_BtnLeather_clicked()
{
    type = 2;
    emit chosenType();
}

void swpage00::on_BtnSingleIroning_clicked()
{
    type = 3;
    emit chosenType();
}

void swpage00::on_BtnOther_clicked()
{
    type = 4;
    emit chosenType();
}
