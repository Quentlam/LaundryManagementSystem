#ifndef CLOTHESINFO_H
#define CLOTHESINFO_H

#include <QObject>

class clothesInfo//每件衣服的固有属性
{
public:
    clothesInfo();
    QString ID;
    QString Name;
    int Price;
    QString Type;
    QString WashWay;

    enum WashWayType
    {
        allClothes,     //全部种类的衣服
        wash,           //水洗的衣服
        dryClean,       //干洗的衣服
        leatherCoat,    //皮衣
        singleIroning,  //单烫
        other           //其他
    };


    static QList<QString> clothesTittle;//                        衣服名称和价格
    static QList<QString> clothesColorTittle;//                   衣服颜色
    static QList<QString> clothesDefectTittle;//                  衣服瑕疵
    static QList<QString> clothesBrandTittle;//                   衣服品牌
    static QList<QString> clothesWashEffectTittle;//              洗后效果
    static QList<QString> clothesSpecialTreatmentTittle;//        特殊处理
};

class clothesAttributeInfo//用来存储衣服的其他属性的，比如颜色之类的
{
public:
    clothesAttributeInfo();
    clothesAttributeInfo(QString id,QString name);
public:
    QString ID;
    QString Name;
    enum AttributeType
    {
        Color,
        Defect,
        Brand,
        SpecialTreatment,
        WashingEffect
    };
};

class SelectClothesInfo//收衣服的时候，选择的属性
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
