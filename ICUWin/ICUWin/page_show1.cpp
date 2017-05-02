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


void MainWindow::setupRealtimeData_show1(QCustomPlot *customPlot)
{

    customPlot->addGraph(); // blue line
    //customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(200, 220, 250));
    customPlot->graph(0)->setPen(pen);
    customPlot->graph(0)->setBrush(QBrush(QColor(255,200,20,70)));

    // set some pens, brushes and backgrounds:
    customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    customPlot->axisRect()->setBackground(axisRectGradient);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1000, 1000);

    // make left and bottom axes transfer their ranges to right and top axes:
    //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}
