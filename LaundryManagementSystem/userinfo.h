#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
class userInfo
{
public:
    userInfo();
    QString ID;
    QString Account;
    QString Password;
    QString Name;
    QString Authority;

    static QList<QString> userInfoTittle;
};

#endif // USERINFO_H
