#include "mainwindow.h"
#include <QApplication>
#include "pulic.h"
#include <QDebug>
#include "printer.h"
#include <QTextCodec>
#include <QPrinter>
#include <QPainter>
#include <QPrinterInfo>
#include <QSerialPortInfo>


MainWindow* MainWindow::Instance = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto mainWindow = MainWindow::getInstance();
    QList<QPrinterInfo> printerList = QPrinterInfo::availablePrinters();
    foreach (const QPrinterInfo &printerInfo, printerList) {
        qDebug() << "Printer Name:" << printerInfo.printerName();
    }

    return a.exec();
}
