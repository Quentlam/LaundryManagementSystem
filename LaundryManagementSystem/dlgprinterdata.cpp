#include "dlgprinterdata.h"
#include <QDebug>
#include "printerinfo.h"
#include "ui_dlgprinterdata.h"
#include <QMessageBox>
#include <QPrinterInfo>
#include "sqlManager.h"

dlgPrinterData::dlgPrinterData(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dlgPrinterData)
{
    ui->setupUi(this);
}

dlgPrinterData::~dlgPrinterData()
{
    delete ui;
}

void dlgPrinterData::reFresh()
{
    Ref<printerInfo> temp = sqlManager::createPrinterSql()->selectPrinterInfo();
    QList<QPrinterInfo> printerList = QPrinterInfo::availablePrinters();
    int i = 0;
    foreach (const QPrinterInfo &printerInfo, printerList) {
        ui->CBPrinterName->addItem(printerInfo.printerName());
        if(printerInfo.printerName() == temp->printerName)
        {
            ui->CBPrinterName->setCurrentIndex(i);
            ui->LACurrentPrinterName->setText(QString("现在打印机名称：%1").arg(printerInfo.printerName()));
        }
        i ++;
        qDebug() << "Printer Name:" << printerInfo.printerName();
    }
    if(temp->paperCount == "1")
    {
        ui->CBPaperCount->setCurrentIndex(0);
    }
    if(temp->paperCount == "2")
    {
        ui->CBPaperCount->setCurrentIndex(1);
    }
    if(temp->paperCount == "3")
    {
        ui->CBPaperCount->setCurrentIndex(2);
    }

    if(temp->paperWidth == "80mm")
    {
        ui->RA80mmPaper->setChecked(true);
    }
    if(temp->paperWidth == "58mm")
    {
        ui->RA58mmPaper->setChecked(true);
    }
    if(temp->paperWidth == "76mm")
    {
        ui->RA76mmPaper->setChecked(true);
    }
    ui->plainTextEdit->setPlainText(temp->Head1);
    ui->plainTextEdit_2->setPlainText(temp->Head2);
    ui->plainTextEdit_3->setPlainText(temp->Head3);


}

void dlgPrinterData::on_BtnSavePrinterData_clicked()
{
    printerInfo temp;
    temp.printerName = ui->CBPrinterName->currentText();
    if(ui->RA80mmPaper->isChecked())
    {
        temp.paperWidth = "80mm";
    }
    if(ui->RA76mmPaper->isChecked())
    {
        temp.paperWidth = "76mm";
    }
    if(ui->RA58mmPaper->isChecked())
    {
        temp.paperWidth = "58mm";
    }

    temp.paperCount  = ui->CBPaperCount->currentText();
    temp.Head1 = ui->plainTextEdit->toPlainText();
    temp.Head2 = ui->plainTextEdit_2->toPlainText();
    temp.Head3 = ui->plainTextEdit_3->toPlainText();
    auto status = sqlManager::createPrinterSql()->savePrinterInfo(temp);
    if(status)
    {
        QMessageBox::information(nullptr,"信息","修改成功！");
        return;
    }
    if(!status)
    {
        QMessageBox::information(nullptr,"信息","修改失败！");
        return;
    }

}

