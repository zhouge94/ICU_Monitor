#include "mainwindow.h"
QCustomPlot *ecgPlot;
QCustomPlot *mbPlot;
void MainWindow::on_pushButton_savedata_clicked()
{
    QString filename=ui->lineEdit_savefilename->text();
    SaveData(filename);
}
//test for date
void MainWindow::on_pushButton_2_clicked()
{

    QString qstring = "lyc_daniel";
    // msgdialog.show();
    ui_dp.exec();
}
void MainWindow::on_comboBox_uartpath_2_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit_uartpath_2->setText(arg1);
}
//get the name of save file
void MainWindow::on_pushButton_3_clicked()
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyyMMdd-hhmmss");
    ui->lineEdit_savefilename->setText(str);
}

void MainWindow::on_pushButton_openpath_clicked()
{
    system("nautilus ./Data");
}

void MainWindow::on_pushButton_show1_begin_clicked()
{
    if(ui->pushButton_show1_begin->text()=="开始记录")
    {
        ResetAllData();
        sys.IsBeginRecode=1;
        dataTimer_show1.start(50);
        ui->pushButton_show1_stop->setEnabled(1);
        ui->pushButton_show1_begin->setText("停止记录");
        ui->pushButton_show1_stop->setText("暂停记录");
    }else
    {
        dataTimer_show1.stop();
        ui->pushButton_show1_stop->setEnabled(0);
        ui->pushButton_show1_begin->setText("开始记录");
        sys.IsBeginRecode=0;
    }
}


void MainWindow::on_pushButton_show1_stop_clicked()
{
    if(ui->pushButton_show1_stop->text()=="暂停记录")
    {
        dataTimer_show1.stop();
        ui->pushButton_show1_stop->setText("继续记录");
    }else
    {
        dataTimer_show1.start(20);;
        ui->pushButton_show1_stop->setText("暂停记录");
    }
}
void MainWindow::on_pushButton_UartAuto_clicked()
{
    ConnectUART();
}
