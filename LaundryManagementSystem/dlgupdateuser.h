#ifndef DLGUPDATEUSER_H
#define DLGUPDATEUSER_H

#include <QDialog>
#include "userinfo.h"


namespace Ui {
class dlgUpdateUser;
}

class dlgUpdateUser : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUpdateUser(QWidget *parent = nullptr);
    explicit dlgUpdateUser(QWidget *parent, UserInformation Temp);
    ~dlgUpdateUser();
    UserInformation userTemp;

private:
    Ui::dlgUpdateUser *ui;
};

#endif // DLGUPDATEUSER_H
