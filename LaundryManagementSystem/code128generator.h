#ifndef CODE128GENERATE_H
#define CODE128GENERATE_H

#include <QObject>

class code128Generator
{
public:
    code128Generator(QString OrderID);
    char calculateChecksum(const QString &data);
    Ref<QImage> GenerateCode128();
    QString OrderID;
};

#endif // CODE128GENERATE_H
