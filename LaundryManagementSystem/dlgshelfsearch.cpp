#include "dlgshelfsearch.h"
#include "ui_dlgshelfsearch.h"
#include "pulic.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
dlgShelfSearch::dlgShelfSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgShelfSearch)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setRowCount(77);// 1000/13 = 76.9,也就是多了9个
    ui->tableWidget->setColumnCount(13);//有13列
    ui->RAASet->setChecked(true);
    reFresh();
}

dlgShelfSearch::~dlgShelfSearch()
{
    delete ui;
}

void dlgShelfSearch::reFresh()
{
    Ref<QList<shelfInfo>> Shelves;
    ui->tableWidget->clear();
    shelfNumber = "未选择";
    shelfSelected = false;
    if(ui->RAASet->isChecked())
    {
        Shelves = sqlManager::createShelfSql()->selectAllShelves(shelfInfo::shelfSet::A);
        ui->LBShelfSet->setText(QString("当前选择的架号系列：%1").arg("A"));
    }

    if(ui->RABSet->isChecked())
    {
        Shelves = sqlManager::createShelfSql()->selectAllShelves(shelfInfo::shelfSet::B);
        ui->LBShelfSet->setText(QString("当前选择的架号系列：%1").arg("B"));
    }

    int k = 0;
    for(int j = 0 ; j < 77 ; j ++)//第几行
    {
            for(int i = 0 ; i < 13 ; i ++)//第几列
            {
                if(k > 999)break;
                ui->tableWidget->setItem(j,i,new QTableWidgetItem((*Shelves)[k].ID));
                if("已上架" == (*Shelves)[k ++].status)
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

void dlgShelfSearch::on_tableWidget_cellClicked(int row, int column)
{
    if(nullptr == ui->tableWidget->item(row,column))return;

    shelfNumber = ui->tableWidget->item(row,column)->text();
    ui->LBShelfNumber->setText(QString("当前选择的架号：%1").arg(shelfNumber));
}

void dlgShelfSearch::on_RAASet_clicked()
{
    reFresh();
    shelfNumber = "未选择";
    ui->LBShelfNumber->setText(QString("当前选择的架号：未选择"));
    ui->tableWidget->clearSelection();
}

void dlgShelfSearch::on_RABSet_clicked()
{
    reFresh();
    shelfNumber = "未选择";
    ui->LBShelfNumber->setText(QString("当前选择的架号：未选择"));
    ui->tableWidget->clearSelection();
}

void dlgShelfSearch::on_BtnUp_clicked()
{
    if(255 == ui->tableWidget->currentItem()->foreground().color().red())//如果字体是红色的
    {
        QMessageBox::information(nullptr,"信息","该格架已使用！请更换！");
        return;
    }
    auto answer = QMessageBox::question(nullptr,"信息","您确定要将此架号上架？",QMessageBox::Yes,QMessageBox::No);
    QString set = ui->LBShelfSet->text().right(1);
    auto ShelfOccupy = sqlManager::createShelfSql()->setShelfOccupy(shelfNumber,ui->LBShelfSet->text().right(1));

    if(true == ShelfOccupy && QMessageBox::Yes == answer)
    {
        QMessageBox::information(nullptr,"信息","上架成功！");
        reFresh();
        return;
    }

    if(false == ShelfOccupy)
    {
        sqlManager::createShelfSql()->getError();
        QMessageBox::information(nullptr,"信息","上架失败！");
        return;
    }
}

void dlgShelfSearch::on_BtnDown_clicked()
{
    auto answer = QMessageBox::question(nullptr,"信息","您确定要将此架号下架？",QMessageBox::Yes,QMessageBox::No);
    auto ShelfOccupy = sqlManager::createShelfSql()->setShelfNotOccupy(shelfNumber,ui->LBShelfSet->text().right(1));
    if(true == ShelfOccupy && QMessageBox::Yes == answer)
    {
        QMessageBox::information(nullptr,"信息","下架成功！");
        reFresh();
        return;
    }

    if(false == ShelfOccupy)
    {
        sqlManager::createShelfSql()->getError();
        QMessageBox::information(nullptr,"信息","下架失败！");
        return;
    }

}
