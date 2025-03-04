#include "customerinfo.h"



QList<QString> customerInfo::customerTittle = {
                            "客户编号",
                            "客户性别",
                            "客户姓名",
                            "客户电话",
                            "客户卡号",
                            "消费额",
                            "消费次数",
                            "消费卡种类",
                            "欠缴情况",
                            "欠缴余额",
                            "客户卡剩余余额",
                            "客户住址",
                            "客户信用",
                            "备注"
                             };
customerInfo::customerInfo()
{

}

customerInfo::customerInfo(QString ID,QString Gender,QString Name,QString Phone,QString CardID,double Spend,double Count,QString CardType,QString HaveNotPaid,QString HaveNotPaidMoney,double CardMoney,QString Address,QString Credit,QString Notes)
    :ID(ID),Gender(Gender),Name(Name),Phone(Phone),CardID(CardID),Spend(Spend),Count(Count),CardType(CardType),HaveNotPaid(HaveNotPaid),HaveNotPaidMoney(HaveNotPaidMoney),CardMoney(CardMoney),Address(Address),Credit(Credit),Notes(Notes)
{

}
