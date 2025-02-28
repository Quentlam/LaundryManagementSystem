#include "dlgadd.h"
#include "ui_dlgadd.h"
#include <QMessageBox>
#include "pulic.h"
#include "userinfo.h"
#include <QDebug>
#include "mainwindow.h"
#include "customerinfo.h"
#include "clothesinfo.h"
#include <QSqlError>

dlgAdd::dlgAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAdd),
    currentMode(-1)
{
    dlgUC = nullptr;
    ui->setupUi(this);
    connect(ui->ClothesNameAndPrice,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);
    connect(ui->ClothesBrand,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);
    connect(ui->ClothesColor,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);
    connect(ui->ClothesDefect,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);
    connect(ui->ClothesEffect,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);
    connect(ui->ClothesTreatment,&QRadioButton::clicked,this,&dlgAdd::onRadioButtonChanged);


    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    deleteOperate.operate = QString("删除数据");
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->ClothesBrand->hide();
    ui->ClothesTreatment->hide();
    ui->ClothesEffect->hide();
    ui->ClothesColor->hide();
    ui->ClothesNameAndPrice->hide();
    ui->ClothesDefect->hide();
    ui->groupBox->hide();
    ui->ClothesNameAndPrice->setChecked(true);

}



dlgAdd::~dlgAdd()
{
    delete ui;
}



int dlgAdd::choseMode()
{
    currentMode = ui->choseCBox->currentIndex();
    //qDebug() << "现在的模式是：" << currentMode;
    if(0 == currentMode)//如果选择的是客户
    {
        return 0;
    }
    else if(1 == currentMode)//如果选择的是衣物种类
    {
        return 1;
    }
    else if(2 == currentMode)//如果选择的是员工账号
    {
        return 2;
    }
    else return -1;


}

void dlgAdd::reFresh(int index)
{
    auto sqlPtr = pulic::getInstance()->sql;
    currentMode = index;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看客户信息
    if(0 == currentMode)//选择客户
    {
        ui->tableWidget->clear();
        QList<QString> customerTittle;
        QList<customerInfo> customerListTemp;
        customerInfo customerTemp;
        customerTittle << "客户编号" << "客户性别" << "客户姓名"  << "客户电话" << "客户卡号" << "消费额" << "消费次数" << "消费卡种类" << "欠缴情况" << "欠缴余额" << "客户卡剩余余额" << "客户住址" << "客户信用" << "备注";


        sqlPtr->exec("select count(ID) from Customer");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前总客户人数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(customerTittle.size());


        for(int i = 0; i < customerTittle.size() ; i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem (customerTittle[i]));//设置tittle


        sqlPtr->exec("select * from Customer");
        while(sqlPtr->next())//从数据库里把所有的客户查出来
        {
            customerTemp.ID = sqlPtr->value(0).toString();
            customerTemp.Gender = sqlPtr->value(1).toString();
            customerTemp.Name = sqlPtr->value(2).toString();
            customerTemp.Phone = sqlPtr->value(3).toString();
            customerTemp.CardID = sqlPtr->value(4).toString();
            customerTemp.Spend = sqlPtr->value(5).toDouble();
            customerTemp.Count = sqlPtr->value(6).toDouble();
            customerTemp.CardType = sqlPtr->value(7).toString();
            customerTemp.HaveNotPaid = sqlPtr->value(8).toString();
            customerTemp.HaveNotPaidMoney = sqlPtr->value(9).toString();
            customerTemp.CardMoney = sqlPtr->value(10).toDouble();
            customerTemp.Address = sqlPtr->value(11).toString();
            customerTemp.Credit = sqlPtr->value(12).toString();
            customerTemp.Notes = sqlPtr->value(13).toString();
            customerListTemp.push_back(customerTemp);
        }

        for(int i = 0; i < customerListTemp.size(); i ++ )//客户的数据回显
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(customerListTemp[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(customerListTemp[i].Gender));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(customerListTemp[i].Name));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(customerListTemp[i].Phone));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(customerListTemp[i].CardID));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(customerListTemp[i].Spend)));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(customerListTemp[i].Count)));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(customerListTemp[i].CardType));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem(customerListTemp[i].HaveNotPaid));
            ui->tableWidget->setItem(i,9,new QTableWidgetItem(customerListTemp[i].HaveNotPaidMoney));
            ui->tableWidget->setItem(i,10,new QTableWidgetItem(QString::number(customerListTemp[i].CardMoney)));
            ui->tableWidget->setItem(i,11,new QTableWidgetItem(customerListTemp[i].Address));
            ui->tableWidget->setItem(i,12,new QTableWidgetItem(customerListTemp[i].Credit));
            ui->tableWidget->setItem(i,13,new QTableWidgetItem(customerListTemp[i].Notes));
        }
         ui->tableWidget->update();

    }




