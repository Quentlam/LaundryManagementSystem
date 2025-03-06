#include "code128generator.h"
#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <QDebug>
#include <QThread>
#include "qzint.h"

code128Generator::code128Generator(QString OrderID):
    OrderID(OrderID)
{
    qDebug() << "当前生成Code128的订单号为：" << this->OrderID;

}



char code128Generator::calculateChecksum(const QString &data) {
    int sum = 104;  // CODE-B的起始符加权
    for(int i=0; i<data.length();  i++){
        sum += (data[i].toLatin1() - 32) * (i+1);
    }
    return static_cast<char>(sum % 103 + 32);
}

Ref<QImage> code128Generator::GenerateCode128()
{
    Zint::QZint bc;
    Zint::QZint::AspectRatioMode ar = Zint::QZint::KeepAspectRatio;
    //init
    bc.setText(OrderID);
    bc.setSymbol(BARCODE_CODE128);//BARCODE_QRCODE二维码
    //bc.setErrorLevel(QZINT_ERROR_LEVEL_L);  // 设置错误级别
    bc.setSecurityLevel(0);

    const int paperWidthMM = 80;          // 纸张物理宽度
    const int printerDPI = 203;           // 热敏打印机典型分辨率
    const int printableWidth = paperWidthMM - 5 * 2; // 留出5mm双边距
    bc.setShowText(false);
    // 毫米转像素公式：pixels = (mm * DPI) / 25.4
    int targetWidthPx = static_cast<int>((printableWidth * printerDPI) / 25.4); // ≈70mm→560px
    int targetHeightPx = static_cast<int>(targetWidthPx / 3); // 2:1 比例

    //绘制一维码
    Ref<QImage> image = std::make_unique<QImage>(QSize(targetWidthPx,targetHeightPx),QImage::Format_RGB32);
    QPainter painter(image.get());
    bc.render(painter,image->rect(),ar);
    painter.end();
    image->save("barcode.png");
    return image;
}
