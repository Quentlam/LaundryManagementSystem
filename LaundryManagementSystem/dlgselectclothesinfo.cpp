#include "dlgselectclothesinfo.h"
#include "ui_dlgselectclothesinfo.h"

dlgSelectClothesInfo::dlgSelectClothesInfo(QWidget *parent,QList<SelectClothesInfo> selectClothesInfo) :
    QDialog(parent),
    temp(selectClothesInfo),
    ui(new Ui::dlgSelectClothesInfo)
{
    ui->setupUi(this);
     this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    reFresh();
}

dlgSelectClothesInfo::~dlgSelectClothesInfo()
{
    delete ui;
}

int dlgSelectClothesInfo::exec()
{
    QDialog::exec();
    reFresh();
    return 1;
}

void dlgSelectClothesInfo::reFresh()
{
    ui->tableWidget->clear();
    ui->tableWidget->clear();
    ui->label->setText(QString("共记录了%1件衣服").arg(temp.size()));
    QList<QString> clothesTittle;
    clothesTittle << "衣服名称" << "衣服颜色" << "衣服瑕疵" << "衣服品牌" << "特殊处理" << "洗后效果" << "价格";

    int Cnt = temp.size();
    ui->tableWidget->setRowCount(Cnt);
    ui->tableWidget->setColumnCount(clothesTittle.size());

    for(int i = 0 ; i < clothesTittle.size(); i ++)
    ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle



    for(int i = 0; i < temp.size(); i ++)//把所有的衣服都放上去
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(temp[i].Name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(temp[i].Color));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(temp[i].Defect));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(temp[i].Brand));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(temp[i].Treament));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(temp[i].Effect));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(temp[i].Price));

    }

     ui->tableWidget->update();
}

void dlgSelectClothesInfo::on_lineEdit_textChanged(const QString &arg1)//关键词搜索
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
