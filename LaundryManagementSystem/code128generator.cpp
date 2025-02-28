#include "code128generator.h"
#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <QDebug>

code128Generator::code128Generator(QString OrderID):
    OrderID(OrderID)
{
    qDebug() << "当前生成Code128的订单号为：" << OrderID;
}



char code128Generator::calculateChecksum(const QString &data) {
    int sum = 104;  // Code128C的起始值为104（自动模式）
    for(int i=0; i<data.length();  i++) {
        sum += (data[i].toLatin1() - 32) * (i+1);
    }
    return static_cast<char>(sum % 103 + 32);
}

void code128Generator::GenerateCode128()
{
    // 设置条码类型为Code128
    QByteArray setBarcodeType = QByteArray::fromHex("1D6B49");  // 49对应Code128

    // 设置条码参数（高度、字符是否显示等）
    QByteArray setBarcodeHeight = QByteArray::fromHex("1D6840");  // 高度64点
    QByteArray showText = QByteArray::fromHex("1D4801");          // 显示条码下方文字

    // 发送条码数据
    QByteArray barcodeData;
    barcodeData.append(0x7B);          // Code128起始符（自动模式）
    barcodeData.append(OrderID);       // 实际数据
    barcodeData.append(calculateChecksum(OrderID));   // 校验位计算（需实现）

    // 完整指令组合
    QByteArray printCmd;
    printCmd.append(setBarcodeType)
            .append(setBarcodeHeight)
            .append(showText)
            .append(barcodeData)
            .append(QByteArray::fromHex("00"));  // 结束符

    QSerialPort serial;
    serial.setPortName("COM3");
    serial.setBaudRate(QSerialPort::Baud19200);

    if(serial.open(QIODevice::WriteOnly))
    {
        // 发送初始化指令
        serial.write(QByteArray::fromHex("1B40"));

        // 发送Code128指令
        QByteArray fullCmd;
        fullCmd.append(printCmd);           // 上述条码指令
        fullCmd.append(QByteArray::fromHex("0A"));   // 换行
        //fullCmd.append(QByteArray::fromHex("1D564200"));   // 切纸(需要切纸，因为这个只是条纹码)
        serial.write(fullCmd);
    }

}
