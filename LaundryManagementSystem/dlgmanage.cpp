#include "dlgmanage.h"
#include "ui_dlgmanage.h"

dlgManage::dlgManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgManage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->stackedWidget->hide();
    ui->stackedWidget->addWidget(&dlgadd);
    ui->stackedWidget->addWidget(&dlgshop);
}

dlgManage::~dlgManage()
{
    delete ui;
}

void dlgManage::on_BtnBack_clicked()
{
    this->close();
    emit backToMainWindow();
}



void dlgManage::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    QString text = item->text(column);
    ui->stackedWidget->show();
    if("基本数据管理" == text)//基本数据管理在第0页
    {
        dlgadd.reFresh(dlgadd.choseMode());
        ui->stackedWidget->setCurrentIndex(0);
    }

    if("店铺基本参数" == text)
    {
        dlgshop.reFresh();
        ui->stackedWidget->setCurrentIndex(1);
    }


}

void dlgManage::show()
{
    dlgadd.reFresh(dlgadd.choseMode());
    QDialog::show();
}


