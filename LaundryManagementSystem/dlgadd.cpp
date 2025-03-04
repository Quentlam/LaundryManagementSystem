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
#include <QVariant>
#include "sqlmanager.h"

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
    currentMode = index;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看客户信息
    if(0 == currentMode)//选择客户
    {
        ui->tableWidget->clear();

        std::unique_ptr<QList<customerInfo>> customerListTemp;
        customerListTemp = sqlManager::createCustomerSql()->selectAllCustomerInfo();

        ui->LbCount->setText(QString("当前总客户人数:%1").arg(customerListTemp->size()));
        ui->tableWidget->setRowCount(customerListTemp->size());
        ui->tableWidget->setColumnCount(customerInfo::customerTittle.size());


        for(int i = 0; i < customerInfo::customerTittle.size() ; i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem (customerInfo::customerTittle[i]));//设置tittle

        for(int i = 0; i < customerListTemp->size(); i ++ )//客户的数据回显
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem((*customerListTemp)[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem((*customerListTemp)[i].Gender));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem((*customerListTemp)[i].Name));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem((*customerListTemp)[i].Phone));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem((*customerListTemp)[i].CardID));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number((*customerListTemp)[i].Spend)));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((*customerListTemp)[i].Count)));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem((*customerListTemp)[i].CardType));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem((*customerListTemp)[i].HaveNotPaid));
            ui->tableWidget->setItem(i,9,new QTableWidgetItem((*customerListTemp)[i].HaveNotPaidMoney));
            ui->tableWidget->setItem(i,10,new QTableWidgetItem(QString::number((*customerListTemp)[i].CardMoney)));
            ui->tableWidget->setItem(i,11,new QTableWidgetItem((*customerListTemp)[i].Address));
            ui->tableWidget->setItem(i,12,new QTableWidgetItem((*customerListTemp)[i].Credit));
            ui->tableWidget->setItem(i,13,new QTableWidgetItem((*customerListTemp)[i].Notes));
        }
         ui->tableWidget->update();

    }