/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看衣服种类
    else if(1 == currentMode)//选择衣物种类
    {
        ui->tableWidget->clear();
        QList<clothesInfo> clothesListTemp;
        QList<QString> clothesTittle;
        clothesInfo clothesTemp;

        ui->ClothesBrand->show();
        ui->ClothesTreatment->show();
        ui->ClothesEffect->show();
        ui->ClothesColor->show();
        ui->ClothesNameAndPrice->show();
        ui->ClothesDefect->show();
        ui->groupBox->show();


        if(ui->ClothesNameAndPrice->isChecked())
       {
        clothesTittle.clear();
        ui->tableWidget->clear();
        QString washWay = ui->CBWashWay->currentText();
        clothesTittle << "衣服ID" << "衣服名称" << "建议价格" << "衣服类型" << "衣物处理";

        if("全部" == washWay)//如果是全部，那么就全部放上去
        {
            sqlPtr->exec(QString("select count(ID) from Clothes"));
            sqlPtr->next();
            int Cnt = sqlPtr->value(0).toInt();
            ui->LbCount->setText(QString("当前衣物种类总数:%1").arg(Cnt));
            ui->tableWidget->setRowCount(Cnt);
            ui->tableWidget->setColumnCount(clothesTittle.size());

            for(int i = 0 ; i < clothesTittle.size(); i ++)
            ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




            sqlPtr->exec(QString("select * from Clothes"));
            while(sqlPtr->next())
            {
                clothesTemp.ID = sqlPtr->value(0).toString();
                clothesTemp.Name = sqlPtr->value(1).toString();
                clothesTemp.Price = sqlPtr->value(2).toInt();
                clothesTemp.Type = sqlPtr->value(3).toString();
                clothesTemp.WashWay = sqlPtr->value(4).toString();
                clothesListTemp.push_back(clothesTemp);

            }

            for(int i = 0; i < clothesListTemp.size(); i ++)//把所有的衣服都查出来都放上去
            {
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(clothesListTemp[i].ID));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(clothesListTemp[i].Name));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(clothesListTemp[i].Price)));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(clothesListTemp[i].Type));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(clothesListTemp[i].WashWay));
            }

             ui->tableWidget->update();
             return;
        }

        sqlPtr->exec(QString("select count(ID) from Clothes where WashWay = '%1';").arg(washWay));
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前衣物种类总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec(QString("select * from Clothes where WashWay = '%1'").arg(washWay));
        while(sqlPtr->next())
        {
            clothesTemp.ID = sqlPtr->value(0).toString();
            clothesTemp.Name = sqlPtr->value(1).toString();
            clothesTemp.Price = sqlPtr->value(2).toInt();
            clothesTemp.Type = sqlPtr->value(3).toString();
            clothesTemp.WashWay = sqlPtr->value(4).toString();
            clothesListTemp.push_back(clothesTemp);

        }

        for(int i = 0; i < clothesListTemp.size(); i ++)//把所有的衣服都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(clothesListTemp[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(clothesListTemp[i].Name));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(clothesListTemp[i].Price)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(clothesListTemp[i].Type));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(clothesListTemp[i].WashWay));
        }

         ui->tableWidget->update();
       }




        if(ui->ClothesColor->isChecked())////////////////////////选择了衣服，如果选择了衣服的颜色
       {
        ui->tableWidget->clear();
        clothesTittle.clear();
        clothesTittle << "ID" << "衣服颜色";

        sqlPtr->exec("select count(ID) from ClothesColor");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前衣物颜色总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec("select * from ClothesColor");


        for(int i = 0;sqlPtr->next(); i ++)//把所有的衣服颜色都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlPtr->value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlPtr->value(1).toString()));
        }

         ui->tableWidget->update();
       }



        if(ui->ClothesDefect->isChecked())////////////////////////选择了衣服，如果选择了衣服的瑕疵
       {
        ui->tableWidget->clear();
        clothesTittle.clear();
        clothesTittle << "ID" << "衣服瑕疵";

        sqlPtr->exec("select count(ID) from ClothesDefect");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前衣物瑕疵总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec("select * from ClothesDefect");


        for(int i = 0;sqlPtr->next(); i ++)//把所有的衣服瑕疵都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlPtr->value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlPtr->value(1).toString()));
        }

         ui->tableWidget->update();
       }




        if(ui->ClothesBrand->isChecked())////////////////////////选择了衣服，如果选择了衣服的品牌
       {
        ui->tableWidget->clear();
        clothesTittle.clear();
        clothesTittle << "ID" << "衣服品牌";

        sqlPtr->exec("select count(ID) from ClothesBrand");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前衣物品牌总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec("select * from ClothesBrand");


        for(int i = 0;sqlPtr->next(); i ++)//把所有的衣服品牌都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlPtr->value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlPtr->value(1).toString()));
        }

         ui->tableWidget->update();
       }



        if(ui->ClothesTreatment->isChecked())////////////////////////选择了衣服，如果选择了衣服的特殊处理
       {
        ui->tableWidget->clear();
        clothesTittle.clear();
        clothesTittle << "ID" << "特殊处理";

        sqlPtr->exec("select count(ID) from SpecialTreatment");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前特殊处理总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec("select * from SpecialTreatment");


        for(int i = 0;sqlPtr->next(); i ++)//把所有的衣服品牌都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlPtr->value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlPtr->value(1).toString()));
        }

         ui->tableWidget->update();
       }




        if(ui->ClothesEffect->isChecked())////////////////////////选择了衣服，如果选择了衣服的洗后效果
       {
        ui->tableWidget->clear();
        clothesTittle.clear();
        clothesTittle << "ID" << "衣服洗后效果";

        sqlPtr->exec("select count(ID) from WashingEffect");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();
        ui->LbCount->setText(QString("当前洗后效果总数:%1").arg(Cnt));
        ui->tableWidget->setRowCount(Cnt);
        ui->tableWidget->setColumnCount(clothesTittle.size());

        for(int i = 0 ; i < clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesTittle[i]));//设置tittle




        sqlPtr->exec("select * from WashingEffect");


        for(int i = 0;sqlPtr->next(); i ++)//把所有的衣服品牌都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlPtr->value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlPtr->value(1).toString()));
        }

         ui->tableWidget->update();
       }





     }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看员工账号密码
    else if(2 == currentMode && "经理" == pulic::currentUser->userInformation.Authority)//如果选择的是员工账号并且有用经理特权，才能查看员工的账号密码
    {
        ui->tableWidget->clear();
        QList<UserInformation> tempList;
        QList<QString> horizontalTitleList;
        UserInformation tempInfo;
        horizontalTitleList << "员工编号ID" << "员工账号" << "员工密码" << "员工姓名" << "员工权限";//插入title要在setColum和setRow之后再设置标题，不然不会显示




        sqlPtr->exec("select * from User");//把所有的员工都查出来（反正也没几个）
        while(sqlPtr->next())
        {
            tempInfo.ID = sqlPtr->value(0).toString();
            tempInfo.Account = sqlPtr->value(1).toString();
            tempInfo.Password = sqlPtr->value(2).toString();
            tempInfo.Name = sqlPtr->value(3).toString();
            tempInfo.Authority = sqlPtr->value(4).toString();
            tempList.push_back(tempInfo);
        }


        sqlPtr->exec("select count(ID) from User");
        sqlPtr->next();
        int Cnt = sqlPtr->value(0).toInt();//在设置多少行之前，要先拿到总共有多少人
        ui->LbCount->setText(QString("当前总员工人数:%1").arg(Cnt));//并且用标签播报出来
        //qDebug() << "现在员工总共有：" << Cnt << "人";

        ui->tableWidget->setRowCount(Cnt);//设置有多少行
        ui->tableWidget->setColumnCount(horizontalTitleList.size());//设置总共有多少列
        for(int i = 0 ; i < tempList.size() ; i ++)//设置表中的元素
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(tempList[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(tempList[i].Account));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(tempList[i].Password));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(tempList[i].Name));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(tempList[i].Authority));
        }
        for(int i = 0 ; i < 5 ; i ++)//设置tittle
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(horizontalTitleList[i]));

        ui->tableWidget->update();

    }

    else if(2 == currentMode && "员工" == pulic::currentUser->userInformation.Authority)//否则不能查看
    {
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("普通员工无权限查看"));
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("通知"));
    }


}




