#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "pulic.h"
#include <QSqlError>
#include <QFile>
dlgLogin::dlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLogin)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    QFile cssFile;
    auto cssFilePath = QCoreApplication::applicationDirPath();
    cssFile.setFileName(cssFilePath + "/" + "style.css");
    cssFile.open(QIODevice::ReadOnly);
    auto css = cssFile.readAll();
    //qDebug() << css;

    this->setStyleSheet(css);
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
    auto ptr = pulic::getInstance();
    QString loginSql = QString("SELECT * FROM User WHERE Account = '%1' AND Password = '%2'").arg(ui->leAccount->text()).arg(ui->lePassword->text());
    ptr->sql->exec(loginSql);

    if("所在分店" == ui->comboBox->currentText())
    {
        QMessageBox::information(nullptr,"警告","请在登陆前选择你所在的分店！");
        return;
    }
    if(ptr->sql->next())//判断是否登录成功其实就是看这个sql有没有next，也就是有没有返回值，因为查询到了就会返回
    {
        QMessageBox::information(nullptr,"信息","登录成功！");
        this->close();
        pulic::currentUser->userInformation.ID = ptr->sql->value(0).toString();
        pulic::currentUser->userInformation.Account = ptr->sql->value(1).toString();
        pulic::currentUser->userInformation.Password = ptr->sql->value(2).toString();
        pulic::currentUser->userInformation.Name = ptr->sql->value(3).toString();
        pulic::currentUser->userInformation.Authority = ptr->sql->value(4).toString();
        pulic::currentAddress =  new QString(ui->comboBox->currentText());//选择分店之后，放到现在的分店里
        pulic::login = true;
        QMessageBox::information(nullptr,"信息",QString("欢迎%1登录！").arg(pulic::currentUser->userInformation.Name));
        emit loginSuccess();
    }
    else
    {
        QMessageBox::information(nullptr,"信息","账号或者密码错误！");
    }

    //qDebug() << loginSql;

    //qDebug() << ptr->getInstance()->sql->lastError().text();
}

