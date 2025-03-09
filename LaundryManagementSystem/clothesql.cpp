#include "clothesql.h"
#include <QVariant>

Scope<clotheSql> clotheSql::Instance = nullptr;

clotheSql::~clotheSql()
{
    delete  sql;
}

Ref<QList<clothesInfo>> clotheSql::showClothesInfo(clothesInfo::WashWayType type)
{
    Ref<QList<clothesInfo>>clothesTempList;
    clothesInfo clothesTemp;
    QString typeName;
    switch (type)//挑选现在的类型
    {
    case clothesInfo::allClothes:
        {
        typeName = "全部";
        sql->exec(QString("select * from Clothes"));
        break;
        }
    case clothesInfo::wash:
        {
        typeName = "水洗";
        break;
        }
    case clothesInfo::dryClean:
        {
        typeName = "干洗";
        break;
        }
    case clothesInfo::leatherCoat:
        {
        typeName = "皮衣";
        break;
        }
    case clothesInfo::singleIroning:
        {
        typeName = "单烫";
        break;
        }
    case clothesInfo::other:
        {
        typeName = "其他";
        break;
        }

    }

    if(type != clothesInfo::WashWayType::allClothes)
    {
       sql->exec(QString("select * from Clothes where WashWay = '%1'").arg(typeName));
    }
    else
    {
       sql->exec(QString("select * from Clothes"));
    }
    while(sql->next())
    {
        clothesTemp.ID      = sql->value(0).toString();
        clothesTemp.Name    = sql->value(1).toString();
        clothesTemp.Price   = sql->value(2).toInt();
        clothesTemp.Type    = sql->value(3).toString();
        clothesTemp.WashWay = sql->value(4).toString();
        clothesTempList->push_back(clothesTemp);
    }
    return clothesTempList;
}

Ref<QList<clothesAttributeInfo> > clotheSql::showClothesColorInfo()
{
    Ref<QList<clothesAttributeInfo>> clothesColorInfoList;
    clothesAttributeInfo clothesColorInfoTemp;
    sql->exec(QString("select * from ClothesColor;"));
    while(sql->next())
    {
        clothesColorInfoTemp.ID        = sql->value(0).toString();
        clothesColorInfoTemp.Name      = sql->value(1).toString();
        clothesColorInfoList->push_back(clothesColorInfoTemp);
    }
    return clothesColorInfoList;
}

Ref<QList<clothesAttributeInfo> > clotheSql::showClothesDefectInfo()
{
    Ref<QList<clothesAttributeInfo>> clothesDefectInfoList;
    clothesAttributeInfo clothesDefectInfoTemp;
    sql->exec(QString("select * from ClothesDefect;"));
    while(sql->next())
    {
        clothesDefectInfoTemp.ID        = sql->value(0).toString();
        clothesDefectInfoTemp.Name      = sql->value(1).toString();
        clothesDefectInfoList->push_back(clothesDefectInfoTemp);
    }
    return clothesDefectInfoList;
}


Ref<QList<clothesAttributeInfo> > clotheSql::showClothesBrandInfo()
{
    Ref<QList<clothesAttributeInfo>> clothesBrandInfoList;
    clothesAttributeInfo clothesBrandInfoTemp;
    sql->exec(QString("select * from ClothesBrand;"));
    while(sql->next())
    {
        clothesBrandInfoTemp.ID        = sql->value(0).toString();
        clothesBrandInfoTemp.Name      = sql->value(1).toString();
        clothesBrandInfoList->push_back(clothesBrandInfoTemp);
    }
    return clothesBrandInfoList;
}


Ref<QList<clothesAttributeInfo> > clotheSql::showClothesSpecialTreatmentInfo()
{
    Ref<QList<clothesAttributeInfo>> clothesSpecialTreatmentInfoList;
    clothesAttributeInfo clothesSpecialTreatmentInfoTemp;
    sql->exec(QString("select * from SpecialTreatment;"));
    while(sql->next())
    {
        clothesSpecialTreatmentInfoTemp.ID        = sql->value(0).toString();
        clothesSpecialTreatmentInfoTemp.Name      = sql->value(1).toString();
        clothesSpecialTreatmentInfoList->push_back(clothesSpecialTreatmentInfoTemp);
    }
    return clothesSpecialTreatmentInfoList;
}


