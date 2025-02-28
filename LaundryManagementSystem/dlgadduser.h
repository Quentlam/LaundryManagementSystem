#ifndef DLGADDUSER_H
#define DLGADDUSER_H

#include <QDialog>
#include "laundrymanagementlogger.h"


namespace Ui {
class dlgAddUser;
}

class dlgAddUser : public QDialog
{
    Q_OBJECT
public:
    explicit dlgAddUser(QWidget *parent = nullptr);
    ~dlgAddUser();
    Operate addUserOperate;
    int exec();


private slots:
    void on_BtnEnter_clicked();

private:
    Ui::dlgAddUser *ui;
};

#endif // DLGADDUSER_H
