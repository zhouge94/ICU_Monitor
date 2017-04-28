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
/*    FileParse fd;
    Sheet temp,temp2;
    int i;
    if(!fd.parseCSV("test_body_20170221_ecg.csv",&temp))
    {
        std::cout<<temp.name.toStdString()<<":"<<temp.data.count()<<std::endl;
    }
    if(!fd.parseCSV("test_body_20170221_mb.csv",&temp2))
    {
        std::cout<<temp2.name.toStdString()<<":"<<temp2.data.count()<<std::endl;
    }
    ui->plot1_huxi->addGraph();
    int count=temp.data.count();
    for(i=500*30;i<500*45;i++)
    {
        QString a=temp.data.at(i).at(0);
        QString b=temp.data.at(i).at(1);
        float key=a.toFloat();
        float value=b.toFloat();
        float value2=filter_low1.RealFIR(value);
        if(FindMinMax_ecg.input2(key,value2))
        {
            std::cout<<"success get max ecg --------------t:"<<FindMinMax_ecg.maxkey<<std::endl;
            sys.maxecg_t.append(FindMinMax_ecg.maxkey);
            sys.maxecg_v.append(FindMinMax_ecg.max);
            QCPItemTracer *groupTracer = new QCPItemTracer(ui->plot1_huxi);
            groupTracer->setGraph(ui->plot1_huxi->graph(0));
            groupTracer->setGraphKey(FindMinMax_ecg.maxkey);
            groupTracer->setInterpolating(true);
            groupTracer->setStyle(QCPItemTracer::tsCircle);
            groupTracer->setPen(QPen(Qt::red));
            groupTracer->setBrush(Qt::red);
            groupTracer->setSize(7);

        }
        ui->plot1_huxi->graph(0)->addData(key, value2);
        ui->plot1_huxi->graph(0)->rescaleValueAxis(false,false);
        ui->plot1_huxi->xAxis->setRange(30,35);
        if(!(i%50))ui->plot1_huxi->replot();
    }
    for(i=104*30;i<104*45;i++)
    {
        QString a=temp2.data.at(i).at(0);
        QString b=temp2.data.at(i).at(1);
        float key=a.toFloat();
        float value=b.toFloat();
        float value2=filter_bandpass1.RealFIR(value);
        if(FindMinMax_mb.input(key,value2))
        {
            std::cout<<"success get max mb -------------t:"<<FindMinMax_mb.maxkey<<std::endl;
            sys.maxmb_t.append(FindMinMax_mb.maxkey);
            sys.maxmb_v.append(FindMinMax_mb.max);
            QCPItemTracer *groupTracer = new QCPItemTracer(ui->plot1_huxi);
            groupTracer->setGraph(ui->plot1_huxi->graph(1));
            groupTracer->setGraphKey(FindMinMax_mb.maxkey);
            groupTracer->setInterpolating(true);
            groupTracer->setStyle(QCPItemTracer::tsCircle);
            groupTracer->setPen(QPen(Qt::green));
            groupTracer->setBrush(Qt::green);
            groupTracer->setSize(7);

        }
        ui->plot1_huxi->graph(1)->addData(key, (value2+200)*40);
        ui->plot1_huxi->graph(1)->rescaleValueAxis(false,false);
        // rescale value (vertical) axis to fit the current data:
        if(!(i%50))ui->plot1_huxi->replot();
    }

    XueYa();
    */
    QString qstring = "lyc_daniel";
    // msgdialog.show();
    sysseting.exec();
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
