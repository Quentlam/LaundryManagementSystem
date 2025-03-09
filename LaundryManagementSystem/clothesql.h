#ifndef CLOTHESQL_H
#define CLOTHESQL_H

#include <QObject>
#include <QSqlQuery>
#include "clothesinfo.h"
#include <QDebug>
#include <QSqlError>

class clotheSql
{
public:
    clotheSql();
    static Scope<clotheSql> Instance;
    ~clotheSql();
    static Scope<clotheSql> getInstance()
    {
        if(nullptr == Instance)
        {
            Instance = std::make_shared<clotheSql>();
            return Instance;
        }
        else
        {
            return Instance;
        }
    }

public:
   Ref<QList<clothesInfo>>          showClothesInfo(clothesInfo::WashWayType type);
   Ref<QList<clothesAttributeInfo>> showClothesColorInfo();
   Ref<QList<clothesAttributeInfo>> showClothesDefectInfo();
   Ref<QList<clothesAttributeInfo>> showClothesBrandInfo();
   Ref<QList<clothesAttributeInfo>> showClothesSpecialTreatmentInfo();
   Ref<QList<clothesAttributeInfo>> showClothesWashingEffectInfo();


   QList<SelectClothesInfo>* showCustomerAllClothesFunc(QString OrderID);//用于查询订单的所有衣服
   void setCustomerClothes                             (QList<SelectClothesInfo> *, QString OrderID);//用于设置已经选好的衣服到订单里去
   bool deleteClothesByID                              (QString id);
   bool deleteClothesColorByID                         (QString id);
   bool deleteClothesBrandByID                         (QString id);
   bool deleteClothesDefectByID                        (QString id);
   bool deleteClothesTreatmentByID                     (QString id);
   bool deleteClothesWashingEffectByID                 (QString id);
   bool updateClothesById                              (clothesInfo clothesInfoTemp,QString ID);
   bool updateClothesAttributeById                     (clothesAttributeInfo clothesAttributeInfoTemp,clothesAttributeInfo::AttributeType type,QString ID);
   bool addClothes                                     (clothesInfo clothesInfoTemp);
   bool addClothesAttribute                            (clothesAttributeInfo clothesAttributeInfoTemp,clothesAttributeInfo::AttributeType type);



   void getError()
   {
       qDebug() << sql->lastError().text();
   }

private:
    QSqlQuery* sql;

};

#endif // CLOTHESQL_H
