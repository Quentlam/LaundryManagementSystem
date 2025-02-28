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

void STSelectClothesTypeAndPrice::keyPressEvent(QKeyEvent* event)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text() == (ui->LeSearch->text())) {
                    rowMatches = true;
                    Name = ui->tableWidget->item(row,1)->text();
                    Price = ui->tableWidget->item(row,2)->text();
                    emit chosenClothesType();
                    ui->LeSearch->clear();
                    return;
                }
            }
        }
        // 根据是否匹配来发送信号

    }
}

void STSelectClothesTypeAndPrice::lineFocus()
{
    ui->LeSearch->setFocus();
}

void STSelectClothesTypeAndPrice::choseClothes(int type)
{
    ui->tableWidget->clear();
    auto sqlPtr = pulic::getInstance()->sql;
    QList<clothesInfo> clothesListTemp;
    QList<QString> clothesTittle;
    clothesInfo clothesTemp;
    clothesTittle << "衣服ID" << "衣服名称" << "建议价格" << "衣服类型";


    switch (type)
    {
         case 0://如果选择了干洗
        {
         sqlPtr->exec("select count(ID) from Clothes where WashWay = '干洗'");
         sqlPtr->next();
         int Cnt = sqlPtr->value(0).toInt();
         ui->tableWidget->setRowCount(Cnt);
         ui->tableWidget->setColumnCount(clothesTittle.size());
         sqlPtr->exec("select * from Clothes where WashWay = '干洗'");
         break;
        }
         case 1://如果选择了水洗
        {
         sqlPtr->exec("select count(ID) from Clothes where WashWay = '水洗'");
         sqlPtr->next();
         int Cnt = sqlPtr->value(0).toInt();
         ui->tableWidget->setRowCount(Cnt);
         ui->tableWidget->setColumnCount(clothesTittle.size());
         sqlPtr->exec("select * from Clothes where WashWay = '水洗'");
         break;
        }
         case 2://如果选择了皮衣
        {
         sqlPtr->exec("select count(ID) from Clothes where WashWay = '皮衣'");
         sqlPtr->next();
         int Cnt = sqlPtr->value(0).toInt();
         ui->tableWidget->setRowCount(Cnt);
         ui->tableWidget->setColumnCount(clothesTittle.size());
         sqlPtr->exec("select * from Clothes where WashWay = '皮衣'");
         break;
        }
        case 3://如果选择了单烫
       {
        sqlPtr->exec("select count(ID) from Clothes where WashWay = '单烫'");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());
        sqlPtr->exec("select * from Clothes where WashWay = '单烫'");
        break;
       }
        case 4://如果选择了其他
       {
        sqlPtr->exec("select count(ID) from Clothes where WashWay = '其他'");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());
        sqlPtr->exec("select * from Clothes where WashWay = '其他'");
        break;
       }
        default:
        {
            QMessageBox::information(nullptr,"信息","不存在的类型！");
            break;
        }
    }



    for(int i = 0 ; i < clothesTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle

    while(sqlPtr->next())
    {
        clothesTemp.ID = sqlPtr->value(0).toString();
        clothesTemp.Name = sqlPtr->value(1).toString();
        clothesTemp.Price = sqlPtr->value(2).toInt();
        clothesTemp.Type = sqlPtr->value(3).toString();
        clothesListTemp.push_back(clothesTemp);
    }

    for(int i = 0; i < clothesListTemp.size(); i ++)//把所有的衣服都查出来都放上去
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(clothesListTemp[i].ID));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(clothesListTemp[i].Name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(clothesListTemp[i].Price)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(clothesListTemp[i].Type));
    }

     ui->tableWidget->update();
}


void STSelectClothesTypeAndPrice::on_tableWidget_cellClicked(int row, int column)
{
    int currentRow = ui->tableWidget->currentRow();
    Name = ui->tableWidget->item(currentRow,1)->text();
    Price = ui->tableWidget->item(currentRow,2)->text();
    //qDebug() << "Name:" << Name;
    //qDebug() << "Price:" << Price;

    emit chosenClothesType();

}

void STSelectClothesTypeAndPrice::on_LeSearch_textChanged(const QString &arg1)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text().contains(arg1,Qt::CaseInsensitive)) {
                    rowMatches = true;
                    break;
                }
            }
        }
        // 根据是否匹配来显示或隐藏行
        ui->tableWidget->setRowHidden(row, !rowMatches);
    }
}
