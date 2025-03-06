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
    sqlManager::createSqlManager();
    pulic::getInstance();
    login = std::make_unique<dlgLogin>();
    connect(login.get(),&dlgLogin::loginSuccess,this,&MainWindow::show);
    if(false == pulic::login)
    {

        login->show();
    }

    connect(timer,&QTimer::timeout,this,&MainWindow::reFresh);




}

MainWindow::~MainWindow()
{
    delete ui;
    delete Instance;
}

void MainWindow::reFresh()//获取当前用户的信息，并且填在主窗口
{
    ui->LbUser->setText(QString("用户:%1").arg((*pulic::currentUser).Name));
    ui->LbAddress->setText(QString("所在分店:%1").arg(pulic::currentAddress->data()));
    ui->LbAuthortiy->setText(QString("权限:%1").arg((*pulic::currentUser).Authority));
    ui->LbTime->setText(QString("当前时间:%1").arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::on_BtnAdd_clicked()
{
    this->hide();
    dlgMana = std::make_unique<dlgManage>();
    connect(dlgMana.get(),&dlgManage::backToMainWindow,this,&MainWindow::show);
    dlgMana->show();
}


void MainWindow::on_BtnGetClothes_clicked()
{
    this->hide();
    dlgGetClo = std::make_unique<dlgGetClothes>();
    connect(dlgGetClo.get(),&dlgGetClothes::backToMainWindow,this,&MainWindow::show);
    dlgGetClo->show();
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
    dlgRecharge =  std::make_unique<dlgCustomerRecharge>(nullptr,chargeCustomerTemp);
    dlgRecharge->exec();
}

void MainWindow::on_BtnSearch_clicked()
{
    this->hide();
    dlgSea = std::make_unique<dlgSearch>();
    connect(dlgSea.get(),&dlgSearch::backToMainWindow,this,&MainWindow::show);
    dlgSea->show();
}

void MainWindow::on_BtnCancel_clicked()
{
    auto answer = QMessageBox::question(nullptr,"信息","您确定要退出吗?",QMessageBox::Yes,QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        QMessageBox::information(nullptr,"信息",QString("感谢%1您的使用！").arg((*pulic::currentUser).Name));
        this->close();
        return;
    }
    if(answer == QMessageBox::No)
    {
        return;
    }
}
