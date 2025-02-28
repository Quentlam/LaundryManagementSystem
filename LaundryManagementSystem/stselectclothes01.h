#ifndef SWPAGE01_H
#define SWPAGE01_H

#include <QDialog>

namespace Ui {
class STSelectClothes01;
}

class STSelectClothes01 : public QDialog
{
    Q_OBJECT

public:
    explicit STSelectClothes01(QWidget *parent = nullptr);
    ~STSelectClothes01();
     QString message;

     void reFresh();
     void keyPressEvent(QKeyEvent *event);
     void lineFocus();
signals:
    void chosenMessage();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::STSelectClothes01 *ui;
};

#endif // SWPAGE01_H