void dlgAdd::on_BtnAdd_clicked()//如果点击了添加
{
    if(pulic::currentUser->userInformation.Authority != "经理")
    {
        QMessageBox::information(nullptr,"信息","只有经理才能进行添加！");
        return;
    }
    currentMode = choseMode();//先查询选择了哪个
    if(-1 == currentMode)
    {
        QMessageBox::information(nullptr,"警告","选择错误");
        return;
    }

    else if(0 == currentMode)//如果选择了客户
    {
        mDlgAddCustomer.exec();
    }
    else if(1 == currentMode)//如果选择了衣物种类
    {
        if(ui->ClothesNameAndPrice->isChecked())
        {
            mDlgAddClothes.exec();
        }

        if(ui->ClothesColor->isChecked())
        {
            dlgAC = new dlgAddClothesOtherAttributes(nullptr,1);
            dlgAC->exec();
        }


        if(ui->ClothesDefect->isChecked())
        {
            dlgAC = new dlgAddClothesOtherAttributes(nullptr,2);
            dlgAC->exec();
        }

        if(ui->ClothesBrand->isChecked())
        {
            dlgAC = new dlgAddClothesOtherAttributes(nullptr,3);
            dlgAC->exec();
        }


        if(ui->ClothesTreatment->isChecked())
        {
            dlgAC = new dlgAddClothesOtherAttributes(nullptr,4);
            dlgAC->exec();
        }

        if(ui->ClothesEffect->isChecked())
        {
            dlgAC = new dlgAddClothesOtherAttributes(nullptr,5);
            dlgAC->exec();
        }


    }
    else if(2 == currentMode)//如果选择了员工账号
    {
        mDlgAddUser.exec();
    }



    reFresh(choseMode());

}

