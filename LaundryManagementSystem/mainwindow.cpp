#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pulic.h"
#include <QDateTime>
#include <QMessageBox>



MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    if(false == pulic::login)dlgLogin.show();

    connect(&dlgGetClo,&dlgGetClothes::backToMainWindow,this,&MainWindow::show);
    connect(&dlgLogin,&dlgLogin::loginSuccess,this,&MainWindow::show);
    connect(&dlgMana,&dlgManage::backToMainWindow,this,&MainWindow::show);
    connect(timer,&QTimer::timeout,this,&MainWindow::reFresh);
    connect(&dlgSea,&dlgSearch::backToMainWindow,this,&MainWindow::show);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reFresh()//获取当前用户的信息，并且填在主窗口
{
    ui->LbUser->setText(QString("用户:%1").arg(pulic::currentUser->userInformation.Name));
    ui->LbAddress->setText(QString("所在分店:%1").arg(pulic::currentAddress->data()));
    ui->LbAuthortiy->setText(QString("权限:%1").arg(pulic::currentUser->userInformation.Authority));
    ui->LbTime->setText(QString("当前时间:%1").arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::on_BtnAdd_clicked()
{
    this->hide();
    dlgMana.show();
}


void MainWindow::on_BtnGetClothes_clicked()
{
    this->hide();
    dlgGetClo.show();
}

void MainWindow::show()
{
    QWidget::show();
    timer->start(1000);
    reFresh();
}


void MainWindow::on_BtnRecharge_clicked()
{
    customerInfo chargeCustomerTemp;
    dlgRecharge = new dlgCustomerRecharge(nullptr,chargeCustomerTemp);
    dlgRecharge->exec();
}

void MainWindow::on_BtnSearch_clicked()
{
    this->hide();
    dlgSea.show();
}

void MainWindow::on_BtnCancel_clicked()
{
    auto answer = QMessageBox::question(nullptr,"信息","您确定要退出吗?",QMessageBox::Yes,QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        QMessageBox::information(nullptr,"信息",QString("感谢%1您的使用！").arg(pulic::currentUser->userInformation.Name));
        this->close();
        return;
    }
    if(answer == QMessageBox::No)
    {
        return;
    }
}
