#ifndef DLGSHELFSEARCH_H
#define DLGSHELFSEARCH_H

#include <QDialog>

namespace Ui {
class dlgShelfSearch;
}

class dlgShelfSearch : public QDialog
{
    Q_OBJECT

public:
    explicit dlgShelfSearch(QWidget *parent = nullptr);
    ~dlgShelfSearch();

    void reFresh();
    QString shelfNumber;
    bool shelfSelected;
private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_RAASet_clicked();

    void on_RABSet_clicked();

    void on_BtnUp_clicked();

    void on_BtnDown_clicked();

private:
    Ui::dlgShelfSearch *ui;
};

#endif // DLGSHELFSEARCH_H