/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看衣服种类
    else if(1 == currentMode)//选择衣物种类
    {
        ui->tableWidget->clear();
        ui->ClothesBrand->show();
        ui->ClothesTreatment->show();
        ui->ClothesEffect->show();
        ui->ClothesColor->show();
        ui->ClothesNameAndPrice->show();
        ui->ClothesDefect->show();
        ui->groupBox->show();


        if(ui->ClothesNameAndPrice->isChecked())
       {
        ui->tableWidget->clear();
        QString washWay = ui->CBWashWay->currentText();
        clothesInfo::WashWayType type = clothesInfo::allClothes;
        //以下是选择类型
        if("全部" == washWay)
        type = clothesInfo::allClothes;
        if("水洗" == washWay)
        type = clothesInfo::wash;
        if("干洗" == washWay)
        type = clothesInfo::dryClean;
        if("皮衣" == washWay)
        type = clothesInfo::leatherCoat;
        if("单烫" == washWay)
        type = clothesInfo::singleIroning;
        if("其他" == washWay)
        type = clothesInfo::other;

        std::unique_ptr<QList<clothesInfo>> clothesTempList;
        clothesTempList = sqlManager::createClothesSql()->showClothesInfo(type);
        ui->LbCount->setText(QString("当前衣物种类总数:%1").arg(clothesTempList->size()));
        ui->tableWidget->setRowCount(clothesTempList->size());
        ui->tableWidget->setColumnCount(clothesInfo::clothesTittle.size());

        for(int i = 0 ; i < clothesInfo::clothesTittle.size(); i ++)
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(clothesInfo::clothesTittle[i]));//设置tittle

        for(int i = 0; i < clothesTempList->size(); i ++)//把所有的衣服都查出来都放上去
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem((*clothesTempList)[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem((*clothesTempList)[i].Name));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number((*clothesTempList)[i].Price)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem((*clothesTempList)[i].Type));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem((*clothesTempList)[i].WashWay));
        }

             ui->tableWidget->update();
             return;
        }


        if(!ui->ClothesNameAndPrice->isChecked())
        {
            ui->tableWidget->clear();
            std::unique_ptr<QList<clothesAttributeInfo>> clothesAttributeList;
            QList<QString>* tittle;
        if(ui->ClothesColor->isChecked())////////////////////////选择了衣服，如果选择了衣服的颜色
       {
            tittle = &clothesInfo::clothesColorTittle;
            clothesAttributeList = sqlManager::createClothesSql()->showClothesColorInfo();//查询
            ui->LbCount->setText(QString("当前衣物颜色总数:%1").arg(clothesAttributeList->size()));
       }
        if(ui->ClothesDefect->isChecked())////////////////////////选择了衣服，如果选择了衣服的瑕疵
       {
            tittle = &clothesInfo::clothesDefectTittle;
            clothesAttributeList = sqlManager::createClothesSql()->showClothesDefectInfo();//查询
            ui->LbCount->setText(QString("当前衣物瑕疵总数:%1").arg(clothesAttributeList->size()));
       }
        if(ui->ClothesBrand->isChecked())////////////////////////选择了衣服，如果选择了衣服的品牌
       {
            tittle = &clothesInfo::clothesBrandTittle;
            clothesAttributeList = sqlManager::createClothesSql()->showClothesBrandInfo();//查询
            ui->LbCount->setText(QString("当前衣物品牌总数:%1").arg(clothesAttributeList->size()));
       }
        if(ui->ClothesTreatment->isChecked())////////////////////////选择了衣服，如果选择了衣服的特殊处理
       {
            tittle = &clothesInfo::clothesSpecialTreatmentTittle;
            clothesAttributeList = sqlManager::createClothesSql()->showClothesSpecialTreatmentInfo();//查询
            ui->LbCount->setText(QString("当前衣物特殊处理总数:%1").arg(clothesAttributeList->size()));
       }

        if(ui->ClothesEffect->isChecked())////////////////////////选择了衣服，如果选择了衣服的洗后效果
       {
            tittle = &clothesInfo::clothesWashEffectTittle;
            clothesAttributeList = sqlManager::createClothesSql()->showClothesWashingEffectInfo();//查询
            ui->LbCount->setText(QString("当前衣物洗后效果总数:%1").arg(clothesAttributeList->size()));
       }
            ui->tableWidget->setRowCount(clothesAttributeList->size());
            ui->tableWidget->setColumnCount(tittle->size());
            for(int i = 0 ; i < tittle->size(); i ++)
            ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem((*tittle)[i]));//设置tittle
            for(int i = 0; i < clothesAttributeList->size() ; i ++)//把所有的衣服属性都查出来都放上去
            {
                ui->tableWidget->setItem(i,0,new QTableWidgetItem((*clothesAttributeList)[i].ID));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem((*clothesAttributeList)[i].Name));
            }
             ui->tableWidget->update();
        }
    }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////查看员工账号密码
    else if(2 == currentMode && "经理" == pulic::currentUser->Authority)//如果选择的是员工账号并且有用经理特权，才能查看员工的账号密码
    {
        ui->tableWidget->clear();
        std::unique_ptr<QList<userInfo>> userTempList;
        userTempList = sqlManager::createUserSql()->showAllUser();

        ui->LbCount->setText(QString("当前总员工人数:%1").arg(userTempList->size()));//并且用标签播报出来
        //qDebug() << "现在员工总共有：" << Cnt << "人";

        ui->tableWidget->setRowCount(userTempList->size());//设置有多少行
        ui->tableWidget->setColumnCount(userInfo::userInfoTittle.size());//设置总共有多少列
        for(int i = 0 ; i < userTempList->size() ; i ++)//设置表中的元素
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem((*userTempList)[i].ID));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem((*userTempList)[i].Account));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem((*userTempList)[i].Password));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem((*userTempList)[i].Name));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem((*userTempList)[i].Authority));
        }
        for(int i = 0 ; i < userInfo::userInfoTittle.size() ; i ++)//设置tittle
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(userInfo::userInfoTittle[i]));

        ui->tableWidget->update();

    }

    else if(2 == currentMode && "员工" == pulic::currentUser->Authority)//否则不能查看
    {
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("普通员工无权限查看"));
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("通知"));
    }


}




