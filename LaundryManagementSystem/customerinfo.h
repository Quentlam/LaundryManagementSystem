#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H
#include <QObject>


class customerInfo
{
public:
    customerInfo();
    customerInfo(QString ID,QString Gender,QString Name,QString Phone,QString CardID,double Spend,double Count,QString CardType,QString HaveNotPaid,QString HaveNotPaidMoney,double CardMoney,QString Address,QString Credit,QString Notes);
    QString ID;
    QString Gender;
    QString Name;
    QString Phone;
    QString CardID;
    double Spend;
    double Count;
    QString CardType;
    QString HaveNotPaid;
    QString HaveNotPaidMoney;
    double CardMoney;
    QString Address;
    QString Credit;
    QString Notes;

};

#endif // CUSTOMERINFO_H
