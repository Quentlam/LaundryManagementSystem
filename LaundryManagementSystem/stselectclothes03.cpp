#include "stselectclothes03.h"
#include "ui_stselectclothes03.h"
#include "pulic.h"

STSelectClothes03::STSelectClothes03(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STSelectClothes03)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->tableWidget->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮

    reFresh();

}

STSelectClothes03::~STSelectClothes03()
{
    delete ui;
}

void STSelectClothes03::on_tableWidget_cellClicked(int row, int column)
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
    message = ui->tableWidget->item(row,1)->text();
    //qDebug() << "message:" << message;
    emit chosenMessage();
}

bool STSelectClothes03::searchClothes(QString text)
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
                    message = ui->tableWidget->item(row,1)->text();
                    emit chosenMessage();
                    return true;
                }
            }
        }
        // 根据是否匹配来发送信号
    }
    return false;
}

void STSelectClothes03::reFresh()
{
    Ref<QList<clothesAttributeInfo>> clothesAttributeTempList = sqlManager::createClothesSql()->showClothesSpecialTreatmentInfo();
    ui->tableWidget->setRowCount(clothesAttributeTempList->size());
    ui->tableWidget->setColumnCount(clothesInfo::clothesSpecialTreatmentTittle.size());
    for(int i = 0 ; i < clothesInfo::clothesSpecialTreatmentTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesInfo::clothesSpecialTreatmentTittle[i]));


    for(int i = 0 ; i < clothesAttributeTempList->size(); i ++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem((*clothesAttributeTempList)[i].ID));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem((*clothesAttributeTempList)[i].Name));
    }
}
