#include "clothesinfo.h"
#include "pulic.h"
#include <QSql>
#include <QVariant>

QList<QString> clothesInfo::clothesTittle =
                                    {
                                    "衣服ID" ,
                                    "衣服名称" ,
                                    "建议价格" ,
                                    "衣服类型" ,
                                    "衣物处理"
                                    };
QList<QString> clothesInfo::clothesColorTittle =
                                    {
                                    "ID" ,
                                    "衣服颜色"
                                    };

QList<QString> clothesInfo::clothesDefectTittle =
                                    {
                                    "ID" ,
                                    "衣服瑕疵"
                                    };
QList<QString> clothesInfo::clothesBrandTittle =
                                    {
                                    "ID" ,
                                    "衣服品牌"
                                    };
QList<QString> clothesInfo::clothesWashEffectTittle =
                                    {
                                    "ID" ,
                                    "洗后效果"
                                    };
QList<QString> clothesInfo::clothesSpecialTreatmentTittle =
                                    {
                                    "ID" ,
                                    "特殊处理"
                                    };

clothesInfo::clothesInfo()
{

}



clothesAttributeInfo::clothesAttributeInfo()
{

}

clothesAttributeInfo::clothesAttributeInfo(QString id, QString name):
                                        ID(id),Name(name)
{

}