void dlgAdd::on_BtnAdd_clicked()//如果点击了添加
{
    if(pulic::currentUser->Authority != "经理")
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
    if(pulic::currentUser->Authority != "经理")
    {
        QMessageBox::information(nullptr,"信息","只有经理才能进行删除！");
        return;
    }
    if(currentRow != -1)
    {
        auto status = QMessageBox::question(nullptr, "确认操作", "你确定要继续吗？",QMessageBox::Yes | QMessageBox::No);
        if(status == QMessageBox::Yes)
        {
        QString id = ui->tableWidget->item(currentRow, 0)->text();
        currentMode = choseMode();
        bool success = false;

        if(0 == currentMode)//如果是客户
        {
            success = sqlManager::createCustomerSql()->deleteCustomerByID(id);
            deleteOperate.target = QString("删除了客户：%1，ID：%2,客户性别：%3，客户卡ID：%4，客户欠缴情况：%5，客户欠缴费：%6元，客户卡余额：%7,客户住址：%8，客户信用：%9")
                    .arg(ui->tableWidget->item(currentRow, 2)->text()).arg(id).arg(ui->tableWidget->item(currentRow,1)->text())
                    .arg(ui->tableWidget->item(currentRow,4)->text()).arg(ui->tableWidget->item(currentRow,8)->text())
                    .arg(ui->tableWidget->item(currentRow,9)->text()).arg(ui->tableWidget->item(currentRow,10)->text())
                    .arg(ui->tableWidget->item(currentRow,11)->text()).arg(ui->tableWidget->item(currentRow,12)->text());
            if(success)
            {
                QMessageBox::information(nullptr,"信息","删除成功！");
                LaundryManagementLogger::record(deleteOperate);
            }
            else
            {
                sqlManager::createUserSql()->getError();
                QMessageBox::information(nullptr,"信息","删除失败！");
            }
        }


        if(1 == currentMode)//如果是衣服
        {
            if(ui->ClothesNameAndPrice->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesByID(id);
                deleteOperate.target = QString("删除了衣服:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
            }

            if(ui->ClothesColor->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesColorByID(id);
                deleteOperate.target = QString("删除了衣服颜色:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
            }

            if(ui->ClothesDefect->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesDefectByID(id);
                deleteOperate.target = QString("删除了衣服瑕疵:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
            }

            if(ui->ClothesBrand->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesBrandByID(id);
                deleteOperate.target = QString("删除了衣服品牌:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
            }

            if(ui->ClothesEffect->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesWashingEffectByID(id);
                deleteOperate.target = QString("删除了衣服洗后效果:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());
            }

            if(ui->ClothesTreatment->isChecked())
            {
                success = sqlManager::createClothesSql()->deleteClothesTreatmentByID(id);
                deleteOperate.target = QString("删除了特殊处理:%1，ID为%2").arg(ui->tableWidget->item(currentRow, 1)->text()).arg(ui->tableWidget->item(currentRow,0)->text());

            }
            if(success)
            {
                QMessageBox::information(nullptr,"信息","删除成功！");
                LaundryManagementLogger::record(deleteOperate);
            }
            else
            {
                sqlManager::createClothesSql()->getError();
                QMessageBox::information(nullptr,"信息","删除失败！");
            }
        }


        if(2 == currentMode)//如果是员工
        {
           success = sqlManager::createUserSql()->deleteUserById(id);
           if(success)
           {
               QMessageBox::information(nullptr,"信息","删除成功！");
               deleteOperate.target = QString("删除了员工%1，ID为%2").arg(ui->tableWidget->item(currentRow, 3)->data(0).toString()).arg(id);
               LaundryManagementLogger::record(deleteOperate);
           }
           else
           {
               sqlManager::createUserSql()->getError();
               QMessageBox::information(nullptr,"信息","删除失败！");
           }
        }

        }

    }

     reFresh(choseMode());
}



void dlgAdd::on_BetnUpdate_clicked()
{
    if(pulic::currentUser->Authority != "经理")
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
        userInfo userTemp;
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
        clothesTemp.WashWay = ui->tableWidget->item(currentRow,4)->text();
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
