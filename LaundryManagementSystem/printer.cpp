#include "printer.h"
#include <QApplication>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QSizeF>
#include "pulic.h"
#include <QDate>
#include <QDebug>
#include <QPrintDialog>
#include "shopdata.h"
#include <QSqlError>
#include "QZXing.h"


Printer::Printer()
{

}

void Printer::printCustomerCurrentOrder(OrderInfo order)
{
    QString text;
    CodeGenerator = new code128Generator(order.orderID);
    CodeGenerator->GenerateCode128();
    auto sqlPtr = pulic::getInstance()->sql;
    sqlPtr->exec("select * from ShopData");
    ShopData shopData;
    while(sqlPtr->next())
    {
        shopData.ShopID          = sqlPtr->value(0).toString();
        shopData.ShopName        = sqlPtr->value(1).toString();
        shopData.ShopAddress     = sqlPtr->value(2).toString();
        shopData.SearchPhone     = sqlPtr->value(3).toString();
        shopData.ComplaintsPhone = sqlPtr->value(4).toString();
        shopData.AdvertiseMent   = sqlPtr->value(5).toString();
    }

    QString tittle = "    " + *pulic::getInstance()->currentAddress + "服务点（洗衣单）";
    tittle += "\n          客户联";
    //////////////////////////这里生成流水号的Code128码
    tittle += QString("\n打印日期：%1 %2").arg(QDate::currentDate().toString()).arg(QTime::currentTime().toString());



    text += tittle;
    text += "\n---------------------------------\n";

    QString type = "编号  名称  颜色  品牌  价格";
    text += type;
    text += "\n---------------------------------\n";
    QString ShelfsOccupied;
    ShelfsOccupied      += order.ShelfID + " ";//首先记录一下当前已经选择好的格架
    for(int i = 0 ; i < order.clothesTemp.size(); i ++)
    {
         if(i % pulic::getInstance()->shelfCount == 0 && i >= pulic::getInstance()->shelfCount - 1)//如果超过了最大格架数，那么就要换到下一个格架去了
         {
            order.ShelfID = incrementPrefix(order.ShelfID);
            bool occupySuccess = shelfOccupy(order.ShelfID);
            while(!occupySuccess)//如果每次都不成功，就继续增加架子号
            {
                order.ShelfID = incrementPrefix(order.ShelfID);
                occupySuccess = shelfOccupy(order.ShelfID);
            }
            ShelfsOccupied   += order.ShelfID + " ";//然后再记录一下之后选择好的格架
         }
         QString ShelfNum     = order.ShelfID + QString("-%1").arg(i,2,10,QLatin1Char('0'));
         QString ClothesName  = order.clothesTemp[i].Name;
         QString ClothesColor = order.clothesTemp[i].Color;
         QString ClothesBrand = order.clothesTemp[i].Brand;
         QString ClothesPrice = order.clothesTemp[i].Price;
         if(order.clothesTemp[i].Name.isNull())
         {
             ClothesName = " ";
         }
         if(order.clothesTemp[i].Color.isNull())
         {
             ClothesColor = " ";
         }
         if(order.clothesTemp[i].Brand.isNull())
         {
             ClothesBrand = " ";
         }
         if(order.clothesTemp[i].Price.isNull())
         {
             ClothesPrice = " ";
         }
         text += ShelfNum + " " + ClothesName + " " + ClothesColor + " " + ClothesBrand + " " + ClothesPrice + '\n';
    }

    recordShelves(order.orderID,ShelfsOccupied);//修改一下订单里一共有多少个架号被占用了
    text += "\n----------------------------------\n";
    text += QString("合计；          衣物%1件\n").arg(order.clothesTemp.size());
    text += QString("付款方式：%1").arg(order.PayWay);
    text += QString(" 总金额：%1元\n").arg(order.MoneyCount);
    text += QString("折扣率：%1").arg(order.Discount);
    text += QString(" 应收金额：%1元\n").arg(order.AfterDiscountMoneyCount);
    text += QString("充值卡号：%1\n").arg(order.customerCardID);
    text += QString("卡余额：%1元\n").arg(order.CustomerCardMoney);
    text += QString("实收金额：%1元\n").arg(order.InputMoney);
    text += QString("找零：%1元\n").arg(order.OutputMoney);
    text += "\n----------------------------------\n";


    text += QString("客户代号：%1\n").arg(order.customerID);
    text += QString("店员姓名：%1\n").arg(pulic::getInstance()->currentUser->userInformation.Name);
    text += QString("客户姓名：%1\n").arg(order.customerName);
    text += QString("取衣日期：%1\n").arg(order.GetClothesDate);
    text += QString("查询电话：%1\n").arg(shopData.SearchPhone);
    text += QString("本店地址：%1\n").arg(shopData.ShopAddress);
    text += QString("投诉电话：%1\n").arg(shopData.ComplaintsPhone);

    text += "\n----------------------------------\n";

    text += shopData.AdvertiseMent;


    text += "\n----------------------------------\n";
    text += "我对以上打印内容确认无误\n";
    text += "\n----------------------------------\n";
    text += "顾客签名：\n";
    text += "\n";
    text += "电话：\n";
    text += "\n";

    // 打印机初始化
    QPrinter printer;
    // 指定打印机名称
    printer.setPrinterName("CHITENG-CT320B");

    // 设置纸张大小80*30mm（由于setPageSize默认设置中没有对应的纸张，所以需要转一手设置）
    QPageSize customPageSize(QSizeF(80, 80), QPageSize::Millimeter);

    // 纸张大小设定
    printer.setPageSize(customPageSize);

    //设置打印方向为横向
    printer.setPageOrientation(QPageLayout::Portrait);

    // 设置打印分辨率为300 DPI（常规设置，够用了）
    printer.setResolution(300);

    //设置打印份数
    printer.setCopyCount(1);

    // 另起一页，可以避免第一次使用时出现打印2次的情况
    printer.newPage();


//    // 使用QPainter在打印机上绘制图片
//    QPainter painter(&printer);

//    // 开始绘制
//    painter.begin(&printer);

//    QImage img =  QZXing::encodeData(order.orderID

//                  ,QZXing::EncoderFormat::EncoderFormat_QR_CODE

//                  ,QSize(80,80)

//                  ,QZXing::EncodeErrorCorrectionLevel::EncodeErrorCorrectionLevel_H

//                  ,true

//                  ,false);


//    // 调整打印坐标的图片大小，以适应页面大小或保持图片的比例
//    qreal scaleX = printer.width() / img.width();
//    qreal scaleY = printer.height() / img.height();
//    qreal scale  = qMin(scaleX, scaleY);


//    // 生成坐标和区域参数（二维码居中偏上，已调）
//    QRect rect((printer.width() - img.width() * scale) / 2 - 25,
//               (printer.height() - img.height() * scale) / 2 - 6,
//               img.width() * scale,
//               img.height() * scale);

//    // 在坐标参数下打印图片
//    painter.drawImage(rect, img);

//    // 保存结果
//    painter.save();

//    // 设置文本字体
//    QFont font("MS Reference Sans Serif", 10);
//    painter.setFont(font);

//    // 将绘制原点移到文本区域的中心
//    painter.translate(rect.center());

//    // 根据实际逆时针方向旋转文本（实际需要旋转270°）
//    painter.rotate(270);

//    //在二维码底部绘制文本（根据实际情况调整坐标，已调整）
//    painter.drawText(QPointF(-rect.width() / 2 + 8,rect.height() / 2 + 55), order.orderID);

//    // 恢复设置，可以避免第一次使用时出现打印2次的情况
//    painter.restore();

//    // 完成绘制
//    painter.end();


    qDebug() << text.split("\n");
}

