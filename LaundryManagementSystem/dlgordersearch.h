#ifndef DLGORDERSEARCH_H
#define DLGORDERSEARCH_H
#include "orderinfo.h"
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


    QList<OrderInfo> allOrder;
    void reFresh();
    void show();
private slots:
    void on_LeSearch_textChanged(const QString &arg1);

    void on_RaDateSearch_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::dlgOrderSearch *ui;
};

#endif // DLGORDERSEARCH_H
