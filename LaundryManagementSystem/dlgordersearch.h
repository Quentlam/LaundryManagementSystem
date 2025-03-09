#ifndef DLGORDERSEARCH_H
#define DLGORDERSEARCH_H
#include "orderinfo.h"
#include "dlgchosecustomer.h"
#include <QDialog>

namespace Ui {
class dlgOrderSearch;
}

class dlgOrderSearch : public QDialog
{
    Q_OBJECT

public:
    explicit dlgOrderSearch(QWidget *parent = nullptr);
    ~dlgOrderSearch();
    dlgChoseCustomer dlgChoseCus;
    bool selectCustomer;
    void reFresh();
    void show();
private slots:
    void on_LeSearch_textChanged(const QString &arg1);

    void on_RaDateSearch_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_BtnChoseCustomer_clicked();

    void on_BtnDateSearch_clicked();

    void on_BtnCancel_clicked();

    void on_pushButton_clicked();

private:
    Ui::dlgOrderSearch *ui;
};

#endif // DLGORDERSEARCH_H
