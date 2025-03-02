#ifndef PRINTPREVIEWWIDGET_H
#define PRINTPREVIEWWIDGET_H

#include <QObject>
#include <QWidget>

class PrintPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrintPreviewWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PRINTPREVIEWWIDGET_H