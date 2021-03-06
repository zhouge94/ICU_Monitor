#ifndef SYS_H
#define SYS_H

#include <QString>
#include "sys/time.h"
#include "my_cvs.h"
#include <iostream>
#include <vector>
#include "string.h"
#include "mapminmax.h"
#include "findpeaks.h"
typedef struct
{
    bool IsBeginRecode;
    float TiWen;
    float ssxl;
    float pjxl;
    float FPS1;
    float FPS2;
    float FPS3;

    float ecg_hq;
    float RecievedFloatArray[500];
    QList<double> common_t;
    QList<double> tiwendata;
    QList<double> rthtdata;
    QList<double> pjhtdata;
    QList<double> tw_axdata;
    QList<double> tw_aydata;
    QList<double> tw_azdata;
    QList<double> tw_gxdata;
    QList<double> tw_gydata;
    QList<double> tw_gzdata;
    QList<double> spo2data;
    QList<double> xueya_t;
    QList<double> xueya_data;
    QList<double> xueya_dataT;

    QList<double>ecgdata_t;
    QList<double> ecgdata;

    QList<double> mbrrdata_t;
    QList<double> mbridata_t;
    QList<double> mbrrdata;
    QList<double> mbridata;

    QList<double> hxdata;
    QList<double> hxdata_t;

    QList<double> maxecg_v;
    QList<double> maxecg_t;

    QList<double> maxmb_v;
    QList<double> maxmb_t;
    int ecgdata_index_cur;
    int ecgdata_index_last;
    int mbdata_index_cur;
    int mbdata_index_last;
    int hxdata_index_cur;
    int hxdata_index_last;
    float ecgdata_FPS;
    double ecgrate;
    double mbrate;
    double hxrate;
    double ecgtime=0;
    double mbtime=0;
    double hxtime=0;

    double StartTime;
    double mbrr;
    double mbri;
    double hx;
    double spo2;
    double spo2_A;
    double spo2_B;
    double xueya;
    double xueya_ave;
    double xueya_A;
    double xueya_B;
    double ax,ay,az,gx,gy,gz;
    double hx_count;
    double huxilv;
    int uart_ecg_count=0;
    int count;
    int count2;
///////////////////////////////////////////////////////////
    double plot_range_TRange_EcgMb;
    double plot_range_TRange_Hx;
    double plot_range_V0_Ecg;
    double plot_range_V1_Ecg;
    double plot_range_VRange_Ecg;
    bool Show_RR_RI;
////////////////////////////////////////////////////////////
}sys_S;
extern sys_S sys;

void AddData(unsigned char chx,unsigned int data);
double GetTimeToDouble(void);
float XueYa(void);
double XueYa_T(QList<double>ecg_max_t,QList<double>mb_max_t);
void SaveData(QString filename);
int myexec(QString cmd, QList<QString> &resvec);
double XueYang(QList<double> mb_rr,QList<double> mb_ri);
#endif // SYS_H
