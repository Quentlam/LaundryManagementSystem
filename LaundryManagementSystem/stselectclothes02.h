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
    void keyPressEvent(QKeyEvent *event);
    void lineFocus();
signals:
   void chosenMessage();
private slots:
   void on_tableWidget_cellClicked(int row, int column);

   void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::STSelectClothes02 *ui;
};

#endif // STSELECTCLOTHES02_H