Ref<QList<clothesAttributeInfo> > clotheSql::showClothesWashingEffectInfo()
{
    Ref<QList<clothesAttributeInfo>> clothesWashingEffectInfoList;
    clothesAttributeInfo clothesWashingEffectInfoTemp;
    sql->exec(QString("select * from WashingEffect;"));
    while(sql->next())
    {
        clothesWashingEffectInfoTemp.ID        = sql->value(0).toString();
        clothesWashingEffectInfoTemp.Name      = sql->value(1).toString();
        clothesWashingEffectInfoList->push_back(clothesWashingEffectInfoTemp);
    }
    return clothesWashingEffectInfoList;
}

bool clotheSql::deleteClothesByID(QString id)
{
    return sql->exec(QString("delete from Clothes where ID = '%1'").arg(id));
}

bool clotheSql::deleteClothesColorByID(QString id)
{
    return sql->exec(QString("delete from ClothesColor where ID = '%1'").arg(id));
}

bool clotheSql::deleteClothesBrandByID(QString id)
{
    return sql->exec(QString("delete from ClothesBrand where ID = '%1'").arg(id));
}

bool clotheSql::deleteClothesDefectByID(QString id)
{
    return sql->exec(QString("delete from ClothesDefect where ID = '%1'").arg(id));
}

bool clotheSql::deleteClothesTreatmentByID(QString id)
{
    return sql->exec(QString("delete from SpecialTreatment where ID = '%1'").arg(id));
}

bool clotheSql::deleteClothesWashingEffectByID(QString id)
{
    return sql->exec(QString("delete from WashingEffect where ID = '%1'").arg(id));
}

bool clotheSql::updateClothesById(clothesInfo clothesInfoTemp,QString ID)
{
    return  sql->exec(QString("UPDATE Clothes SET ID = '%1',Name = '%2',Price = %3,Type = '%4',WashWay = '%5' where ID = '%6'")
            .arg(clothesInfoTemp.ID).arg(clothesInfoTemp.Name).arg(clothesInfoTemp.Price).arg(clothesInfoTemp.Type).arg(clothesInfoTemp.WashWay).arg(ID));
}

bool clotheSql::updateClothesAttributeById(clothesAttributeInfo clothesAttributeInfoTemp,clothesAttributeInfo::AttributeType type,QString ID)
{
    QString tableName;
    QString AttributeName;
    switch (type)
    {
    case clothesAttributeInfo::Color:
        tableName = "ClothesColor";
        AttributeName = "Color";
        break;
    case clothesAttributeInfo::Defect:
        tableName = "ClothesDefect";
        AttributeName = "Defect";
        break;
    case clothesAttributeInfo::Brand:
        tableName = "ClothesBrand";
        AttributeName = "Brand";
        break;
    case clothesAttributeInfo::SpecialTreatment:
        tableName = "SpecialTreatment";
        AttributeName = "Treatment";
        break;
    case clothesAttributeInfo::WashingEffect:
        tableName = "WashingEffect";
        AttributeName = "Effect";
        break;
    }
    return sql->exec(QString("update %1 set ID = '%2',%3 = '%4' where ID = '%5';")
                     .arg(tableName).arg(clothesAttributeInfoTemp.ID).arg(AttributeName).arg(clothesAttributeInfoTemp.Name).arg(ID));
}

bool clotheSql::addClothes(clothesInfo clothesInfoTemp)
{
    return sql->exec(QString("insert into Clothes values('%1','%2',%3,'%4','%5')").arg(clothesInfoTemp.ID).arg(clothesInfoTemp.Name).arg(clothesInfoTemp.Price).arg(clothesInfoTemp.Type).arg(clothesInfoTemp.WashWay));
}

bool clotheSql::addClothesAttribute(clothesAttributeInfo clothesAttributeInfoTemp,clothesAttributeInfo::AttributeType type)
{
    QString tableName;
    switch (type)
    {
    case clothesAttributeInfo::Color:
        tableName = "ClothesColor";
        break;
    case clothesAttributeInfo::Defect:
        tableName = "ClothesDefect";
        break;
    case clothesAttributeInfo::Brand:
        tableName = "ClothesBrand";
        break;
    case clothesAttributeInfo::SpecialTreatment:
        tableName = "SpecialTreatment";
        break;
    case clothesAttributeInfo::WashingEffect:
        tableName = "WashingEffect";
        break;
    }
    return sql->exec(QString("insert into %1 values('%2','%3')").arg(tableName).arg(clothesAttributeInfoTemp.ID).arg(clothesAttributeInfoTemp.Name));

}


clotheSql::clotheSql():
    sql(new QSqlQuery())
{

}
