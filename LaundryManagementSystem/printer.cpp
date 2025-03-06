#include "printer.h"
#include <QApplication>
#include <QPainter>
#include <QSizeF>
#include "pulic.h"
#include <QDate>
#include <QDebug>
#include <QPrintDialog>
#include <QTextCursor>
#include "shopdata.h"
#include <QSqlError>
#include <QPrinterInfo>
#include <QFont>
#include <QTextCodec>
#include <QThread>

Printer::Printer()
{
    mPrinter.setPrinterName("Zonerich AB-88H");
}

void Printer::printCustomerCurrentOrder(OrderInfo order)
{
    QTextDocument tittleDocument;
    makeCurrentOrderTittleDocument(tittleDocument,order);//先创建标题的Document

    QTextDocument textDocument;//再创建正文的Document
    makeCusotmerCurrentOrderDocument(textDocument,order);

    set80mmPaperPrinter(tittleDocument.size(),textDocument.size());//这是设置纸张大小


    CodeGenerator = new code128Generator(order.orderID);///////////////生成条纹码
    Ref<QImage> beforImg = CodeGenerator->GenerateCode128();
    QImage img = beforImg->scaled(420,40, Qt::IgnoreAspectRatio);
////////////////////////////////////////////////////////////////////////////////////////////以下是绘画逻辑
    QPainter painter(&mPrinter); // 构造函数自动激活设备
    painter.setRenderHint(QPainter::HighQualityAntialiasing,  true); // 启用抗锯齿

    painter.save();
    tittleDocument.drawContents(&painter);//这个是先写标头
    painter.restore(); // 恢复状态

    QRect docBoundingRect = getDocumentBoundingRect(tittleDocument);
    int docWidth = docBoundingRect.width();
    int docHeight = docBoundingRect.height();


    painter.save(); // 保存当前状态
    int imageX = 10 + (docWidth - img.width()) / 2;
    int imageY = 10 + docHeight; // 图像放在文档下方
    painter.drawImage(QPoint(imageX, imageY),  img);//然后再画流水号的条纹码
    painter.restore(); // 恢复状态

    // 绘制第二个 QTextDocument
    painter.save(); // 保存当前状态
    painter.translate(10, 10 + docHeight + img.height() + 10); // 计算第二个文档的起始位置
    textDocument.drawContents(&painter);
    painter.restore(); // 恢复状态

    painter.end();  // 显式结束绘制（非必须但推荐）
}




void Printer::printSelectedOrder(QList<OrderInfo> order)
{

}

void Printer::printUserCurrentOrder(OrderInfo order)
{
    QTextDocument tittleDocument;
    makeCurrentOrderTittleDocument(tittleDocument,order);//先创建标题的Document

    QTextDocument textDocument;//再创建正文的Document
    makeUserCurrentOrderDocument(textDocument,order);

    set80mmPaperPrinter(tittleDocument.size(),textDocument.size());//这是设置纸张大小
////////////////////////////////////////////////////////////////////////////////////////////以下是绘画逻辑
    QPainter painter(&mPrinter); // 构造函数自动激活设备
    painter.setRenderHint(QPainter::HighQualityAntialiasing,  true); // 启用抗锯齿
    // 定义绘制位置
    int margin = 20;  // 边距
    qreal doc1Height = tittleDocument.size().height();
    qreal doc2Height = tittleDocument.size().height();
    qreal totalHeight = doc1Height + doc2Height + 3 * margin; // 包含边距

    painter.save();
    tittleDocument.drawContents(&painter);//这个是先写标头
    painter.restore(); // 恢复状态


    painter.save();
    painter.translate(margin, doc1Height + 2 * margin); // 设置绘制位置
    textDocument.drawContents(&painter);
    painter.restore(); // 恢复状态

    painter.end();  // 显式结束绘制（非必须但推荐）
}

