#ifndef CLOTHESINFO_H
#define CLOTHESINFO_H

#include <QLabel>
#include <QObject>

class clothesInfo
{
public:
    clothesInfo();
    QString ID;
    QString Name;
    int Price;
    QString Type;
    QString WashWay;


    void showCustomerFunc();//用于数据回显的方法

};

class SelectClothesInfo
{
public:
    QString Name;
    QString Color;
    QString Defect;
    QString Brand;
    QString Treament;
    QString Effect;
    QString Price;
};

#endif // CLOTHESINFO_H
