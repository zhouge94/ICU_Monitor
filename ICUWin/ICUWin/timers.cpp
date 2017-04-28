#include "mainwindow.h"
void MainWindow::realtimeDataSlot_show1()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double ecg_key;
    static double mb_key;
    static double hx_key;
    static double lastPointKey = 0;
    QVector<double> vector_ecgkey;
    QVector<double> vector_ecgdata;
    QVector<double> vector_mbkey;
    QVector<double> vector_mbdata;
    QVector<double> vector_hxkey;
    QVector<double> vector_hxdata;
    int i,i0,i1,i2,i3,i4,i5;
    if(sys.IsBeginRecode)
    {
        if (key-lastPointKey > 0.02) // at most add point every 20 ms
        {
            i0=sys.ecgdata_index_last;
            i1=sys.ecgdata_index_cur;

            i2=sys.mbdata_index_last;
            i3=sys.mbdata_index_cur;

            i4=sys.hxdata_index_last;
            i5=sys.hxdata_index_cur;

            sys.ecgdata_index_last=i1;
            sys.mbdata_index_last=i3;
            sys.hxdata_index_last=i5;

            for(i=i0;i<i1;i++)
            {
                if(!(i%4))
                {
                    ecg_key=sys.ecgdata_t.at(i);
                    vector_ecgkey.append(ecg_key);
                    vector_ecgdata.append(sys.ecgdata.at(i));
                }
            }
            for(i=i2;i<i3;i++)
            {
                mb_key=sys.mbridata_t.at(i);
                vector_mbkey.append(mb_key);
                vector_mbdata.append(sys.mbridata.at(i));
            }
            for(i=i4;i<i5;i++)
            {
                hx_key=sys.hxdata_t.at(i);
                vector_hxkey.append(hx_key);
                vector_hxdata.append(sys.hxdata.at(i));
            }

            // add data to lines:
            ui->plot1_xinlv->graph(0)->addData(vector_ecgkey,vector_ecgdata,0);
            // rescale value (vertical) axis to fit the current data:
            ui->plot1_xinlv->graph(0)->rescaleValueAxis(false,true);
            // add data to lines:
            ui->plot1_tiwei->graph(0)->addData(vector_mbkey,vector_mbdata,0);
            // rescale value (vertical) axis to fit the current data:
            ui->plot1_tiwei->graph(0)->rescaleValueAxis(false,true);
            // add data to lines:
            ui->plot1_huxi->graph(0)->addData(vector_hxkey,vector_hxdata,0);
            // rescale value (vertical) axis to fit the current data:
            ui->plot1_huxi->graph(0)->rescaleValueAxis(true,false);
            //ui->plot1_xinlv->graph(0)->getValueRange()
            //ui->plot1_xinlv->yAxis->setRange(-1000,10000);
            lastPointKey = key;
        }

        static double LastEcgPointKey=0;
        static double LastmbPointKey=0;
        static double LastHxPointKey=0;
        static double FirstIn=0;
        if(FirstIn==0)
        {
            ui->plot1_xinlv->xAxis->setRange(0,5);
            ui->plot1_tiwei->xAxis->setRange(0,5);
            ui->plot1_huxi->xAxis->setRange(0,10);
            FirstIn++;
        }
        if(key-LastHxPointKey > 10)
        {
            ui->plot1_huxi->xAxis->setRange(hx_key,hx_key+10);
            LastHxPointKey=key;
        }
        if(key-LastEcgPointKey > 5)
        {
            ui->plot1_xinlv->xAxis->setRange(ecg_key,ecg_key+5);
            //ui->plot1_tiwei->xAxis->setRange(ecg_key,ecg_key+5);
            LastEcgPointKey=key;
            //LastmbPointKey=key;
        }
        if(key-LastmbPointKey > 5)
        {
            printf("begin to change scale :%f \n",mb_key);
            ui->plot1_tiwei->xAxis->setRange(mb_key,mb_key+6);
            LastmbPointKey=key;
        }

        // make key axis range scroll with the data (at a constant range size of 8):
        //ui->Plot1->yAxis->setRange(ui->doubleSpinBox_YScale1_->tex1t().toFloat(), ui->doubleSpinBox_YScale2_->text().toFloat());
        ui->plot1_xinlv->replot();
        ui->plot1_huxi->replot();
        ui->plot1_tiwei->replot();
    }
}