void Printer::makeUserCurrentOrderDocument(QTextDocument& textDocument,OrderInfo order)
{
    // 另起一页
    //mPrinter.newPage(); // 这行代码会将当前页面结束并开始新的一页
    QString text;
    auto sqlPtr = GET_SQL_POINTER;
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
    text += QString("\n打印日期：%1 %2").arg(QDate::currentDate().toString()).arg(QTime::currentTime().toString());
    text += "\n---------------------------------------\n";
    QString type = "编号   名称   颜色   品牌   价格";
    text += type;
    text += "\n---------------------------------------\n";
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
         if(order.clothesTemp[i].Name.isNull() || order.clothesTemp[i].Name.size() < 1)
         {
             ClothesName = "---- ";
         }
         if(order.clothesTemp[i].Color.isNull()|| order.clothesTemp[i].Color.size() < 1)
         {
             ClothesColor = "---- ";
         }
         if(order.clothesTemp[i].Brand.isNull()|| order.clothesTemp[i].Brand.size() < 1)
         {
             ClothesBrand = "---- ";
         }
         if(order.clothesTemp[i].Price.isNull()|| order.clothesTemp[i].Price.size() < 1)
         {
             ClothesPrice = "---- ";
         }
         text += ShelfNum + " " + ClothesName + " " + ClothesColor + " " + ClothesBrand + " " + ClothesPrice + '\n';
    }

    recordShelves(order.orderID,ShelfsOccupied);//修改一下订单里一共有多少个架号被占用了
    text += "\n---------------------------------------\n";
    text += QString("合计；    衣物%1件\n").arg(order.clothesTemp.size());
    text += QString("付款方式：%1\n")      .arg(order.PayWay);
    text += QString("总金额：%1元\n")   .arg(order.MoneyCount);
    text += QString("卡上金额：%1元\n")    .arg(order.customerCardMoneyBeforePay);
    text += QString("折扣率：%1 ")        .arg(order.Discount);
    text += QString("应收金额：%1元\n") .arg(order.AfterDiscountMoneyCount);
    text += QString("充值卡号：%1\n")    .arg(order.customerCardID);
    text += QString("卡余额：%1元\n")    .arg(order.CustomerCardMoney);
    text += QString("实收金额：%1元\n")   .arg(order.InputMoney);
    text += QString("找零：%1元")      .arg(order.OutputMoney);
    if(order.thisOrderNotPaid.contains("欠缴"))
    text += QString("欠缴：%1元 欠！").arg(order.thisOrderNotPaid);
    text += "\n---------------------------------------\n";


    text += QString("客户代号：%1").arg(order.customerID);
    text += QString(" 店员姓名：%1\n").arg((*pulic::getInstance()).currentUser->Name);
    text += QString("客户姓名：%1\n").arg(order.customerName);
    text += QString("取衣日期：%1\n").arg(order.GetClothesDate);
    text += "\n---------------------------------------\n";

    textDocument.setTextWidth(mPrinter.pageRect().width()); // 减去一定的边距
    QFont font("SimHei",10);  // 获取默认字体
    font.setStyleStrategy(QFont::PreferAntialias);  // 优先使用抗锯齿
    font.setHintingPreference(QFont::PreferFullHinting);  // 优先使用全提示
    textDocument.setDefaultFont(font);  // 更新默认字体
    textDocument.setPlainText(text);
}

void Printer::makeCusotmerCurrentOrderDocument(QTextDocument& textDocument,OrderInfo order)
{
    QString text;
    auto sqlPtr = GET_SQL_POINTER;
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
    text += QString("\n打印日期：%1 %2").arg(QDate::currentDate().toString()).arg(QTime::currentTime().toString());
    text += "\n---------------------------------------\n";
    QString type = "编号   名称   颜色   品牌   价格";
    text += type;
    text += "\n---------------------------------------\n";
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
         if(order.clothesTemp[i].Name.isNull() || order.clothesTemp[i].Name.size() < 1)
         {
             ClothesName = "---- ";
         }
         if(order.clothesTemp[i].Color.isNull()|| order.clothesTemp[i].Color.size() < 1)
         {
             ClothesColor = "---- ";
         }
         if(order.clothesTemp[i].Brand.isNull()|| order.clothesTemp[i].Brand.size() < 1)
         {
             ClothesBrand = "---- ";
         }
         if(order.clothesTemp[i].Price.isNull()|| order.clothesTemp[i].Price.size() < 1)
         {
             ClothesPrice = "---- ";
         }
         text += ShelfNum + " " + ClothesName + " " + ClothesColor + " " + ClothesBrand + " " + ClothesPrice + '\n';
    }

    recordShelves(order.orderID,ShelfsOccupied);//修改一下订单里一共有多少个架号被占用了

    text += "\n---------------------------------------\n";
    text += QString("合计；    衣物%1件\n").arg(order.clothesTemp.size());
    text += QString("付款方式：%1\n")      .arg(order.PayWay);
    text += QString("总金额：%1元\n")   .arg(order.MoneyCount);
    text += QString("卡上金额：%1元\n")    .arg(order.customerCardMoneyBeforePay);
    text += QString("折扣率：%1 ")        .arg(order.Discount);
    text += QString("应收金额：%1元\n") .arg(order.AfterDiscountMoneyCount);
    text += QString("充值卡号：%1\n")    .arg(order.customerCardID);
    text += QString("卡余额：%1元\n")    .arg(order.CustomerCardMoney);
    text += QString("实收金额：%1元\n")   .arg(order.InputMoney);
    text += QString("找零：%1元")      .arg(order.OutputMoney);
    if(order.thisOrderNotPaid.contains("欠缴"))
    text += QString("欠缴：%1元 欠！").arg(order.thisOrderNotPaid);
    text += "\n---------------------------------------\n";


    text += QString("客户代号：%1").arg(order.customerID);
    text += QString(" 店员姓名：%1\n").arg((*pulic::getInstance()).currentUser->Name);
    text += QString("客户姓名：%1\n").arg(order.customerName);
    text += QString("取衣日期：%1\n").arg(order.GetClothesDate);
    text += QString("查询电话：%1\n").arg(shopData.SearchPhone);
    text += QString("本店地址：%1\n").arg(shopData.ShopAddress);
    text += QString("投诉电话：%1").arg(shopData.ComplaintsPhone);
    text += "\n---------------------------------------\n";

    text += shopData.AdvertiseMent;


    text += "\n---------------------------------------\n";
    text += "我对以上打印内容确认无误\n";
    text += "\n---------------------------------------\n";
    text += "顾客签名：  \n";
    text += "电话：     \n";
    text += "          \n";
    text += "          \n";
    text += "\n---------------------------------------\n";

    textDocument.setTextWidth(mPrinter.pageRect().width()); // 减去一定的边距
    QFont font("SimHei",10);  // 获取默认字体
    font.setStyleStrategy(QFont::PreferAntialias);  // 优先使用抗锯齿
    font.setHintingPreference(QFont::PreferFullHinting);  // 优先使用全提示
    textDocument.setDefaultFont(font);  // 更新默认字体
    textDocument.setPlainText(text);
}

