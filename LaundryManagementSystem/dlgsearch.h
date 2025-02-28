#ifndef DLGSEARCH_H
#define DLGSEARCH_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "dlgordersearch.h"
#include "dlgorderstatus.h"
#include "dlgshelfsearch.h"
namespace Ui {
class dlgSearch;
}

class dlgSearch : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSearch(QWidget *parent = nullptr);
    ~dlgSearch();

    dlgOrderSearch dlgOrderSea;
    dlgOrderStatus dlgOrderStatusSea;
    dlgShelfSearch dlgShelfSea;

    void show();
private slots:
    void on_BtnBack_clicked();

    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

signals:
    void backToMainWindow();
private:
    Ui::dlgSearch *ui;
};

#endif // DLGSEARCH_H