void dlgAdd::on_choseCBox_currentIndexChanged(int index)//数据回显
{
      reFresh(index);
      if(index != 1)
      {
          ui->groupBox->hide();
      }

}



void dlgAdd::on_BtnreFresh_clicked()//刷新键
{
    reFresh(choseMode());
     ui->tableWidget->update();
}



void dlgAdd::on_BtnDelete_clicked()
{
    auto currentRow = ui->tableWidget->currentRow();
    if(pulic::currentUser->userInformation.Authority != "经理")
    {
        QMessageBox::information(nullptr,"信息","只有经理才能进行删除！");
        return;
    }
    if(currentRow != -1)
    {
        auto status = QMessageBox::question(nullptr, "确认操作", "你确定要继续吗？",QMessageBox::Yes | QMessageBox::No);
        if(status == QMessageBox::Yes)
        {
        QTableWidgetItem *item = ui->tableWidget->item(currentRow, 0);
        QString id = item->data(0).toString();
        currentMode = choseMode();
        auto sqlPtr = pulic::getInstance()->sql;
        bool success = false;

        if(0 == currentMode)//如果是客户
        {
            deleteOperate.target = QString("删除了客户：%1，ID：%2,客户性别：%3，客户卡ID：%4，客户欠缴情况：%5，客户欠缴费：%6元，客户卡余额：%7,客户住址：%8，客户信用：%9")
                    .arg(ui->tableWidget->item(currentRow, 2)->text()).arg(item->text().toInt()).arg(ui->tableWidget->item(currentRow,1)->text())
                    .arg(ui->tableWidget->item(currentRow,4)->text()).arg(ui->tableWidget->item(currentRow,8)->text())
                    .arg(ui->tableWidget->item(currentRow,9)->text()).arg(ui->tableWidget->item(currentRow,10)->text())
                    .arg(ui->tableWidget->item(currentRow,11)->text()).arg(ui->tableWidget->item(currentRow,12)->text());
            LaundryManagementLogger::record(deleteOperate);
            success = sqlPtr->exec(QString("delete from Customer where ID = '%1'").arg(id));

        }


        if(1 == currentMode)//如果是衣服
        {
            QString ID = ui->tableWidget->item(currentRow,0)->text();
            if(ui->ClothesNameAndPrice->isChecked())
            {
                deleteOperate.target = QString("删除了衣服:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from Clothes where ID = '%1'").arg(ID));
            }

            if(ui->ClothesColor->isChecked())
            {
                deleteOperate.target = QString("删除了衣服颜色:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from ClothesColor where ID = '%1'").arg(ID));
            }

            if(ui->ClothesDefect->isChecked())
            {
                deleteOperate.target = QString("删除了衣服瑕疵:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from ClothesDefect where ID = '%1'").arg(ID));
            }

            if(ui->ClothesBrand->isChecked())
            {
                deleteOperate.target = QString("删除了衣服品牌:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from ClothesBrand where ID = '%1'").arg(ID));
            }

            if(ui->ClothesEffect->isChecked())
            {
                deleteOperate.target = QString("删除了衣服洗后效果:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from WashingEffect where ID = '%1'").arg(ID));
            }

            if(ui->ClothesTreatment->isChecked())
            {
                deleteOperate.target = QString("删除了特殊处理:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
                LaundryManagementLogger::record(deleteOperate);
                success = sqlPtr->exec(QString("delete from SpecialTreatment where ID = '%1'").arg(ID));
            }
        }


        if(2 == currentMode)//如果是员工
        {
           deleteOperate.target = QString("删除了员工%1，ID为%2").arg(ui->tableWidget->item(currentRow, 3)->data(0).toString()).arg(item->data(0).toInt());
           LaundryManagementLogger::record(deleteOperate);
           success = sqlPtr->exec(QString("delete from User where ID = '%1'").arg(id));

        }


        if(true == success)
        {
            QMessageBox::information(nullptr,"信息","删除成功！");
        }

        else
        {
            QMessageBox::information(nullptr,"信息","删除失败！");
            qDebug() << sqlPtr->lastError().text();
        }

        }

    }
     reFresh(choseMode());
}



