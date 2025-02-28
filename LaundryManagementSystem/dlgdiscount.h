#ifndef DLGDISCOUNT_H
#define DLGDISCOUNT_H

#include <QDialog>

namespace Ui {
class dlgDiscount;
}

class dlgDiscount : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDiscount(QWidget *parent = nullptr);
    ~dlgDiscount();
    void setCurrentIndex(int index);
    QString Message;

private slots:


    void on_BtnEnter_clicked();

    void on_BtnCancel_clicked();

signals:
    void sentDiscount();

private:
    Ui::dlgDiscount *ui;
};

#endif // DLGDISCOUNT_H
