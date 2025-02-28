#include "dlgadduser.h"
#include "ui_dlgadduser.h"
#include "userinfo.h"
#include <QMessageBox>
#include "pulic.h"
#include "mainwindow.h"

dlgAddUser::dlgAddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAddUser)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    addUserOperate.operate = QString("新添加员工账号");

}

dlgAddUser::~dlgAddUser()
{
    delete ui;
}

int dlgAddUser::exec()
{
    QDialog::exec();
    ui->leName->clear();
    ui->leAccount->clear();
    ui->lePassword->clear();
    ui->LeID->clear();
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    return 1;
}

void dlgAddUser::on_BtnEnter_clicked()
{
    userInfo temp;
    temp.userInformation.ID = ui->LeID->text();
    temp.userInformation.Account = ui->leAccount->text();
    temp.userInformation.Password = ui->lePassword->text();
    temp.userInformation.Name = ui->leName->text();
    if(ui->radioButton->isChecked())
    temp.userInformation.Authority = "员工";


    else if(ui->radioButton_2->isChecked())
    temp.userInformation.Authority = "经理";


    if(temp.userInformation.ID.isEmpty() || temp.userInformation.Name.isEmpty() || temp.userInformation.Password.isEmpty() || temp.userInformation.Account.isEmpty() || temp.userInformation.Authority.isEmpty())
        QMessageBox::information(nullptr,"警告","添加员工时，全部都不能为空！");
    else//先判断是否为空，如果不是就有以下查重
    {   
        auto sql = pulic::getInstance()->sql;

        sql->exec(QString("select * from User where Account = '%1'").arg(temp.userInformation.Account));
        if(sql->next())
        {
        QMessageBox::information(nullptr,"警告","该账号已经被占用过！请重新输入要添加的账号！");
        return;
        }


        sql->exec(QString("select * from User where Name = '%1'").arg(temp.userInformation.Name));
        if(sql->next())
        {
        QMessageBox::information(nullptr,"警告","该员工已经有账号了！");
        return;
        }


        sql->exec(QString("insert into User values('%1','%2','%3','%4','%5');").
                  arg(temp.userInformation.ID).
                  arg(temp.userInformation.Account).
                  arg(temp.userInformation.Password).
                  arg(temp.userInformation.Name).
                  arg(temp.userInformation.Authority)
                      );
        QMessageBox::information(nullptr,"信息","添加成功！");
        addUserOperate.target = QString("添加了%1员工账号，员工编号为：%2").arg(temp.userInformation.Name).arg(temp.userInformation.ID);
        LaundryManagementLogger::record(addUserOperate);


        this->close();

    }
}
