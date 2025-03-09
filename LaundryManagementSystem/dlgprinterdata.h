#ifndef DLGPRINTERDATA_H
#define DLGPRINTERDATA_H

#include <QDialog>

namespace Ui {
class dlgPrinterData;
}

class dlgPrinterData : public QDialog
{
    Q_OBJECT

public:
    explicit dlgPrinterData(QWidget *parent = nullptr);
    ~dlgPrinterData();
    void reFresh();

private slots:
    void on_BtnSavePrinterData_clicked();

private:
    Ui::dlgPrinterData *ui;
};

#endif // DLGPRINTERDATA_H
