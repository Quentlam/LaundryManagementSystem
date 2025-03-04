#include "dlgupadateuser.h"
#include "ui_dlgupadateuser.h"
#include "pulic.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "sqlmanager.h"

dlgUpadateUser::dlgUpadateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUpadateUser)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    updateUserOperate.operate = QString("修改了员工数据");
}

dlgUpadateUser::dlgUpadateUser(QWidget *parent, userInfo Temp):
    QDialog(parent),
    userTemp(Temp),
    ui(new Ui::dlgUpadateUser)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->LeID->setText(userTemp.ID);
    ui->LeName->setText(QString(userTemp.Name));
    ui->LeAccount->setText(QString(userTemp.Account));
    ui->LePassword->setText(QString(userTemp.Password));
    updateUserOperate.operate = QString("修改了员工数据");
}

dlgUpadateUser::~dlgUpadateUser()
{
    delete ui;
}

void dlgUpadateUser::on_BtnEnter_clicked()
{
    userInfo userTemp;
    userTemp.ID = ui->LeID->text();
    userTemp.Account = ui->LeAccount->text();
    userTemp.Password = ui->LePassword->text();
    userTemp.Name = ui->LeName->text();
    bool success = sqlManager::createUserSql()->updateUserById(userTemp,this->userTemp.ID);
    updateUserOperate.target = QString("原先员工ID：%1,原先员工账号：%2，原先员工密码：%3，原先员工名字：%4----现在员工ID：%5，现在员工账号：%6，现在员工密码：%7，现在员工名字：%8")
            .arg(userTemp.ID).arg(userTemp.Account).arg(userTemp.Password).arg(userTemp.Name).arg(ui->LeID->text()).arg(ui->LeAccount->text())
            .arg(ui->LePassword->text()).arg(ui->LeName->text());//修改用户的比较严重，所以多写了一点

    if(true == success)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        LaundryManagementLogger::record(updateUserOperate);
        this->close();
    }
    else
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
    }
}

void dlgUpadateUser::on_BtnCancel_clicked()
{
    deleteLater();
    this->close();
}
