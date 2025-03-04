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
    ~clotheSql();
    static clotheSql* getInstance()
    {
        if(nullptr == Instance)
        {
            return new clotheSql();
        }
        else
        {
            return Instance;
        }
    }

public:
   std::unique_ptr<QList<clothesInfo>>          showClothesInfo(clothesInfo::WashWayType type);
   std::unique_ptr<QList<clothesAttributeInfo>> showClothesColorInfo();
   std::unique_ptr<QList<clothesAttributeInfo>> showClothesDefectInfo();
   std::unique_ptr<QList<clothesAttributeInfo>> showClothesBrandInfo();
   std::unique_ptr<QList<clothesAttributeInfo>> showClothesSpecialTreatmentInfo();
   std::unique_ptr<QList<clothesAttributeInfo>> showClothesWashingEffectInfo();


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
    clotheSql();
    QSqlQuery* sql;
    static clotheSql* Instance;
};

#endif // CLOTHESQL_H
