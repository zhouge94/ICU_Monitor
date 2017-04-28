#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtimer.h"
#include "stdio.h"
#include "unistd.h"
#include "QMessageBox"
#include "sys.h"
#include "iostream"
#include "filter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    setupRealtimeData(ui->Plot0);
    setupRealtimeData(ui->Plot1);
    setupRealtimeData_show1(ui->plot1_xinlv);
    setupRealtimeData_show1(ui->plot1_huxi);
    setupRealtimeData_show1(ui->plot1_tiwei);

    connect(&SecondTimer, SIGNAL(timeout()), this, SLOT(SecondCallBack()));//the callback for seconds to do sth
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    connect(&dataTimer_show1, SIGNAL(timeout()), this, SLOT(realtimeDataSlot_show1()));
    connect(ui->action_gethard,SIGNAL(triggered()),this,SLOT(GetHardSudoCallBack()));
/////////////////////////////////////////////////////////////////////////////////////////
    sys.ecgrate=500;
    filter_bandpass1.SetFilterA(firA,50);
    filter_bandpass2.SetFilterA(firC,100);
    filter_low1.SetFilterA(firB,250);

    FindMinMax_ecg.Set(-400);
    FindMinMax_mb.Set2(250,200,200);
    ecgPlot=ui->plot1_xinlv;
    mbPlot=ui->plot1_tiwei;
////////////////////////////////////////////////////////////////////////////////////////
    // 使用线程,跑定时器

    CommTimer.setSingleShot(true);
    CommTimer.start(200);
    CommTimer.moveToThread(&CommThread);
    connect(&CommTimer, SIGNAL(timeout()), this, SLOT(onCommTimeout()), Qt::DirectConnection);
    CommThread.start();

    UartTimer.start(200);
    UartTimer.setSingleShot(true);
    UartTimer.moveToThread(&uart1Thread);
    connect(&UartTimer, SIGNAL(timeout()), this, SLOT(UartCallback()), Qt::DirectConnection);
    uart1Thread.start();

    UartTimer2.start(200);
    UartTimer2.setSingleShot(true);
    UartTimer2.moveToThread(&uart2Thread);
    connect(&UartTimer2, SIGNAL(timeout()), this, SLOT(UartCallback2()), Qt::DirectConnection);
    uart2Thread.start();

    SecondTimer.start(500);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetHardSudoCallBack()
{
    printf("OK\n");
    system("gnome-terminal -x bash -c \" sudo chmod 666 /dev/ttyU*; echo \\\"OK now\\\"; sleep 2s\" ");
}

void MainWindow::ConnectUART()
{
    QList<QString> result;
    int i,ret;
    if(ui->pushButton_UartAuto->text()=="连接")
    {
        ret=(myexec("ls /dev/ttyUSB*",result));
        if(ret>0)
        {
            printf("Found %d Device:\n",ret);
            for(i=0;i<result.count();i++)
            {
                printf("%s\n",result.at(i).toStdString().data());
            }
            printf("Openning Device!\n");
            for(i=0;i<result.count();i++)
            {
                printf("Openning %s\n",result.at(i).toStdString().data());
                if(i==0)uart.Init((const char *)(result.at(i).toStdString().data()),115200);
                else if(i==1)uart2.Init((const char *)(result.at(i).toStdString().data()),115200);
            }
            if(uart.Is_connect||uart2.Is_connect)
            {
                OutOneinfo(QString("成功连接")+QString("%1").arg((uart.Is_connect+uart2.Is_connect))+QString("个设备"));
                ui->pushButton_UartAuto->setText("断开");
            }else
            {
                OutOneinfo("连接失败：没有访问权限，请先获取权限！");
            }
        }
        else
        {
            OutOneinfo("连接失败：没有找到设备！");
        }
    }else
    {
        if(uart.Is_connect)uart.Disconnect();
        if(uart2.Is_connect)uart2.Disconnect();
        OutOneinfo("连接已经断开");
        ui->pushButton_UartAuto->setText("连接");
    }


}
void MainWindow::Outinfo(const QString &msg)
{
    //ui->textEdit_info->textCursor().insertText(msg);
    //ui->textEdit_info->moveCursor(QTextCursor::End);
}

void MainWindow::OutOneinfo(const QString &msg)
{
    printf("%s\n",msg.toStdString().data());
    ui->label_info_out->setText(msg);

}
void MainWindow::ResetAllData()
{
    struct  timeval tv;
    sys.ecgdata.clear();
    sys.ecgdata_t.clear();

    sys.mbridata.clear();
    sys.mbrrdata.clear();
    sys.mbridata_t.clear();
    sys.mbrrdata_t.clear();

    sys.hxdata.clear();
    sys.hxdata_t.clear();
    sys.ecgtime=0;

    QVector<double> x, y;
    ui->plot1_xinlv->graph()->setData(x, y);
    ui->plot1_tiwei->graph()->setData(x, y);
    ui->plot1_huxi->graph()->setData(x, y);

    gettimeofday(&tv,NULL);
    sys.StartTime=tv.tv_sec+tv.tv_usec/1000000.0;
}
