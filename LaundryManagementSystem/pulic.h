#ifndef PULIC_H
#define PULIC_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "userinfo.h"
#include "sqlmanager.h"

class pulic : public QObject
{
    Q_OBJECT
public:
    explicit pulic(QObject *parent = nullptr);
    static pulic* getInstance()
    {
        if(nullptr == instance)
        {
           instance = new pulic();
        }
          return instance;
    }

    static userInfo* currentUser;
    static QString* currentAddress;
    static bool login;
    static int shelfCount;
    static QSqlDatabase* DB;

private:
    static pulic* instance;

};

#endif // PULIC_H
