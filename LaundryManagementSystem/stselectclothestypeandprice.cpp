#include "stselectclothestypeandprice.h"
#include "ui_stselectclothestypeandprice.h"
#include "pulic.h"
#include "clothesinfo.h"
#include <QMessageBox>
#include <QDebug>


STSelectClothesTypeAndPrice::STSelectClothesTypeAndPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STSelectClothesTypeAndPrice)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->tableWidget->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮
}

STSelectClothesTypeAndPrice::~STSelectClothesTypeAndPrice()
{
    delete ui;
}



bool STSelectClothesTypeAndPrice::searchClothes(QString text)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text() == (text)) {
                    rowMatches = true;
                    Name = ui->tableWidget->item(row,1)->text();
                    Price = ui->tableWidget->item(row,2)->text();
                    emit chosenClothesType();
                    return true;
                }
            }
        }
        // 根据是否匹配来发送信号
    }
    return false;
}

void STSelectClothesTypeAndPrice::choseClothes(int type)
{
    ui->tableWidget->clear();
    std::unique_ptr<QList<clothesInfo>> dryClenClothesTempList = sqlManager::createClothesSql()->showClothesInfo(clothesInfo::WashWayType::dryClean);
    std::unique_ptr<QList<clothesInfo>> washClothesTempList = sqlManager::createClothesSql()->showClothesInfo(clothesInfo::WashWayType::wash);
    std::unique_ptr<QList<clothesInfo>> leatherCoatClothesTempList = sqlManager::createClothesSql()->showClothesInfo(clothesInfo::WashWayType::leatherCoat);
    std::unique_ptr<QList<clothesInfo>> singleIroningClothesTempList = sqlManager::createClothesSql()->showClothesInfo(clothesInfo::WashWayType::singleIroning);
    std::unique_ptr<QList<clothesInfo>> otherClothesTempList = sqlManager::createClothesSql()->showClothesInfo(clothesInfo::WashWayType::other);
    int size = dryClenClothesTempList->size() + washClothesTempList->size() + leatherCoatClothesTempList->size() + singleIroningClothesTempList->size() + otherClothesTempList->size();
    ui->tableWidget->setColumnCount(clothesInfo::clothesTittle.size() - 1);
    ui->tableWidget->setRowCount(size + 5);
    for(int i = 0 ; i < clothesInfo::clothesTittle.size() - 1; i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesInfo::clothesTittle[i]));//设置tittle


    int count = 0;
    int currentRow = 0;
    ui->tableWidget->setItem(count ++,0,new QTableWidgetItem("干洗"));
    currentRow = count + dryClenClothesTempList->size();
    for(int i = 0;count < currentRow; i ++,count ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(count,0,new QTableWidgetItem((*dryClenClothesTempList)[i].ID));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem((*dryClenClothesTempList)[i].Name));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString::number((*dryClenClothesTempList)[i].Price)));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem((*dryClenClothesTempList)[i].Type));
    }



    ui->tableWidget->setItem(count ++,0,new QTableWidgetItem("水洗"));
    currentRow = count + washClothesTempList->size();
    for(int i = 0;count < currentRow; i ++,count ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(count,0,new QTableWidgetItem((*washClothesTempList)[i].ID));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem((*washClothesTempList)[i].Name));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString::number((*washClothesTempList)[i].Price)));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem((*washClothesTempList)[i].Type));
    }

    ui->tableWidget->setItem(count ++,0,new QTableWidgetItem("皮衣"));
    currentRow = count + leatherCoatClothesTempList->size();
    for(int i = 0;count < currentRow; i ++,count ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(count,0,new QTableWidgetItem((*leatherCoatClothesTempList)[i].ID));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem((*leatherCoatClothesTempList)[i].Name));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString::number((*leatherCoatClothesTempList)[i].Price)));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem((*leatherCoatClothesTempList)[i].Type));
    }

    ui->tableWidget->setItem(count ++,0,new QTableWidgetItem("单烫"));
    currentRow = count + singleIroningClothesTempList->size();
    for(int i = 0;count < currentRow; i ++,count ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(count,0,new QTableWidgetItem((*singleIroningClothesTempList)[i].ID));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem((*singleIroningClothesTempList)[i].Name));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString::number((*singleIroningClothesTempList)[i].Price)));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem((*singleIroningClothesTempList)[i].Type));
    }

    ui->tableWidget->setItem(count ++,0,new QTableWidgetItem("其他"));
    currentRow = count + otherClothesTempList->size();
    for(int i = 0;count < currentRow; i ++,count ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(count,0,new QTableWidgetItem((*otherClothesTempList)[i].ID));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem((*otherClothesTempList)[i].Name));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString::number((*otherClothesTempList)[i].Price)));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem((*otherClothesTempList)[i].Type));
    }


     ui->tableWidget->update();
}


void STSelectClothesTypeAndPrice::on_tableWidget_cellClicked(int row, int column)
{
    if(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().isNull())
    {
        return;
    }
    QString text = ui->tableWidget->item(row,0)->text();
    bool isNumber = false;
    text.toInt(&isNumber);
    if(!isNumber)
    {
        return;
    }
    int currentRow = ui->tableWidget->currentRow();
    Name = ui->tableWidget->item(currentRow,1)->text();
    Price = ui->tableWidget->item(currentRow,2)->text();
    //qDebug() << "Name:" << Name;
    //qDebug() << "Price:" << Price;

    emit chosenClothesType();

}
