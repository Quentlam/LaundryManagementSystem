#ifndef PRINTER_H
#define PRINTER_H
#include "orderinfo.h"
#include "code128generator.h"
#include <QTextDocument>
#include <QPrinter>
#include <QWidget>
#include <QPen>
#include <QPainter>


class Printer: public QWidget
{
public:
    Printer();
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

    void makeSelectOrderTittleDocument(QTextDocument &tittleDocument, std::unique_ptr<QList<OrderInfo> > order);
    void makeSelectOrderTextDocument(QTextDocument &textDocument, std::unique_ptr<QList<OrderInfo> > order);
private:
    static Scope<QPrinter> mPrinter;

};

#endif // PRINTER_H
