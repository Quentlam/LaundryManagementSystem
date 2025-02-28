#ifndef ORDERNUMBERGENERATOR_H
#define ORDERNUMBERGENERATOR_H

#include <QDate>
#include <QString>
#include <QObject>
#include <QRandomGenerator>

class OrderNumberGenerator
{
public:
    OrderNumberGenerator();
    QString generateOrderNumber();

private:
    int head;
    int currentSuffix;
    void incrementSuffix();
  };

#endif // ORDERNUMBERGENERATOR_H
