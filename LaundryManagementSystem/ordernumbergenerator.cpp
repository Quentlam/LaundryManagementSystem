#include "ordernumbergenerator.h"
#include "pulic.h"
#include <QVariant>
#include <QDebug>

OrderNumberGenerator::OrderNumberGenerator()
{

}

QString OrderNumberGenerator::generateOrderNumber()
{
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select * from CurrentOrderID");
    sqlPtr->next();
    QString preOrderID = sqlPtr->value(0).toString();//这里拿的是之前的OrderID
    QString QHead;//获得头部
    QString QCurrentSuffix;//获得尾部

    QHead = preOrderID.at(0);
    QCurrentSuffix = preOrderID.right(4);//拿到后四位
    head = QHead.toInt();//给Head
    currentSuffix = QCurrentSuffix.toInt();//给尾部
    incrementSuffix();

    QDate currentDate = QDate::currentDate();
    int year = currentDate.year() % 10; // 取年份的后一位
    int month = currentDate.month();
    int day = currentDate.day();


    // 生成订单号
    QString orderNumber = QString("%1%2%3%4%5")
           .arg(head)
           .arg(year, 1, 10, QLatin1Char('0'))
           .arg(month, 2, 10, QLatin1Char('0'))
           .arg(day, 2, 10, QLatin1Char('0'))
           .arg(currentSuffix, 4, 10, QLatin1Char('0'));


    return orderNumber;
}

void OrderNumberGenerator::incrementSuffix()
{
    // 自增后缀，如果达到9999则重新生成随机数
    currentSuffix++;
    if (currentSuffix > 9999)
    {
      currentSuffix = 0;
      if(head >= 0 && head < 9)head ++;
      else head = 0;
    }
}


