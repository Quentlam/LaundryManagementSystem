#ifndef PRINTER_H
#define PRINTER_H
#include "orderinfo.h"
#include "code128generator.h"
#include <QTextDocument>
#include <QPrinter>

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
    QRect getDocumentBoundingRect(QTextDocument &doc);

    void makeCurrentOrderTittleDocument(QTextDocument& tittleDocument, OrderInfo order);
    void makeUserCurrentOrderDocument(QTextDocument& textDocument, OrderInfo order);
    void makeCusotmerCurrentOrderDocument(QTextDocument& textDocument, OrderInfo order);
    void set80mmPaperPrinter(QSizeF tittleDocumentSize, QSizeF textDocument);
private:
    QPrinter mPrinter;

};

#endif // PRINTER_H
