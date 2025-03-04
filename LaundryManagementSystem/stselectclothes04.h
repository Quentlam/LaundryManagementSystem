#ifndef STSELECTCLOTHES04_H
#define STSELECTCLOTHES04_H

#include <QDialog>

namespace Ui {
class STSelectClothes04;
}

class STSelectClothes04 : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothes04(QWidget *parent = nullptr);
    ~STSelectClothes04();
    QString message;

    void reFresh();
    bool searchClothes(QString text);
signals:
   void chosenMessage();
private slots:
   void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::STSelectClothes04 *ui;
};

#endif // STSELECTCLOTHES04_H
