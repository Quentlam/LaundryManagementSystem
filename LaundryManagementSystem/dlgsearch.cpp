#include "dlgsearch.h"
#include "ui_dlgsearch.h"



dlgSearch::dlgSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSearch)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->stackedWidget->addWidget(&dlgOrderSea);
    ui->stackedWidget->addWidget(&dlgOrderStatusSea);
    ui->stackedWidget->addWidget(&dlgShelfSea);
    dlgOrderSea.reFresh();
    dlgOrderStatusSea.reFresh();
}

dlgSearch::~dlgSearch()
{
    delete ui;
}

void dlgSearch::on_BtnBack_clicked()
{
    this->close();
    emit backToMainWindow();
}

void dlgSearch::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    QString text = item->text(column);
    ui->stackedWidget->show();
    if("订单基本参数" == text)//订单基本参数查询在第0页
    {
        dlgOrderSea.reFresh();
        ui->stackedWidget->setCurrentIndex(0);

    }
    if("订单状态" == text)//订单状态查询在第2页
    {
        dlgOrderStatusSea.reFresh();
        ui->stackedWidget->setCurrentIndex(1);
    }

    if("架号查询" == text)//订单状态查询在第2页
    {
        dlgShelfSea.reFresh();
        ui->stackedWidget->setCurrentIndex(2);
    }

}

void dlgSearch::show()
{
    dlgOrderSea.reFresh();
    dlgOrderStatusSea.reFresh();
    dlgShelfSea.reFresh();
    QWidget::show();
}
