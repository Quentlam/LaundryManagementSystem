#include "mainwindow.h"
#include <QApplication>
#include "pulic.h"
#include <QDebug>
#include "printer.h"
#include <QTextCodec>


MainWindow* MainWindow::Instance = nullptr;
int main(int argc, char *argv[])
{
    // 以下部分解决中文乱码
    QTextCodec *codec = QTextCodec::codecForName("GBK"); //GBK gbk
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    // 以上部分解决中文乱码
    QApplication a(argc, argv);
    auto mainWindow = MainWindow::getInstance();
    //Printer printer;
    //printer.printTest();


    return a.exec();
}
