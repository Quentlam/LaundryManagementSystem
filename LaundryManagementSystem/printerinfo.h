#ifndef PRINTERINFO_H
#define PRINTERINFO_H

#include <QObject>

class printerInfo
{
public:
    printerInfo();
    int id;
    QString printerName;
    QString paperWidth;
    QString paperCount;
    QString Head1;
    QString Head2;
    QString Head3;
};

#endif // PRINTERINFO_H