void Printer::printSelectedOrder(QList<OrderInfo> order)
{

}

void Printer::printUserCurrentOrder(OrderInfo order)
{

}

void Printer::printTest()
{
    QString text = "Hello, Thermal Printer!\n这是打印的内容。\n加上一些额外的内容来测试动态高度。\n";
    CodeGenerator = new code128Generator("12345678");//这里只是测试
    CodeGenerator->GenerateCode128();
    // 创建 QTextDocument 文档并设置内容
    QTextDocument textDocument;
    textDocument.setPlainText(text);

    // 计算文本的宽高
    QSizeF textSize = textDocument.size();

    // 创建 QPrinter 对象，指定使用高分辨率模式
    QPrinter printer(QPrinter::HighResolution);

    // 设置纸张宽度为 80mm，高度为根据文本高度动态计算
    qreal paperWidth = 80; // 80mm
    qreal paperHeight = textSize.height() + 20; // 额外加上一定的边距，比如 20mm
    printer.setPaperSize(QSizeF(paperWidth, paperHeight), QPrinter::Millimeter);

    // 设置其他打印参数
    printer.setOutputFormat(QPrinter::NativeFormat); // 设置输出格式
    printer.setOrientation(QPrinter::Portrait); // 设置打印方向为纵向

    // 打印内容
    QPainter painter(&printer);
    textDocument.drawContents(&painter);
    painter.end();

}

QString Printer::incrementPrefix(const QString& input)
{
    // 找到 '-' 的位置
    int dashPos = input.indexOf('-');
    if (dashPos == -1) {
        return input; // 如果没有找到 '-', 返回原始字符串
    }

    // 提取前缀和后缀
    QString prefix = input.left(dashPos); // 获取前缀
    QString suffix = input.mid(dashPos);   // 获取后缀

    // 提取数字部分
    QString numberPart;
    for (QChar c : prefix) {
        if (c.isDigit()) {
            numberPart.append(c);
        } else {
            // 遇到非数字字符，停止提取
            break;
        }
    }

    // 将数字部分转换为整数
    bool ok;
    int number = numberPart.toInt(&ok);
    if (!ok) {
        return input; // 如果转换失败，返回原始字符串
    }

    number++; // 增加1

    // 将数字格式化回字符串，保持前导零
    QString formattedNumber = QString("%1").arg(number, numberPart.length(), 10, QChar('0'));

    // 重新组合字符串
    return formattedNumber + prefix.mid(numberPart.length()) + suffix;
}

bool Printer::shelfOccupy(QString ShelfID)
{
    auto sqlPtr = pulic::getInstance()->sql;
    auto shelfOccupyStatus = sqlPtr->exec(QString("update Shelf%1 set ShelfStatus = '已上架' where ShelfID = '%2';").arg(ShelfID.at(4)).arg(ShelfID.left(5)));
    if(false == shelfOccupyStatus)
    {

    }
    return shelfOccupyStatus;//看看上架成功没有
}

void Printer::recordShelves(QString OrderID,QString& Shelves)
{
    auto sqlPtr = pulic::getInstance()->sql;
    auto OrderLogShelfStatus = sqlPtr->exec(QString("UPDATE OrderLog SET ShelfID = '%1' where OrderID = '%2';").arg(Shelves).arg(OrderID));
    auto OrderStatusShelfStatus = sqlPtr->exec(QString("UPDATE OrderStatus SET ShelfID = '%1' where OrderID = '%2';").arg(Shelves).arg(OrderID));
    if(false == OrderLogShelfStatus || false == OrderStatusShelfStatus)
    {
        qDebug() << sqlPtr->lastError().text();
    }

}
