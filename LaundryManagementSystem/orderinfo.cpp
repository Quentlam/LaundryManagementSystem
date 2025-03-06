#include "orderinfo.h"

QList<QString> OrderInfo::orderTittle = {
                                    "订单流水号",
                                    "客户编号",
                                    "客户姓名",
                                    "客户电话",
                                    "客户消费次数",
                                    "客户消费额",
                                    "客户卡号",
                                    "衣服名称",
                                    "衣服颜色",
                                    "衣服瑕疵",
                                    "衣服品牌",
                                    "特殊处理",
                                    "洗后效果",
                                    "价格",
                                    "订单总金额",
                                    "折扣率",
                                    "订单折后价",
                                    "衣服总数",
                                    "支付后卡余额",
                                    "收银",
                                    "找零",
                                    "支付方式",
                                    "客户当时欠缴情况",
                                    "取衣日期",
                                    "客户地址",
                                    "架号",
                                    "此订单未支付",
                                    "卡上金额"
                                };

QList<QString> OrderStatus::orderStatusTittle =
                                {
                                    "订单流水号",
                                    "订单状态",
                                    "衣服收发情况",
                                    "客户编号",
                                    "客户姓名",
                                    "架号"
                                };

OrderInfo::OrderInfo()
{

}

OrderInfo::~OrderInfo()
{

}

OrderStatus::OrderStatus()
{

}

OrderStatus::~OrderStatus()
{

}

OrderClothesAttributeMessage::OrderClothesAttributeMessage()
{

}

OrderClothesAttributeMessage::~OrderClothesAttributeMessage()
{

}
