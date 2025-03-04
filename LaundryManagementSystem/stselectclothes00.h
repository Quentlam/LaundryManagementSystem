#ifndef STSELECTCLOTHES00_H
#define STSELECTCLOTHES00_H

#include <QDialog>

namespace Ui {
class STSelectClothes00;
}

class STSelectClothes00 : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothes00(QWidget *parent = nullptr);
    ~STSelectClothes00();
    QString message;

    void reFresh();
    bool searchClothes(QString text);
private:
    Ui::STSelectClothes00 *ui;

signals:
    void chosenMessage();

private slots:
    void on_tableWidget_cellClicked(int row, int column);
};

#endif // STSELECTCLOTHES00_H