void MainWindow::UartCallback2()
{
    int err;
    char temp;
    if(uart2.Is_connect==1)
    {
        if(uart2.read_port(&temp,1))
        {
            do{
                err=uart2.RecievetoFloatArray(temp);
                if(err==0xff)
                {
                    uart2.Uart_data_count_cur++;
                }
            }while(uart2.Is_connect==1&&uart2.read_port(&temp,1));

        }
    }
    usleep(100);
    UartTimer2.start(0);

}

void MainWindow::UartCallback()
{
    int err;
    char temp;
    if(uart.Is_connect==1)
    {
        if(uart.read_port(&temp,1))
        {
            do{
                err=uart.RecievetoFloatArray(temp);
                if(err==0xff)
                {
                    uart.Uart_data_count_cur++;
                }
            }while(uart.Is_connect==1&&uart.read_port(&temp,1));
        }
    }
    usleep(100);
    UartTimer.start(0);
}
void MainWindow::SecondCallBack()
{
    static int count,pjxl_sum,i;
    if(count++<20)pjxl_sum+=sys.ssxl;
    else
    {
        sys.pjxl=pjxl_sum/20.0;
        count=0;
        pjxl_sum=0;
    }
    if(i++%2)
    {
        std::cout<<"rate1:"<<sys.count<<",rate1:"<<sys.count2<<std::endl;
        sys.count=0;
        sys.count2=0;
    }
    ui->show1_tw->setText(QString("%1").arg(sys.TiWen,5,'f',1,' '));
    ui->show1_ssxl->setText(QString("%1").arg(sys.ssxl,5,'f',1,' '));
    ui->show1_pjxl->setText(QString("%1").arg(sys.pjxl,5,'f',1,' '));
    ui->show1_jkzk->setText(QString("%1").arg(sys.spo2,5,'f',1,' '));
    ui->show1_ssy->setText(QString("%1").arg(sys.XueYa_v,5,'f',1,' '));
    ui->show1_szy->setText(QString("%1").arg(sys.XueYa_v_c,5,'f',1,' '));
    QString tiwei;
    if(sys.ax>=sys.ay&&sys.ax>=sys.az)
    {
        tiwei="站立";
    }else if(sys.ay>=sys.ax&&sys.ay>=sys.az)
    {
        tiwei="侧躺";

    }else if(sys.az>=sys.ay&&sys.az>=sys.ax)
    {
        tiwei="平躺";
    }
    ui->show1_tiwei->setText(tiwei);
    //////////////////////////////////////////////////////
    QCPItemTracer *groupTracer = new QCPItemTracer(ecgPlot);
    if(sys.maxecg_t.count())
    {
        groupTracer->setGraph(ecgPlot->graph(0));
        groupTracer->setGraphKey(sys.maxecg_t.last());
        groupTracer->setInterpolating(true);
        groupTracer->setStyle(QCPItemTracer::tsCircle);
        groupTracer->setPen(QPen(Qt::red));
        groupTracer->setBrush(Qt::red);
        groupTracer->setSize(7);
    }
    if(sys.maxmb_t.count())
    {

        groupTracer = new QCPItemTracer(mbPlot);
        groupTracer->setGraph(mbPlot->graph(0));
        groupTracer->setGraphKey(sys.maxmb_t.last());
        groupTracer->setInterpolating(true);
        groupTracer->setStyle(QCPItemTracer::tsCircle);
        groupTracer->setPen(QPen(Qt::green));
        groupTracer->setBrush(Qt::green);
        groupTracer->setSize(7);
    }
    /////////////////////////////////////////////////////////
}

