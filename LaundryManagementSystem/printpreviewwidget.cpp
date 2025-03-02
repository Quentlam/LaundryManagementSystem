#include "printpreviewwidget.h"

PrintPreviewWidget::PrintPreviewWidget(QWidget *parent,QString text)
    :QWidget(parent),text(text)
{
    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    // 创建文本编辑器用于输入内容
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("请输入要打印的内容...");
    layout->addWidget(textEdit);
    textEdit->setText(text);
    // 创建按钮
    QPushButton *previewBtn = new QPushButton("预览", this);
    connect(previewBtn, &QPushButton::clicked, this, &PrintPreviewWidget::showPreview);
    layout->addWidget(previewBtn);

    QPushButton *printBtn = new QPushButton("打印", this);
    connect(printBtn, &QPushButton::clicked, this, &PrintPreviewWidget::doPrint);
    layout->addWidget(printBtn);
}
