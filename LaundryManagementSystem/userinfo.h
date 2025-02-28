#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

struct UserInformation
{
  QString ID;
  QString Account;
  QString Password;
  QString Name;
  QString Authority;

};


class userInfo
{
public:
    userInfo();
    UserInformation userInformation;

};

#endif // USERINFO_H
