#ifndef DLGCHOSESHELF_H
#define DLGCHOSESHELF_H

#include <QDialog>

namespace Ui {
class dlgChoseShelf;
}

class dlgChoseShelf : public QDialog
{
    Q_OBJECT

public:
    explicit dlgChoseShelf(QWidget *parent = nullptr);
    ~dlgChoseShelf();

    int exec();
    void reFresh();
    QString shelfNumber;
    bool shelfSelected;
    void keyPressEvent(QKeyEvent *);
    void close();
private slots:
    void on_RAASet_clicked();

    void on_RABSet_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_BtnCancel_clicked();

    void on_BtnEnter_clicked();

private:
    Ui::dlgChoseShelf *ui;

signals:
    void choseShelfSuccess();
};

#endif // DLGCHOSESHELF_H
