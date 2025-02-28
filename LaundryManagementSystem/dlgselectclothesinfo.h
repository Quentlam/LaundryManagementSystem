#ifndef DLGSELECTCLOTHESINFO_H
#define DLGSELECTCLOTHESINFO_H

#include <QDialog>
#include "clothesinfo.h"
namespace Ui {
class dlgSelectClothesInfo;
}

class dlgSelectClothesInfo : public QDialog
{
    Q_OBJECT

public:
    dlgSelectClothesInfo(QWidget *parent = nullptr,QList<SelectClothesInfo> selectClothesInfo = QList<SelectClothesInfo>());
    ~dlgSelectClothesInfo();
    QList<SelectClothesInfo> temp;


    int exec();
    void reFresh();
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::dlgSelectClothesInfo *ui;
};

#endif // DLGSELECTCLOTHESINFO_H
