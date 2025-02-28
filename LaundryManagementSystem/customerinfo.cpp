#include "customerinfo.h"

customerInfo::customerInfo()
{

}

customerInfo::customerInfo(QString ID,QString Gender,QString Name,QString Phone,QString CardID,double Spend,double Count,QString CardType,QString HaveNotPaid,QString HaveNotPaidMoney,double CardMoney,QString Address,QString Credit,QString Notes)
    :ID(ID),Gender(Gender),Name(Name),Phone(Phone),CardID(CardID),Spend(Spend),Count(Count),CardType(CardType),HaveNotPaid(HaveNotPaid),HaveNotPaidMoney(HaveNotPaidMoney),CardMoney(CardMoney),Address(Address),Credit(Credit),Notes(Notes)
{

}
