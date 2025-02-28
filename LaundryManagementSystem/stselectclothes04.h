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
    void keyPressEvent(QKeyEvent *event);
    void lineFocus();
signals:
   void chosenMessage();
private slots:
   void on_tableWidget_cellClicked(int row, int column);

   void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::STSelectClothes04 *ui;
};

#endif // STSELECTCLOTHES04_H
