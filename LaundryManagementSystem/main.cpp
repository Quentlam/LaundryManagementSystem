#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <QPrinter>
#include <QPainter>
//#include <QPrinterInfo>
#include <memory>
#include <QDate>
#include <QPrinterInfo>

MainWindow* MainWindow::Instance = nullptr;
Scope<sqlManager> sqlManager::Instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto mainWindow = MainWindow::getInstance();


    return a.exec();
}
