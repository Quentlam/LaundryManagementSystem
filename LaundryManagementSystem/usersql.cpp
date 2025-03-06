#include "usersql.h"
#include <QVariant>
#include "pulic.h"


userSql* userSql::Instance = nullptr;

userSql::~userSql()
{
    delete  sql;
    delete  Instance;
}

Ref<QList<userInfo> > userSql::showAllUser()
{
    Ref<QList<userInfo> > userTempInfoList = std::make_unique<QList<userInfo>>();
    userInfo userTempInfo;
    sql->exec("select * from User");//把所有的员工都查出来（反正也没几个）
    while(sql->next())
    {
        userTempInfo.ID        = sql->value(0).toString();
        userTempInfo.Account   = sql->value(1).toString();
        userTempInfo.Password  = sql->value(2).toString();
        userTempInfo.Name      = sql->value(3).toString();
        userTempInfo.Authority = sql->value(4).toString();
        userTempInfoList->push_back(userTempInfo);
    }
    return userTempInfoList;
}

Ref<ShopData> userSql::showShopData()
{
    Ref<ShopData> shopData = std::make_unique<ShopData>();
    sql->exec("select * from ShopData");
    while(sql->next())
    {
        (*shopData).ShopID          = sql->value(0).toString();
        (*shopData).ShopName        = sql->value(1).toString();
        (*shopData).ShopAddress     = sql->value(2).toString();
        (*shopData).SearchPhone     = sql->value(3).toString();
        (*shopData).ComplaintsPhone = sql->value(4).toString();
        (*shopData).AdvertiseMent   = sql->value(5).toString();
    }
    return shopData;
}

bool userSql::deleteUserById(QString id)
{
    return sql->exec(QString("delete from User where ID = '%1'").arg(id));
}

bool userSql::updateUserById(userInfo& userInfoTemp,QString ID)
{
    return sql->exec(QString("update User set ID = '%1',Account = '%2',Password = '%3',Name = '%4',Authority = '%5' where ID = '&6';")
                     .arg(userInfoTemp.ID).arg(userInfoTemp.Account).arg(userInfoTemp.Password).arg(userInfoTemp.Name).arg(userInfoTemp.Authority)
                     .arg(ID));
}

bool userSql::selectUserByAccount(QString account)
{
    sql->exec(QString("select * from User where Account = '%1'").arg(account));
    return sql->next();
}

bool userSql::selectUserByName(QString name)
{
    sql->exec(QString("select * from User where Name = '%1'").arg(name));
    return sql->next();
}

bool userSql::addUser(userInfo userInfoTemp)
{
    return sql->exec(QString("insert into User values('%1','%2','%3','%4','%5');").
              arg(userInfoTemp.ID).
              arg(userInfoTemp.Account).
              arg(userInfoTemp.Password).
              arg(userInfoTemp.Name).
              arg(userInfoTemp.Authority)
                     );
}

bool userSql::userLogin(QString account, QString password,QString address)
{
    sql->exec(QString("SELECT * FROM User WHERE Account = '%1' AND Password = '%2'").arg(account).arg(password));
    bool status = false;
    if(sql->next())
    {
        status =true;
        (*pulic::currentUser).ID        = sql->value(0).toString();
        (*pulic::currentUser).Account   = sql->value(1).toString();
        (*pulic::currentUser).Password  = sql->value(2).toString();
        (*pulic::currentUser).Name      = sql->value(3).toString();
        (*pulic::currentUser).Authority = sql->value(4).toString();
        pulic::currentAddress =  new QString(address);//选择分店之后，放到现在的分店里
        pulic::login = true;
    }

    return status;
}

bool userSql::saveShopData(ShopData& shopdata)
{
    return sql->exec(QString("UPDATE ShopData SET ShopID = '%1',ShopName = '%2',ShopAddress = '%3',SearchPhone = '%4',ComplaintsPhone = '%5',Advertisement = '%6'")
                    .arg(shopdata.ShopID).arg(shopdata.ShopName).arg(shopdata.ShopAddress).arg(shopdata.SearchPhone)
                    .arg(shopdata.ComplaintsPhone).arg(shopdata.AdvertiseMent)
                    );
}

userSql::userSql():
    sql(new QSqlQuery())
{

}
