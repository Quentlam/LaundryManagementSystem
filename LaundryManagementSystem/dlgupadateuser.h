#ifndef DLGUPDATEUSER_H
#define DLGUPDATEUSER_H

#include <QDialog>
#include "userinfo.h"
#include "laundrymanagementlogger.h"

namespace Ui {
class dlgUpadateUser;
}

class dlgUpadateUser : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUpadateUser(QWidget *parent = nullptr);
    explicit dlgUpadateUser(QWidget *parent, UserInformation Temp);
    ~dlgUpadateUser();
    UserInformation userTemp;
    Operate updateUserOperate;


private slots:
    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::dlgUpadateUser *ui;
};

#endif // DLGUPDATEUSER_H
