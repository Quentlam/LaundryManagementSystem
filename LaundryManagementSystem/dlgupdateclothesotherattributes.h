#ifndef DLGUPDATECLOTHESOTHERATTRIBUTES_H
#define DLGUPDATECLOTHESOTHERATTRIBUTES_H

#include <QDialog>
#include "laundrymanagementlogger.h"



namespace Ui {
class dlgUpdateClothesOtherAttributes;
}

class dlgUpdateClothesOtherAttributes : public QDialog
{
    Q_OBJECT

public:
    dlgUpdateClothesOtherAttributes(QWidget *parent = nullptr,int chosedRadio = 1,QString currentID = "无ID",QString currentText = "无");
    ~dlgUpdateClothesOtherAttributes();
    int chosenRadio;
    QString currentID;
    QString currentText;
    Operate operate;



private slots:
    void on_BtnEnter_clicked();

private:
    Ui::dlgUpdateClothesOtherAttributes *ui;
};

#endif // DLGUPDATECLOTHESOTHERATTRIBUTES_H
