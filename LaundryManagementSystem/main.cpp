#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <QPrinter>
#include <QPainter>
//#include <QPrinterInfo>
#include <QSerialPortInfo>
#include <memory>


MainWindow* MainWindow::Instance = nullptr;
Scope<sqlManager> sqlManager::Instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto mainWindow = MainWindow::getInstance();
//    QList<QPrinterInfo> printerList = QPrinterInfo::availablePrinters();
//    foreach (const QPrinterInfo &printerInfo, printerList) {
//        qDebug() << "Printer Name:" << printerInfo.printerName();
//    }

    return a.exec();
}
