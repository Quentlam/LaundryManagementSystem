#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "pulic.h"
#include <QSqlError>
#include <QFile>
#include "sqlmanager.h"


dlgLogin::dlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLogin)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
//    QFile cssFile;
//    auto cssFilePath = QCoreApplication::applicationDirPath();
//    cssFile.setFileName(cssFilePath + "/" + "style.css");
//    cssFile.open(QIODevice::ReadOnly);
//    auto css = cssFile.readAll();
//    qDebug() << css;
//  this->setStyleSheet(css);

}

dlgLogin::~dlgLogin()
{
    delete ui;
}


void dlgLogin::on_btnCancel_clicked()
{
    this->close();
}

void dlgLogin::on_btnLogin_clicked()
{
    QString account = ui->leAccount->text();
    QString password = ui->lePassword->text();
    auto loginStatus = sqlManager::createUserSql()->userLogin(account,password,ui->comboBox->currentText());

    if("所在分店" == ui->comboBox->currentText())
    {
        QMessageBox::information(nullptr,"警告","请在登陆前选择你所在的分店！");
        return;
    }
    if(loginStatus)//判断是否登录成功其实就是看这个sql有没有next，也就是有没有返回值，因为查询到了就会返回
    {
        QMessageBox::information(nullptr,"信息","登录成功！");
        this->close();
        QMessageBox::information(nullptr,"信息",QString("欢迎%1登录！").arg((*pulic::currentUser).Name));
        emit loginSuccess();
    }
    else
    {
        sqlManager::createUserSql()->getError();
        QMessageBox::information(nullptr,"信息","账号或者密码错误！");
    }

}

