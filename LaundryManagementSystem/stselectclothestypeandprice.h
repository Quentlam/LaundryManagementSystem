#ifndef STSELECTCLOTHESTYPEANDPRICE_H
#define STSELECTCLOTHESTYPEANDPRICE_H

#include <QDialog>

namespace Ui {
class STSelectClothesTypeAndPrice;
}

class STSelectClothesTypeAndPrice : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothesTypeAndPrice(QWidget *parent = nullptr);
    ~STSelectClothesTypeAndPrice();
    void choseClothes(int type = 0);
    QString Name;
    QString Price;

    bool searchClothes(QString text);
private slots:
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::STSelectClothesTypeAndPrice *ui;

signals:
    void chosenClothesType();
};

#endif // STSELECTCLOTHESTYPEANDPRICE_H
