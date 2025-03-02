#ifndef PRINTPREVIEWWIDGET_H
#define PRINTPREVIEWWIDGET_H

#include <QTextEdit>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPageSize>
#include <QPrintDialog>
#include <QPaintDevice>

class PrintPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrintPreviewWidget(QWidget *parent = nullptr,QString text = "None");
    QString text;
signals:

public slots:
    void showPreview() {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPagedPaintDevice::A4); // 设置页面大小

        QPrintPreviewDialog previewDialog(&printer, this);
        connect(&previewDialog, &QPrintPreviewDialog::paintRequested, [this](QPrinter *printer) {
            textEdit->document()->print(printer);
        });

        previewDialog.exec();
    }

    void doPrint() {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setPageSize(QPagedPaintDevice::A4);

        if (QPrintDialog(&printer,this).exec() == QDialog::Accepted) {
            textEdit->document()->print(&printer);
            printer.newPage();
        }
    }

private:
    QTextEdit* textEdit;
};

#endif // PRINTPREVIEWWIDGET_H
