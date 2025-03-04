#include "dlgadduser.h"
#include "ui_dlgadduser.h"
#include "userinfo.h"
#include <QMessageBox>
#include "pulic.h"
#include "mainwindow.h"
#include "sqlmanager.h"

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
    temp.ID = ui->LeID->text();
    temp.Account = ui->leAccount->text();
    temp.Password = ui->lePassword->text();
    temp.Name = ui->leName->text();
    if(ui->radioButton->isChecked())
    temp.Authority = "员工";


    else if(ui->radioButton_2->isChecked())
    temp.Authority = "经理";


    if(temp.ID.isEmpty() || temp.Name.isEmpty() || temp.Password.isEmpty() || temp.Account.isEmpty() || temp.Authority.isEmpty())
        QMessageBox::information(nullptr,"警告","添加员工时，全部都不能为空！");
    else//先判断是否为空，如果不是就有以下查重
    {   
        auto accountOccupystatus = sqlManager::createUserSql()->selectUserByAccount(temp.Account);
        if(accountOccupystatus)
        {
            QMessageBox::information(nullptr,"警告","该账号已经被占用过！请重新输入要添加的账号！");
            return;
        }

        auto userHaveAccountOrnot = sqlManager::createUserSql()->selectUserByName(temp.Name);
        if(userHaveAccountOrnot)
        {
            QMessageBox::information(nullptr,"警告","该员工已经有账号了！");
            return;
        }
        sqlManager::createUserSql()->addUser(temp);
        QMessageBox::information(nullptr,"信息","添加成功！");
        addUserOperate.target = QString("添加了%1员工账号，员工编号为：%2").arg(temp.Name).arg(temp.ID);
        LaundryManagementLogger::record(addUserOperate);
        this->close();

    }
}
