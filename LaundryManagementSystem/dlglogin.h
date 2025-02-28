#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>

namespace Ui {
class dlgLogin;
}

class dlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLogin(QWidget *parent = nullptr);
    ~dlgLogin();

private slots:
    void on_btnCancel_clicked();
    void on_btnLogin_clicked();

private:
    Ui::dlgLogin *ui;

signals:
    void loginSuccess();


};

#endif // DLGLOGIN_H
