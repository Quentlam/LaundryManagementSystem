#ifndef DLGADDCLOTHESOTHERATTRIBUTES_H
#define DLGADDCLOTHESOTHERATTRIBUTES_H

#include <QDialog>
#include "laundrymanagementlogger.h"



namespace Ui {
class dlgAddClothesOtherAttributes;
}

class dlgAddClothesOtherAttributes : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAddClothesOtherAttributes(QWidget *parent = nullptr,int chosenRadio = 0);
    ~dlgAddClothesOtherAttributes();
    int chosenRadio;
    Operate operate;
    int exec();
private slots:
    void on_BtnEnter_clicked();

private:
    Ui::dlgAddClothesOtherAttributes *ui;
};

#endif // DLGADDCLOTHESOTHERATTRIBUTES_H