void MainWindow::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.02) // at most add point every 20 ms
    {
        // add data to lines:
        if(ui->checkBox_CH0->isChecked())ui->Plot0->graph(0)->addData(key, (double)sys.RecievedFloatArray[0]);
        if(ui->checkBox_CH1->isChecked())ui->Plot0->graph(1)->addData(key, (double)sys.RecievedFloatArray[1]);
        if(ui->checkBox_CH2->isChecked())ui->Plot0->graph(2)->addData(key, (double)sys.RecievedFloatArray[2]);
        if(ui->checkBox_CH3->isChecked())ui->Plot0->graph(3)->addData(key, (double)sys.RecievedFloatArray[3]);
        if(ui->checkBox_CH4->isChecked())ui->Plot0->graph(4)->addData(key, (double)sys.RecievedFloatArray[4]);
        if(ui->checkBox_CH5->isChecked())ui->Plot0->graph(5)->addData(key, (double)sys.RecievedFloatArray[5]);
        if(ui->checkBox_CH6->isChecked())ui->Plot0->graph(6)->addData(key, (double)sys.RecievedFloatArray[6]);
        if(ui->checkBox_CH7->isChecked())ui->Plot0->graph(7)->addData(key, (double)sys.RecievedFloatArray[7]);
        if(ui->checkBox_CH8->isChecked())ui->Plot0->graph(8)->addData(key, (double)sys.RecievedFloatArray[8]);
        if(ui->checkBox_CH9->isChecked())ui->Plot0->graph(9)->addData(key, (double)sys.RecievedFloatArray[9]);
        if(ui->checkBox_CH10->isChecked())ui->Plot1->graph(0)->addData(key, (double)sys.RecievedFloatArray[10]);
        if(ui->checkBox_CH11->isChecked())ui->Plot1->graph(1)->addData(key, (double)sys.RecievedFloatArray[11]);
        if(ui->checkBox_CH12->isChecked())ui->Plot1->graph(2)->addData(key, (double)sys.RecievedFloatArray[12]);
        if(ui->checkBox_CH13->isChecked())ui->Plot1->graph(3)->addData(key, (double)sys.RecievedFloatArray[13]);
        if(ui->checkBox_CH14->isChecked())ui->Plot1->graph(4)->addData(key, (double)sys.RecievedFloatArray[14]);
        if(ui->checkBox_CH15->isChecked())ui->Plot1->graph(5)->addData(key, (double)sys.RecievedFloatArray[15]);
        if(ui->checkBox_CH16->isChecked())ui->Plot1->graph(6)->addData(key, (double)sys.RecievedFloatArray[16]);
        if(ui->checkBox_CH17->isChecked())ui->Plot1->graph(7)->addData(key, (double)sys.RecievedFloatArray[17]);
        if(ui->checkBox_CH18->isChecked())ui->Plot1->graph(8)->addData(key, (double)sys.RecievedFloatArray[18]);
        if(ui->checkBox_CH19->isChecked())ui->Plot1->graph(9)->addData(key, (double)sys.RecievedFloatArray[19]);
        ui->label_CH0->setText(QString("%1").arg(sys.RecievedFloatArray[0],7,'f',2,' '));
        ui->label_CH1->setText(QString("%1").arg(sys.RecievedFloatArray[1],7,'f',2,' '));
        ui->label_CH2->setText(QString("%1").arg(sys.RecievedFloatArray[2],7,'f',2,' '));
        ui->label_CH3->setText(QString("%1").arg(sys.RecievedFloatArray[3],7,'f',2,' '));
        ui->label_CH4->setText(QString("%1").arg(sys.RecievedFloatArray[4],7,'f',2,' '));
        ui->label_CH5->setText(QString("%1").arg(sys.RecievedFloatArray[5],7,'f',2,' '));
        ui->label_CH6->setText(QString("%1").arg(sys.RecievedFloatArray[6],7,'f',2,' '));
        ui->label_CH7->setText(QString("%1").arg(sys.RecievedFloatArray[7],7,'f',2,' '));
        ui->label_CH8->setText(QString("%1").arg(sys.RecievedFloatArray[8],7,'f',2,' '));
        ui->label_CH9->setText(QString("%1").arg(sys.RecievedFloatArray[9],7,'f',2,' '));
        ui->label_CH10->setText(QString("%1").arg(sys.RecievedFloatArray[10],7,'f',2,' '));
        ui->label_CH11->setText(QString("%1").arg(sys.RecievedFloatArray[11],7,'f',2,' '));
        ui->label_CH12->setText(QString("%1").arg(sys.RecievedFloatArray[12],7,'f',2,' '));
        ui->label_CH13->setText(QString("%1").arg(sys.RecievedFloatArray[13],7,'f',2,' '));
        ui->label_CH14->setText(QString("%1").arg(sys.RecievedFloatArray[14],7,'f',2,' '));
        ui->label_CH15->setText(QString("%1").arg(sys.RecievedFloatArray[15],7,'f',2,' '));
        ui->label_CH16->setText(QString("%1").arg(sys.RecievedFloatArray[16],7,'f',2,' '));
        ui->label_CH17->setText(QString("%1").arg(sys.RecievedFloatArray[17],7,'f',2,' '));
        ui->label_CH18->setText(QString("%1").arg(sys.RecievedFloatArray[18],7,'f',2,' '));
        ui->label_CH19->setText(QString("%1").arg(sys.RecievedFloatArray[19],7,'f',2,' '));

        // rescale value (vertical) axis to fit the current data:
        //ui->Plot0->graph(0)->rescaleValueAxis();
        //ui->Plot0->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Plot0->yAxis->setRange(ui->doubleSpinBox_YScale1->text().toFloat(), ui->doubleSpinBox_YScale2->text().toFloat());
    ui->Plot0->xAxis->setRange(key, ui->doubleSpinBox_XScale->text().toFloat(), Qt::AlignRight);
    ui->Plot0->replot();
    ui->Plot1->yAxis->setRange(ui->doubleSpinBox_YScale1_->text().toFloat(), ui->doubleSpinBox_YScale2_->text().toFloat());
    ui->Plot1->xAxis->setRange(key, ui->doubleSpinBox_XScale2->text().toFloat(), Qt::AlignRight);
    ui->Plot1->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        sys.FPS1=frameCount/(key-lastFpsKey);
        ui->label_uart_date_rate->setText(QString("%1 FPS").arg(uart.Uart_data_count_cur/(key-lastFpsKey),0,'f',0));
        ui->label_uart_date_rate2->setText(ui->label_uart_date_rate->text());
        uart.Uart_data_count_cur=0;
        lastFpsKey = key;
        frameCount = 0;
    }
}
void MainWindow::onCommTimeout()
{
    double temp;
    CommTimer.start(100);
    sys.TiWen=sys.RecievedFloatArray[8];
    sys.ax=sys.RecievedFloatArray[0];
    sys.ay=sys.RecievedFloatArray[1];
    sys.az=sys.RecievedFloatArray[2];
    sys.gx=sys.RecievedFloatArray[3];
    sys.gy=sys.RecievedFloatArray[4];
    sys.gz=sys.RecievedFloatArray[5];
    // Check Time
    if(sys.IsBeginRecode)
    {
        temp=GetTimeToDouble()-sys.StartTime;
        sys.ecgtime=temp;
        sys.mbtime=temp;
        sys.hxtime=temp;
        sys.common_t.append(temp);
        sys.tiwendata.append(sys.TiWen);
        sys.rthtdata.append(sys.ssxl);
        sys.pjhtdata.append(sys.pjxl);
        sys.xueyadata.append(sys.XueYa_v);
        sys.xueyaTdata.append(sys.XueYa_T);
        sys.tw_axdata.append(sys.ax);
        sys.tw_aydata.append(sys.ay);
        sys.tw_azdata.append(sys.az);
        sys.tw_gxdata.append(sys.gx);
        sys.tw_gydata.append(sys.gy);
        sys.tw_gzdata.append(sys.gz);
        //update common data

    }

}
