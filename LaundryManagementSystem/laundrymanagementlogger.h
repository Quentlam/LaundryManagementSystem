#ifndef LAUNDRYMANAGEMENTLOGGER_H
#define LAUNDRYMANAGEMENTLOGGER_H

#include <QObject>
#include "pulic.h"

#define test


struct Operate
{
    int ID;//操作id
    QString userID;
    QString userName;
    QString operate;
    QString target;
    QString time;
    QString address;
};



class LaundryManagementLogger
{
public:
    LaundryManagementLogger();
    static void record(Operate operate);



};

#endif // LAUNDRYMANAGEMENTLOGGER_H
