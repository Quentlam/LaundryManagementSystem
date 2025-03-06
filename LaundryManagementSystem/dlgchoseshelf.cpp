#include "dlgchoseshelf.h"
#include "ui_dlgchoseshelf.h"
#include "pulic.h"

#include <qevent.h>
#include <qnamespace.h>
#include <QMessageBox>
#include <QDebug>
#include "sqlmanager.h"


dlgChoseShelf::dlgChoseShelf(QWidget *parent) :
    QDialog(parent),
    shelfNumber("未选择"),
    shelfSelected(false),
    ui(new Ui::dlgChoseShelf)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(77);// 1000/13 = 76.9,也就是多了9个
    ui->tableWidget->setColumnCount(13);//有13列
    ui->RAASet->setChecked(true);
}

dlgChoseShelf::~dlgChoseShelf()
{
    delete ui;
}

int dlgChoseShelf::exec()
{
    reFresh();
    QDialog::exec();
    return 1;
}

void dlgChoseShelf::reFresh()
{
    Ref<QList<shelfInfo>> shelvesList;
    shelfNumber = "未选择";
    shelfSelected = false;
    ui->LEShelfNumber->clear();
    if(ui->RAASet->isChecked())
    {
        shelvesList = sqlManager::createShelfSql()->selectAllShelves(shelfInfo::A);
        ui->LBShelfSet->setText(QString("当前选择的架号系列：A"));
    }

    if(ui->RABSet->isChecked())
    {
        shelvesList = sqlManager::createShelfSql()->selectAllShelves(shelfInfo::B);
        ui->LBShelfSet->setText(QString("当前选择的架号系列：B"));
    }



    int k = 0;
    for(int j = 0 ; j < 77 ; j ++)//第几行
    {
            for(int i = 0 ; i < 13 ; i ++)//第几列
            {
                if(k > 999)break;
                ui->tableWidget->setItem(j,i,new QTableWidgetItem((*shelvesList)[k].ID));
                if("已上架" == (*shelvesList)[k++].status)
                {
                  ui->tableWidget->item(j,i)->setForeground(QBrush(QColor("red")));
                }
                else
                {
                  ui->tableWidget->item(j,i)->setForeground(QBrush(QColor("black")));
                }
            }
    }

}

void dlgChoseShelf::on_RAASet_clicked()
{
    reFresh();
    shelfNumber = "未选择";
    shelfSelected = false;
    ui->LBShelfNumber->setText(QString("当前选择的架号：未选择"));
    ui->tableWidget->clearSelection();
}

void dlgChoseShelf::on_RABSet_clicked()
{
    reFresh();
    shelfNumber = "未选择";
    shelfSelected = false;
    ui->LBShelfNumber->setText(QString("当前选择的架号：未选择"));
    ui->tableWidget->clearSelection();
}

void dlgChoseShelf::on_tableWidget_cellClicked(int row, int column)
{
    if(nullptr == ui->tableWidget->item(row,column))return;

    shelfNumber = ui->tableWidget->item(row,column)->text();
    ui->LBShelfNumber->setText(QString("当前选择的架号：%1").arg(shelfNumber));

}

void dlgChoseShelf::on_BtnCancel_clicked()
{
    shelfNumber = "未选择";
    shelfSelected = false;
    this->close();
}

void dlgChoseShelf::on_BtnEnter_clicked()
{
    if(nullptr == ui->tableWidget->currentItem()->text())
    {
        shelfNumber = "未选择";
        this->close();
        return;
    }
    if(255 == ui->tableWidget->currentItem()->foreground().color().red())//如果字体是红色的
    {
        QMessageBox::information(nullptr,"信息","该格架已使用！请更换！");
        return;
    }

    shelfSelected = true;
    shelfNumber = ui->tableWidget->currentItem()->text();
    this->close();
}

void dlgChoseShelf::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key::Key_Enter && ui->LEShelfNumber->text().isNull())//如果不用输入框
    {
        if(nullptr == ui->tableWidget->currentItem()->text())
        {
            shelfNumber = "未选择";
            shelfSelected = false;
            this->close();
            return;
        }
        shelfSelected = true;
        shelfNumber = ui->tableWidget->currentItem()->text();
        this->close();
    }


    if(event->key() == Qt::Key::Key_Enter && !ui->LEShelfNumber->text().isNull())//如果用输入框
    {
        bool isNumber;
        int Number;
        Number = ui->LEShelfNumber->text().toInt(&isNumber);
        if(!isNumber)
        {
            QMessageBox::information(nullptr,"信息","请输入数字！");
            return;
        }
        if(Number > 999)
        {
            QMessageBox::information(nullptr,"信息","请输入小于999的数字！");
            return;
        }
        shelfNumber = QString("%1").arg(Number, 3, 10, QLatin1Char('0'));
        //qDebug() << "当前架号号码是：" << shelfNumber;
        shelfSelected = true;
        if(ui->RAASet->isChecked())
        {
            shelfNumber = shelfNumber + "-A";
        }
        else if (ui->RABSet->isChecked())
        {
            shelfNumber = shelfNumber + "-B";
        }
        this->close();
    }

    //qDebug() << "现在的架号是：" << shelfNumber;
}

void dlgChoseShelf::close()
{
    QDialog::close();
    emit choseShelfSuccess();
}
