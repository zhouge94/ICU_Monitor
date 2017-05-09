#include "sys.h"
#include "filter.h"
#include "iostream"
#include "qcustomplot.h"
sys_S sys;
void AddData(unsigned char chx,float data)
{
    float value,value2;
    static double ecg_T=1/sys.ecgrate;
    static double mb_T=1/sys.mbrate;
    sys.RecievedFloatArray[chx]=data;
    if(sys.IsBeginRecode)
    {
        switch(chx)
        {
        case 9:
            sys.hxtime+=0.01;
            sys.hxdata_t.append(sys.hxtime);
            sys.hx=filter_hx.RealFIR(data);;
            //sys.hx=(data);;
            sys.hxdata.append(sys.hx);
            sys.hxdata_index_cur=sys.hxdata.count();
            break;
        case 10:
            sys.count++;
            sys.ecgtime+=ecg_T;
            if(sys.ecg_hq==0)value2=0;
            else value2=data;
            //value=filter_ecg.RealFIR(value2);
            value=value2;
            sys.ecgdata.append(value);
            sys.ecgdata_t.append(sys.ecgtime);
            sys.ecgdata_index_cur=sys.ecgdata.count();
            break;
        case 11:
            sys.ecg_hq=data;
            break;
        case 12:
            sys.ssxl=data;
            break;
        case 20:
            sys.mbtime+=mb_T;
            sys.mbri=filter_mbri.RealFIR(65536-((int)data)>>16);
            //sys.mbri=65536-((int)data)>>16;
            sys.mbridata_t.append(sys.mbtime);
            sys.mbridata.append(sys.mbri);
            sys.mbdata_index_cur=sys.mbridata.count();
            sys.mbrr=65536-(data&&0x0000ffff);
            sys.mbrrdata_t.append(sys.mbtime);
            sys.mbrrdata.append(sys.mbrr);
            sys.count2++;
            break;
        case 21:
            break;
        case 22:
            sys.spo2=data;
            break;
        default:
            break;
        }
    }

}
/*
float XueYa(void)
{
    double difft[50];
    double t_mb0,t_ecg0,t_ecg1;
    int i=0,j=0,count=0,N_mb,N_ecg;
    N_mb=sys.maxmb_t.count();
    N_ecg=sys.maxecg_t.count();
    if(N_ecg<2)return 0;
    while(i<N_mb&&j<N_ecg-1)
    {
        t_mb0=sys.maxmb_t.at(i);
        t_ecg0=sys.maxecg_t.at(j);
        t_ecg1=sys.maxecg_t.at(j+1);
        if(t_mb0<=t_ecg0)i++;
        else if(t_mb0>=t_ecg1)j++;
        else if(t_mb0>t_ecg0&&t_mb0<t_ecg1)
        {
            std::cout<<"Find XueYa  -----t:"<<t_mb0-t_ecg0<<",HT："<<60.0/(t_ecg1-t_ecg0)<<std::endl;
            difft[count++]=t_mb0-t_ecg0;
            i++;
            j++;
        }
    }
    if((count-1)>10)
    {
        //sys.XueYa_T=ZhongZhiFilter(count-1,difft);
        std::cout<<"Find XueYa T:"<<sys.XueYa_T<<",P:"<<sys.XueYa_T*100+60<<std::endl;
        return sys.XueYa_T;
    }else
    {
        std::cout<<"Error! Just Found T of "<<count<<std::endl;
    }
}
*/
double XueYa_T(QList<double>ecg_max_t,QList<double>mb_max_t)
{
    QList<double> T;
    int i=0,j=0;
    while(1)
    {
        if(i>=(ecg_max_t.count()-1)||j>=mb_max_t.count())break;
        if(ecg_max_t[i]<=mb_max_t[j]&&ecg_max_t[i+1]>=mb_max_t[j])
        {
            T.append(mb_max_t[j]-ecg_max_t[i]);
            i++;
            j++;
        }
        else if(ecg_max_t[i]>mb_max_t[j]) j++;
        else if(ecg_max_t[i+1]<mb_max_t[j]) i++;
    }
    double ave_T=ZhongZhiFilter(1,T);
    std::cout<<"found T of "<<T.count()<<",ave_T="<<ave_T<<" :";
    for(i=0;i<T.count();i++)std::cout<<T[i]<<" ";
    std::cout<<std::endl;
    return ave_T;

}

double GetTimeToDouble(void)
{
    struct  timeval tv;
    double time;
    gettimeofday(&tv,NULL);
    time=tv.tv_sec+tv.tv_usec/1000000.0;
    return time;
}

void SaveData(QString filename)
{
    Sheet ecg_sheet,mb_sheet,xueya_sheet,mpu6050_sheet,huxi_sheet,common_sheet;
    int i;
    FileParse fd;
    QStringList a;
    system("mkdir Data");
    //save ecg data
    for(i=0;i<sys.ecgdata.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.ecgdata_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.ecgdata.at(i),12,'f',2,' '));
        ecg_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_ecg.csv"),ecg_sheet);
    //save maibo data
    for(i=0;i<sys.mbridata.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.mbridata_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.mbridata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.mbrrdata.at(i),12,'f',2,' '));
        mb_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_mb.csv"),mb_sheet);
    //save xueya data
    for(i=0;i<sys.xueya_t.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.xueya_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.xueya_dataT.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.xueya_data.at(i),12,'f',2,' '));
        mb_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_xueya.csv"),xueya_sheet);
    //save huxi data
    for(i=0;i<sys.hxdata_t.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.hxdata_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.hxdata.at(i),12,'f',2,' '));
        huxi_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_huxi.csv"),huxi_sheet);
    //save mpu6050 data
    for(i=0;i<sys.common_t.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.common_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.tw_axdata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tw_aydata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tw_azdata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tw_gxdata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tw_gydata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tw_gzdata.at(i),12,'f',2,' '));
        mpu6050_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_tw.csv"),mpu6050_sheet);
    //save common data
    for(i=0;i<sys.common_t.count();i++)
    {
        a.clear();
        a.append(QString("%1").arg(sys.common_t.at(i),7,'f',6,' '));
        a.append(QString("%1").arg(sys.rthtdata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.pjhtdata.at(i),12,'f',2,' '));
        a.append(QString("%1").arg(sys.tiwendata.at(i),12,'f',2,' '));
        common_sheet.data.append(a);
    }
    fd.generateCSV(QString("Data/")+filename+QString("_common.csv"),common_sheet);

    //tar all the data
    QString cmd=QString("tar -cvf Data/temp.tar Data/*.csv ;rm Data/*.csv;mv Data/temp.tar Data/")+filename+QString(".tar");
    system(cmd.toStdString().c_str());
}
//execute shell command
//执行一个shell命令，输出结果逐行存储在resvec中，并返回行数
int myexec(QString cmd, QList<QString> &resvec) {
    resvec.clear();
    FILE *pp = popen(cmd.toStdString().data(), "r"); //建立管道
    if (!pp) {
        return -1;
    }
    char tmp[1024]; //设置一个合适的长度，以存储每一行输出
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0'; //去除换行符
        }
        resvec.append(QString(tmp));
    }
    pclose(pp); //关闭管道
    return resvec.count();
}