void Printer::makeCurrentOrderTittleDocument(QTextDocument& tittleDocument,OrderInfo order)
{
    QString tittle;
    tittle = +"        " + *pulic::getInstance()->currentAddress + "服务点（洗衣单）";
    tittle += "\n   ---------------------------------   \n";
    tittle += QString("           流水号：%1").arg(order.orderID);
    tittleDocument.setTextWidth(mPrinter.pageRect().width()); // 减去一定的边距
    QFont font("SimHei",10);  // 获取默认字体
    font.setStyleStrategy(QFont::PreferAntialias);  // 优先使用抗锯齿
    font.setHintingPreference(QFont::PreferFullHinting);  // 优先使用全提示
    tittleDocument.setDefaultFont(font);  // 更新默认字体
    tittleDocument.setPlainText(tittle);
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
    printer.setResolution(300);
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
    auto sqlPtr = GET_SQL_POINTER;
    auto shelfOccupyStatus = sqlPtr->exec(QString("update Shelf%1 set ShelfStatus = '已上架' where ShelfID = '%2';").arg(ShelfID.at(4)).arg(ShelfID.left(5)));
    if(false == shelfOccupyStatus)
    {

    }
    return shelfOccupyStatus;//看看上架成功没有
}

void Printer::recordShelves(QString OrderID,QString& Shelves)
{
    auto sqlPtr = GET_SQL_POINTER;
    auto OrderLogShelfStatus = sqlPtr->exec(QString("UPDATE OrderLog SET ShelfID = '%1' where OrderID = '%2';").arg(Shelves).arg(OrderID));
    auto OrderStatusShelfStatus = sqlPtr->exec(QString("UPDATE OrderStatus SET ShelfID = '%1' where OrderID = '%2';").arg(Shelves).arg(OrderID));
    if(false == OrderLogShelfStatus || false == OrderStatusShelfStatus)
    {
        qDebug() << sqlPtr->lastError().text();
    }

}

QRect Printer::getDocumentBoundingRect(QTextDocument &doc) {
    QSizeF size = doc.size(); // 获取文档的尺寸
    return QRect(0, 0, size.width(), size.height()); // 创建 QRect
}

void Printer::set80mmPaperPrinter(QSizeF tittleDocumentSize,QSizeF textDocumentSize)
{
    // 设置自定义纸张尺寸（注意：部分打印机不支持自定义尺寸）
    // 计算文本的宽高（以点为单位）
    QSizeF textSize = tittleDocumentSize + textDocumentSize;
    // 将点转换为毫米
    qreal heightInMM = textSize.height() * 25.4 / 72;
    // 额外加上边距，比如 20mm
    qreal paperHeight = heightInMM; // 20mm边距
    QPageSize customPageSize(QSizeF(80, paperHeight), QPageSize::Millimeter);
    mPrinter.setPageSize(customPageSize);
}


