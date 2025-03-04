#ifndef SHELFINFO_H
#define SHELFINFO_H

#include <QObject>

class shelfInfo
{
public:
    shelfInfo();
    QString ID;
    QString status;
    enum shelfSet
    {
      A,
      B
    };

};

#endif // SHELFINFO_H
