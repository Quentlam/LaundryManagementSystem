#include "dlgupdateuser.h"
#include "ui_dlgupdateuser.h"

dlgUpdateUser::dlgUpdateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUpdateUser)
{
    ui->setupUi(this);
}

dlgUpdateUser::dlgUpdateUser(QWidget *parent, UserInformation Temp):
    QDialog(parent),
    userTemp(Temp),
    ui(new Ui::dlgUpdateUser)
{
    ui->setupUi(this);
    ui->LeID->setText(QString(userTemp.ID));
    ui->LeName->setText(QString(userTemp.Name));
    ui->LeAccount->setText(QString(userTemp.Account));
    ui->LePassword->setText(QString(userTemp.Password));
    if(userTemp.Authority == "经理")ui->CBAuthority->setCurrentIndex(1);
    else ui->CBAuthority->setCurrentIndex(0);



}

dlgUpdateUser::~dlgUpdateUser()
{
    delete ui;
}
