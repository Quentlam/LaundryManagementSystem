#ifndef DLGSHOPDATA_H
#define DLGSHOPDATA_H

#include <QDialog>

namespace Ui {
class dlgShopData;
}

class dlgShopData : public QDialog
{
    Q_OBJECT

public:
    explicit dlgShopData(QWidget *parent = nullptr);
    ~dlgShopData();

    void reFresh();
private slots:
    void on_BtnSave_clicked();

private:
    Ui::dlgShopData *ui;
};

#endif // DLGSHOPDATA_H
