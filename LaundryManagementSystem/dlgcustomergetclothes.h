#ifndef DLGCUSTOMERGETCLOTHES_H
#define DLGCUSTOMERGETCLOTHES_H

#include <QDialog>
#include <QEvent>
#include <QLineEdit>
#include "laundrymanagementlogger.h"


namespace Ui {
class dlgCustomerGetClothes;
}

class dlgCustomerGetClothes : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCustomerGetClothes(QWidget *parent = nullptr);
    ~dlgCustomerGetClothes();
    void keyPressEvent(QKeyEvent *event);
    void search(QString OrderID);
    void countShelf(QString ShelfID);
    bool searchStatus;
    Operate operate;

    void setFocus(QString text);
private slots:
    void on_dlgCustomerGetClothes_finished(int result);

    void on_BtnCancel_clicked();

    void on_BtnCusotmerGetClothes_clicked();

    void on_BtnSelectAll_clicked();

private:
    Ui::dlgCustomerGetClothes *ui;
};


#endif // DLGCUSTOMERGETCLOTHES_H
