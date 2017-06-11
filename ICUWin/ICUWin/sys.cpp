#include "sys.h"
#include "filter.h"
#include "iostream"
#include "qcustomplot.h"
sys_S sys;
void AddData(unsigned char chx,unsigned int data)
{
    float value,value2;
    unsigned int temp;
    static double ecg_T=1/sys.ecgrate;
    static double mb_T=1/sys.mbrate;
    static unsigned int data_int;
    static float *p_float=(float *)&data_int;
    static float data_float;
    static float hx_last;
    static float hx_cur;
    static float hx_diff;
    static float hx0=0,hx_t0=0,hx_t1=0;
    data_int=data;
    data_float=*p_float;
    sys.RecievedFloatArray[chx]=data_float;
    if(sys.IsBeginRecode)
    {
        switch(chx)
        {
        case 9:
            sys.hxtime+=0.01;
            hx_cur=data_float;
            if(sys.hxtime>0.01)
            {
                sys.hxdata_t.append(sys.hxtime);
                hx_diff=hx_cur-hx_last;
                sys.hx=filter_hx.RealFIR(hx_diff);
                sys.hxdata.append(sys.hx);
                sys.hxdata_index_cur=sys.hxdata.count();
                if(sys.hx<=-1200&&hx0>=-1200)
                {
                    hx_t1=sys.ecgtime;
                    if(hx_t1-hx_t0>1)
                    {
                        sys.hx_count++;
                        std::cout<<"HX_COUNT:"<<sys.hx_count<<"*******************"<<std::endl;
                    }
                    hx_t0=hx_t1;
                }
                hx0=sys.hx;
            }
            hx_last=hx_cur;
            break;
        case 10:
            sys.count++;
            sys.ecgtime+=ecg_T;
            if(sys.ecg_hq==0)value2=0;
            else value2=data_float;
            //value=filter_ecg.RealFIR(value2);
            value=value2;
            sys.ecgdata.append(value);
            sys.ecgdata_t.append(sys.ecgtime);
            sys.ecgdata_index_cur=sys.ecgdata.count();
            break;
        case 11:
            sys.ecg_hq=data_float;
            break;
        case 12:
            sys.ssxl=data_float;
            break;
        case 20:
            temp=data;
            sys.mbri=filter_mbri.RealFIR(65536-temp>>16);
            //sys.mbri=65536-temp>>16;
            sys.mbridata.append(sys.mbri);
            sys.mbdata_index_cur=sys.mbridata.count();
            sys.mbrr=filter_mbrr.RealFIR(65536-(temp<<16)>>16);
            //sys.mbrr=65536-(temp<<16)>>16;
            sys.mbrrdata.append(sys.mbrr);

            sys.mbtime+=mb_T;
            sys.mbridata_t.append(sys.mbtime);
            sys.mbrrdata_t.append(sys.mbtime);
            sys.count2++;
            break;
        case 22:
            sys.spo2=data_float;
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
double AC_DC(QList<double>in)
{
    QList<int> sign;
    QList<int> indMax;
    QList<double>max;
    QList<int> indMin;
    QList<double>min;
    QList<double>AC,DC;
    int count=in.count();
    for(int i=1;i<count;i++)          /*相邻值做差：小于0，赋-1  *大于0，赋1  *等于0，赋0   */
    {
        double diff = in.at(i) - in.at(i-1);
        if(diff>0)sign.append(1);
        else if(diff<0)sign.append(-1);
        else sign.append(0);
    }
    for(int j=1;j<sign.size();j++)  //再对sign相邻位做差  //保存max的位置
    {
        int diff = sign[j]-sign[j-1];
        if(diff<0) indMax.push_back(j);
    }
    for(int j=1;j<sign.size();j++)  //再对sign相邻位做差  //保存min的位置
    {
        int diff = sign[j]-sign[j-1];
        if(diff>0) indMin.push_back(j);
    }

    for(int j=0;j<indMax.count()-1;) //recheck max
    {
        if(indMax.at(j+1)-indMax.at(j)<100)
        {
            if(in.at(indMax[j])>in.at(indMax[j+1]))indMax.removeAt(j+1);
            else indMax.removeAt(j);
        }else
        {
            j++;
        }
    }
    for(int j=0;j<indMin.count()-1;) //recheck min
    {
        if(indMin.at(j+1)-indMin.at(j)<100)
        {
            if(in.at(indMin[j])<in.at(indMin[j+1]))indMin.removeAt(j+1);
            else indMin.removeAt(j);
        }else
        {
            j++;
        }
    }
    if(indMin[0]<indMax[0])indMin.removeAt(0);
    for(int m = 0;m<indMax.size();m++)
    {
        max.append(in.at(indMax[m]));
    }
    for(int m = 0;m<indMin.size();m++)
    {
        if(m>indMax.size())break;
        min.append(in.at(indMin[m]));
        AC.append(max[m]-min[m]);
        DC.append((max[m]+min[m])/2);
    }
    double ave_ac,ave_dc;
    ave_ac=ZhongZhiFilter(1,AC);
    ave_dc=65536.0-ZhongZhiFilter(1,DC);
    std::cout<<"  AVEAC:"<<ave_ac<<" ";
    std::cout<<"  AVEDC:"<<ave_dc<<" ";
    std::cout<<std::endl;
    return ave_ac/ave_dc;

}
double XueYang(QList<double> mb_rr,QList<double> mb_ri)
{
    std::cout<<"Begin XueYang Cal----------------------------------"<<std::endl;
    double R1,R2,R;
    R1=AC_DC(mb_rr);
    R2=AC_DC(mb_ri);
    R=R1/R2;
    sys.spo2=sys.spo2_A*R+sys.spo2_B;
    std::cout<<"  R:"<<R<<" SPO2:"<<sys.spo2<<std::endl;
    if(sys.spo2>100)sys.spo2=100;
    std::cout<<"Begin XueYang Cal----------------------------------"<<std::endl;
    std::cout<<"End XueYang Cal----------------------------------"<<std::endl;

}
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
        xueya_sheet.data.append(a);
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
