#include "mainwindow.h"
void MainWindow::setupRealtimeData(QCustomPlot *customPlot)
{

    // include this section to fully disable antialiasing for higher performance:
    /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(255, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 110)));
    customPlot->addGraph(); // red line
    customPlot->graph(2)->setPen(QPen(QColor(255, 110, 0)));
    customPlot->addGraph(); // red line
    customPlot->graph(3)->setPen(QPen(QColor(255, 0, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(4)->setPen(QPen(QColor(110, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(5)->setPen(QPen(QColor(0, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(6)->setPen(QPen(QColor(0, 110, 110)));
    customPlot->addGraph(); // red line
    customPlot->graph(7)->setPen(QPen(QColor(255, 110, 110)));
    customPlot->addGraph(); // red line
    customPlot->graph(8)->setPen(QPen(QColor(0, 110, 0)));
    customPlot->addGraph(); // red line
    customPlot->graph(9)->setPen(QPen(QColor(255, 110, 0)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-100, 100);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::setupRealtimeData_show1(QCustomPlot *customPlot)
{

    customPlot->addGraph(); // blue line
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
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
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::on_Bt_UartConect_clicked()
{
    static int i=0;
    char  * uartpath;
    int uartrate;
    if(i==0)
    {
        uartpath=ui->lineEdit_uartpath->text().toLatin1().data();
        uartrate=ui->lineEdit_uartrate->text().toInt();
        uart.Init((const char *)uartpath,uartrate);
        if(uart.Is_connect)
        {
            i=1;
            ui->Bt_UartConect->setText("断开");

        }
    }else
    {
            i=0;
            uart.Disconnect();
            ui->Bt_UartConect->setText("连接");    
    }
}

void MainWindow::on_Bt_UartConect_2_clicked()
{
    static int i=0;
    char  * uartpath;
    int uartrate;
    if(i==0)
    {
        uartpath=ui->lineEdit_uartpath_2->text().toLatin1().data();
        uartrate=ui->lineEdit_uartrate_2->text().toInt();
        uart2.Init((const char *)uartpath,uartrate);
        if(uart2.Is_connect)
        {
            i=1;
            ui->Bt_UartConect_2->setText("断开");
        }
    }else
    {
        i=0;
        uart2.Disconnect();
        ui->Bt_UartConect_2->setText("连接");
    }
}

void MainWindow::on_Bt_UartStart_clicked()
{
    static int i=0;
    if(i==0)
    {
        i=1;
        ui->Bt_UartStart->setText("停止");
        dataTimer.start(20);


    }else
    {
        i=0;
        ui->Bt_UartStart->setText("开始");
        if ( dataTimer.isActive() ) dataTimer.stop();
     }

}



void MainWindow::on_comboBox_uartpath_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit_uartpath->setText(arg1);
}

void MainWindow::on_pushButton_sendfloat_clicked()
{
    unsigned char addr;
    float cmdfloat;
    addr=ui->lineEdit_floataddr->text().toInt();
    cmdfloat=ui->lineEdit_cmdfloat->text().toFloat();
    uart.SendFloat(addr,cmdfloat);
}

void MainWindow::on_pushButton_sendcmd_clicked()
{
    unsigned char cmd;
    cmd=ui->lineEdit_cmd->text().toStdString().c_str()[0];
    uart.SendCommend(cmd);
}


