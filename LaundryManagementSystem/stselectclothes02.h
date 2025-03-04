#ifndef STSELECTCLOTHES02_H
#define STSELECTCLOTHES02_H

#include <QDialog>

namespace Ui {
class STSelectClothes02;
}

class STSelectClothes02 : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothes02(QWidget *parent = nullptr);
    ~STSelectClothes02();
    QString message;

    void reFresh();
    bool searchClothes(QString text);
signals:
   void chosenMessage();
private slots:
   void on_tableWidget_cellClicked(int row, int column);
private:
    Ui::STSelectClothes02 *ui;
};

#endif // STSELECTCLOTHES02_H
