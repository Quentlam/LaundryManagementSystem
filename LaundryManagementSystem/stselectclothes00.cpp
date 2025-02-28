#include "stselectclothes00.h"
#include "ui_stselectclothes00.h"
#include <QDebug>
#include "pulic.h"


STSelectClothes00::STSelectClothes00(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STSelectClothes00)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false); // 禁用表头的高亮（使其不能被选中）
    ui->tableWidget->verticalHeader()->setHighlightSections(false); // 禁用纵向表头的高亮
    reFresh();


}

STSelectClothes00::~STSelectClothes00()
{
    delete ui;
}

void STSelectClothes00::on_tableWidget_cellClicked(int row, int column)
{
    message = ui->tableWidget->item(row,1)->text();
    //qDebug() << "message:" << message;
    emit chosenMessage();
}

void STSelectClothes00::on_lineEdit_textChanged(const QString &arg1)
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


void STSelectClothes00::keyPressEvent(QKeyEvent* event)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text() == (ui->lineEdit->text())) {
                    rowMatches = true;
                    message = ui->tableWidget->item(row,1)->text();
                    ui->lineEdit->clear();
                    emit chosenMessage();
                    return;
                }
            }
        }
        // 根据是否匹配来发送信号

    }
}

void STSelectClothes00::reFresh()
{
    QList<QString> tittle;
    tittle << "编号" << "衣服颜色";
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select count(ID) from ClothesColor");
    sqlPtr->next();
    int Ctn = sqlPtr->value(0).toInt();
    ui->tableWidget->setRowCount(Ctn);
    ui->tableWidget->setColumnCount(tittle.size());
    for(int i = 0 ; i < tittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(tittle[i]));

    sqlPtr->exec("select * from ClothesColor");
    int i = 0;
    QString ID;
    QString name;
    while(sqlPtr->next())
    {
        ID = sqlPtr->value(0).toString();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(ID));
        name = sqlPtr->value(1).toString();
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
        i++;
    }
}

void STSelectClothes00::lineFocus()
{
    ui->lineEdit->setFocus();
}
