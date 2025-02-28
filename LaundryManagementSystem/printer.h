#ifndef PRINTER_H
#define PRINTER_H
#include "orderinfo.h"
#include "code128generator.h"


class Printer
{
public:
    Printer();
    void printTest();
    void printUserCurrentOrder(OrderInfo order);
    void printSelectedOrder(QList<OrderInfo> order);
    void printCustomerCurrentOrder(OrderInfo order);
    QString incrementPrefix(const QString &input);
    bool shelfOccupy(QString ShelfID);
    void recordShelves(QString OrderID, QString &Shelves);

    code128Generator* CodeGenerator;

};

#endif // PRINTER_H