void dlgAdd::on_BetnUpdate_clicked()
{
    if(pulic::currentUser->userInformation.Authority != "经理")
    {
        QMessageBox::information(nullptr,"信息","只有经理才能进行修改！");
        return;
    }
    if(-1 != ui->tableWidget->currentRow())
    {
    currentMode = choseMode();
    auto currentItem = ui->tableWidget->currentItem();
    int currentRow = currentItem->row();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////如果选择了修改员工
    if(2 == currentMode)
    {
        UserInformation userTemp;
        userTemp.ID = ui->tableWidget->item(currentRow,0)->text();
        userTemp.Account = ui->tableWidget->item(currentRow,1)->text();
        userTemp.Password = ui->tableWidget->item(currentRow,2)->text();
        userTemp.Name = ui->tableWidget->item(currentRow,3)->text();
        userTemp.Authority = ui->tableWidget->item(currentRow,4)->text();

//        qDebug() << userTemp.ID;
//        qDebug() << userTemp.Account;
//        qDebug() << userTemp.Password;
//        qDebug() << userTemp.Name;
//        qDebug() << userTemp.Authority;

        mDlgUpdaterUser = new dlgUpadateUser(nullptr,userTemp);
        mDlgUpdaterUser->exec();
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////如果选择了修改衣服
    if(1 == currentMode)
    {
    if(ui->ClothesNameAndPrice->isChecked())
    {
        clothesInfo clothesTemp;
        clothesTemp.ID = ui->tableWidget->item(currentRow,0)->text();
        clothesTemp.Name = ui->tableWidget->item(currentRow,1)->text();
        clothesTemp.Price = ui->tableWidget->item(currentRow,2)->text().toInt();
        clothesTemp.Type = ui->tableWidget->item(currentRow,3)->text();

//        qDebug() << clothesTemp.ID;
//        qDebug() << clothesTemp.Name;
//        qDebug() << clothesTemp.Price;
//        qDebug() << clothesTemp.Type;

        mDlgUpdateClothes = new dlgUpdateClothes(nullptr,clothesTemp);
        mDlgUpdateClothes->exec();
     }

    else
    {
        currentRow = ui->tableWidget->currentRow();
        if(ui->ClothesColor->isChecked())
        dlgUC = new dlgUpdateClothesOtherAttributes(nullptr,1,ui->tableWidget->item(currentRow,0)->text(),ui->tableWidget->item(currentRow,1)->text());

        if(ui->ClothesDefect->isChecked())
        dlgUC = new dlgUpdateClothesOtherAttributes(nullptr,2,ui->tableWidget->item(currentRow,0)->text(),ui->tableWidget->item(currentRow,1)->text());

        if(ui->ClothesBrand->isChecked())
        dlgUC = new dlgUpdateClothesOtherAttributes(nullptr,3,ui->tableWidget->item(currentRow,0)->text(),ui->tableWidget->item(currentRow,1)->text());

        if(ui->ClothesTreatment->isChecked())
        dlgUC = new dlgUpdateClothesOtherAttributes(nullptr,4,ui->tableWidget->item(currentRow,0)->text(),ui->tableWidget->item(currentRow,1)->text());

        if(ui->ClothesEffect->isChecked())
        dlgUC = new dlgUpdateClothesOtherAttributes(nullptr,5,ui->tableWidget->item(currentRow,0)->text(),ui->tableWidget->item(currentRow,1)->text());

        dlgUC->exec();
    }





    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////如果选择了修改客户
    if(0 == currentMode)
    {
        customerInfo customerTemp;
        customerTemp.ID = ui->tableWidget->item(currentRow,0)->text();
        customerTemp.Gender = ui->tableWidget->item(currentRow,1)->text();
        customerTemp.Name = ui->tableWidget->item(currentRow,2)->text();
        customerTemp.Phone = ui->tableWidget->item(currentRow,3)->text();
        customerTemp.CardID = ui->tableWidget->item(currentRow,4)->text();
        customerTemp.Spend = ui->tableWidget->item(currentRow,5)->text().toDouble();
        customerTemp.Count = ui->tableWidget->item(currentRow,6)->text().toDouble();
        customerTemp.CardType = ui->tableWidget->item(currentRow,7)->text();
        customerTemp.HaveNotPaid = ui->tableWidget->item(currentRow,8)->text();
        customerTemp.HaveNotPaidMoney = ui->tableWidget->item(currentRow,9)->text();
        customerTemp.CardMoney = ui->tableWidget->item(currentRow,10)->text().toDouble();
        customerTemp.Address = ui->tableWidget->item(currentRow,11)->text();
        customerTemp.Credit = ui->tableWidget->item(currentRow,12)->text();
        customerTemp.Notes = ui->tableWidget->item(currentRow,13)->text();



//        qDebug() << customerTemp.ID;
//        qDebug() << customerTemp.Name;
//        qDebug() << customerTemp.Phone;
//        qDebug() << customerTemp.CardID;
//        qDebug() << customerTemp.Spend;
//        qDebug() << customerTemp.Count;
//        qDebug() << customerTemp.CardMoney;
//        qDebug() << customerTemp.Notes;

        mDlgUpdateCustomer = new dlgUpdateCustomer(nullptr,customerTemp);
        mDlgUpdateCustomer->exec();





    }



 }
        reFresh(choseMode());
}





void dlgAdd::on_LeSearch_textChanged(const QString &arg1)
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        bool rowMatches = false;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                // 判断单元格文本是否包含搜索词
                if (item->text().contains(arg1,Qt::CaseInsensitive)) {
                    rowMatches = true;
                    break;
                }
            }
        }
        // 根据是否匹配来显示或隐藏行
        ui->tableWidget->setRowHidden(row, !rowMatches);
    }

}

void dlgAdd::onRadioButtonChanged()
{
    reFresh(choseMode());
    if(ui->ClothesNameAndPrice->isChecked())
    {
        ui->CBWashWay->show();
    }
    else
    {
        ui->CBWashWay->hide();
    }
}


void dlgAdd::show()
{
    reFresh(choseMode());
    QWidget::show();
}



void dlgAdd::on_CBWashWay_currentIndexChanged(int index)
{
    reFresh(choseMode());

}
