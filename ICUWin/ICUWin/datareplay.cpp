#include "datareplay.h"
#include "ui_datareplay.h"
#include "mapminmax.h"
#include "findpeaks.h"
DataReplay::DataReplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataReplay)
{
    ui->setupUi(this);
    setupRealtimeData(ui->plot);
}

DataReplay::~DataReplay()
{
    delete ui;
}
void DataReplay::setupRealtimeData(QCustomPlot *customPlot)
{

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
    customPlot->yAxis->setRange(-1, 1);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}
void DataReplay::Play(void)
{
        FileParse fd;
        Sheet temp,temp2;
        int i,t0=15,t1=20,fs_ecg=500,fs_mb=252;
        QList<double>ecg_t,ecg_d,mb_t,mb_drr,mb_dri;
        if(!fd.parseCSV("Data/20170324-184544_ZG_ecg.csv",&temp))
        {
            std::cout<<temp.name.toStdString()<<":"<<temp.data.count()<<std::endl;
        }
        if(!fd.parseCSV("Data/20170324-184544_ZG_mb.csv",&temp2))
        {
            std::cout<<temp2.name.toStdString()<<":"<<temp2.data.count()<<std::endl;
        }
        for(i=0;i<temp.data.count();i++)
        {
            QString a=temp.data.at(i).at(0);
            ecg_t.append((double)(a.toFloat()));
            a=temp.data.at(i).at(1);
            ecg_d.append((double)(a.toFloat()));
        }
        for(i=0;i<temp2.data.count();i++)
        {
            QString a=temp2.data.at(i).at(0);
            mb_t.append((double)(a.toFloat()));
            a=temp2.data.at(i).at(1);
            mb_drr.append((double)filter_mbrr.RealFIR((a.toFloat())));
            a=temp2.data.at(i).at(2);
            mb_dri.append((double)(a.toFloat()));
        }
        //load all data

        QList<double> show_ecg_t,show_ecg_d,show_ecg_d2,max_key_ecg;
        for(i=fs_ecg*t0;i<fs_ecg*t1;i++)
        {
            show_ecg_t.append(ecg_t.at(i));
            show_ecg_d.append(ecg_d.at(i));
        }
        //select data t0 to t1 of ecg
        mapminmax.GetMinMax(show_ecg_d);
        mapminmax.Change(show_ecg_d,&show_ecg_d2);
        findpeaks.Find(show_ecg_d2,show_ecg_t,&max_key_ecg);

        ui->plot->graph(0)->addData(show_ecg_t.toVector(),show_ecg_d2.toVector());
        ui->plot->xAxis->setRange(t0,t1);
        ui->plot->replot();
        //end of the ecg data
        QList<double> show_mb_t,show_mb_d,show_mb_d2,max_key_mb;
        for(i=fs_mb*t0;i<fs_mb*t1;i++)
        {
            show_mb_t.append(mb_t.at(i));
            show_mb_d.append(mb_drr.at(i));
        }
        //select data t0 to t1 of mb

        mapminmax.GetMinMax(show_mb_d);
        mapminmax.Change(show_mb_d,&show_mb_d2);
        FindMinMax_ecg.Set(0);
        findpeaks.Find(show_mb_d2,show_mb_t,&max_key_mb);

        ui->plot->graph(1)->addData(show_mb_t.toVector(),show_mb_d2.toVector());
        // rescale value (vertical) axis to fit the current data:
        for(i=0;i<max_key_ecg.count();i++)
        {
            QCPItemTracer *groupTracer = new QCPItemTracer(ui->plot);
            groupTracer->setGraph(ui->plot->graph(0));
            groupTracer->setGraphKey(max_key_ecg[i]);
            groupTracer->setInterpolating(true);
            groupTracer->setStyle(QCPItemTracer::tsCircle);
            groupTracer->setPen(QPen(Qt::red));
            groupTracer->setBrush(Qt::red);
            groupTracer->setSize(7);
        }
        for(i=0;i<max_key_mb.count();i++)
        {
            QCPItemTracer *groupTracer = new QCPItemTracer(ui->plot);
            groupTracer->setGraph(ui->plot->graph(1));
            groupTracer->setGraphKey(max_key_mb[i]);
            groupTracer->setInterpolating(true);
            groupTracer->setStyle(QCPItemTracer::tsCircle);
            groupTracer->setPen(QPen(Qt::blue));
            groupTracer->setBrush(Qt::blue);
            groupTracer->setSize(7);
        }
        //XueYa();
        double xueya_T=XueYa_T(max_key_ecg,max_key_mb);
        ui->plot->replot();
        ui->Ed_info->setText(QString("Ave_T=%1").arg(xueya_T));

}

void DataReplay::on_Bt_Play_clicked()
{
        Play();
}
