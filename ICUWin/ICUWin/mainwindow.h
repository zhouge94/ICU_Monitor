#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "my_uart.h"
#include "ui_mainwindow.h"
#include "qtimer.h"
#include "stdio.h"
#include "unistd.h"
#include "QMessageBox"
#include "sys.h"
#include <qapplication.h>
#include <stdlib.h>
#include "iostream"
#include "filter.h"
#include "sysseting.h"
#include "datareplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Outinfo(const QString &msg);
    void OutOneinfo(const QString &msg);
    ~MainWindow();
    SysSeting ui_sysseting;
    DataReplay ui_dp;
private slots:
    void UartCallback();
    void UartCallback2();
    void on_Bt_UartConect_clicked();
    void realtimeDataSlot();
    void setupRealtimeData(QCustomPlot *customPlot);
    void on_Bt_UartStart_clicked();

    void on_comboBox_uartpath_currentIndexChanged(const QString &arg1);

    void on_pushButton_sendfloat_clicked();

    void on_pushButton_sendcmd_clicked();

    void setupRealtimeData_show1(QCustomPlot *customPlot);
    void realtimeDataSlot_show1();
    void on_pushButton_show1_begin_clicked();

    void on_pushButton_show1_stop_clicked();

    void on_pushButton_savedata_clicked();

    void on_Bt_UartConect_2_clicked();

    void GetHardSudoCallBack();
    void SecondCallBack();
    void on_pushButton_2_clicked();    
    void on_comboBox_uartpath_2_currentIndexChanged(const QString &arg1);

    void onCommTimeout();
    void on_pushButton_3_clicked();

    void on_pushButton_openpath_clicked();

    void ConnectUART();
    void on_pushButton_UartAuto_clicked();

    void on_pushButton_setting_clicked();

private:
    My_Uart uart;
    My_Uart uart2;
    Ui::MainWindow *ui;

    int Uart_fd;
    int Uart_fd2;

    QTimer SecondTimer;
    QTimer dataTimer;
    QTimer dataTimer_show1;

    QTimer UartTimer;
    QTimer UartTimer2;
    QTimer CommTimer;

    QThread  uart1Thread;
    QThread  uart2Thread;
    QThread  CommThread;

    void ResetAllData(void);
};
extern QCustomPlot *ecgPlot;
extern QCustomPlot *mbPlot;
#endif // MAINWINDOW_H
