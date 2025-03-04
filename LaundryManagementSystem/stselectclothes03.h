#ifndef STSELECTCLOTHES03_H
#define STSELECTCLOTHES03_H

#include <QDialog>

namespace Ui {
class STSelectClothes03;
}

class STSelectClothes03 : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothes03(QWidget *parent = nullptr);
    ~STSelectClothes03();
    QString message;

    void reFresh();
    bool searchClothes(QString text);
signals:
   void chosenMessage();
private slots:
   void on_tableWidget_cellClicked(int row, int column);
private:
    Ui::STSelectClothes03 *ui;
};

#endif // STSELECTCLOTHES03_H
