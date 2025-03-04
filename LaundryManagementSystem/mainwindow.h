#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dlglogin.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QTimer>
#include "dlgadd.h"
#include "dlggetclothes.h"
#include <memory>
#include "dlgmanage.h"
#include "dlgcustomerrecharge.h"
#include "dlgSearch.h"
#include "sqlmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static  MainWindow* getInstance()//创建单例
    {
        if(nullptr == Instance)
        {
            //sqlManager::createSqlManager();//这个也要初始化，不然一切都炸
            return new MainWindow();
        }

        else
        {
            return Instance;
        }

    }


public:
   QTimer *timer;
   dlgLogin dlgLogin;
   dlgManage dlgMana;//管理界面包括了添加
   dlgGetClothes dlgGetClo;//取衣界面
   dlgCustomerRecharge* dlgRecharge;//用户充值入口
   dlgSearch dlgSea;//查询界面


public:
   void reFresh();
   void show();

private slots:
    void on_BtnAdd_clicked();

    void on_BtnGetClothes_clicked();


    void on_BtnRecharge_clicked();

    void on_BtnSearch_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::MainWindow *ui;
    static MainWindow* Instance;//主窗口单例

};

#endif // MAINWINDOW_H
