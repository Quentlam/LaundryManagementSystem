#include "laundrymanagementlogger.h"
#include <QDebug>
#include <QDateTime>


LaundryManagementLogger::LaundryManagementLogger()
{

}

void LaundryManagementLogger::record(Operate operate)//每个操作只需要把操作对象和操作详细给写上去即可，就是创建自己的Operate对象，再写两个属性即可。
{
    operate.userID = (*pulic::currentUser).ID;
    operate.userName = (*pulic::currentUser).Name;
    operate.time = QDateTime::currentDateTime().toString();
    operate.address = QString("%1").arg(pulic::currentAddress->data());
    //qDebug() << "operate.address: " << operate.address;
    auto sqlPtr = GET_SQL_POINTER;
    sqlPtr->exec(QString("insert into OperateLog values (null,'%1','%2','%3','%4','%5','%6');")
                 .arg(operate.userID)
                 .arg(operate.userName)
                 .arg(operate.operate)
                 .arg(operate.time)
                 .arg(operate.target)
                 .arg(operate.address)
                 );

#ifdef test//如果是测试阶段的话

    Operate temp;
    sqlPtr->exec(QString("select * from OperateLog where ID = %1").arg(sqlPtr->lastInsertId().toInt()));//获得最后受影响的ID值，然后返回回来并且查询所做的操作
    //qDebug() << sqlPtr->lastInsertId().toInt();//查一下现在最后受影响的id为多少
    sqlPtr->next();
    temp.ID       = sqlPtr->value(0).toInt();
    temp.userID   = sqlPtr->value(1).toString();
    temp.userName = sqlPtr->value(2).toString();
    temp.operate  = sqlPtr->value(3).toString();
    temp.time     = sqlPtr->value(4).toString();
    temp.target   = sqlPtr->value(5).toString();
    temp.address  = sqlPtr->value(6).toString();

    qDebug() << QString("已经计入数据库，操作ID:%1,操作用户ID:%2,操作员:%3,操作详细:%4,操作时间:%5,操作对象:%6,操作地址:%7")
                .arg(temp.ID)
                .arg(temp.userID)
                .arg(temp.userName)
                .arg(temp.operate)
                .arg(temp.time)
                .arg(temp.target)
                .arg(temp.address);
#endif


}
