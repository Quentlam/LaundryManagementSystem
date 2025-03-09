#ifndef DLGMANAGE_H
#define DLGMANAGE_H

#include <QDialog>
#include "dlgadd.h"
#include <QTreeWidgetItem>
#include "dlgshopdata.h"
#include "dlgprinterdata.h"
namespace Ui {
class dlgManage;
}

class dlgManage : public QDialog
{
    Q_OBJECT

public:
    explicit dlgManage(QWidget *parent = nullptr);
    ~dlgManage();
    dlgAdd dlgadd;
    dlgShopData dlgshop;
    Ref<dlgPrinterData> dlgPinter;
    void show();
signals:
    void backToMainWindow();
private slots:
    void on_BtnBack_clicked();

    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

private:
    Ui::dlgManage *ui;
};

#endif // DLGMANAGE_H
