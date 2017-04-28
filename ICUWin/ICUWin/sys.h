#ifndef SYS_H
#define SYS_H

#include <QString>
#include "sys/time.h"
#include "my_cvs.h"
#include <iostream>
#include <vector>
#include "string.h"
typedef struct
{
    bool IsBeginRecode;
    float TiWen;
    float ssxl;
    float pjxl;
    float FPS1;
    float FPS2;
    float FPS3;
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
    QList<double> xueyadata;
    QList<double> xueyaTdata;

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
    double ecgtime=0;
    double mbtime=0;
    double hxtime=0;

    double StartTime;
    double mbrr;
    double mbri;
    double hx;
    double spo2;
    double XueYa_T;
    double XueYa_t;
    double XueYa_v;
    double XueYa_v_c;
    double ax,ay,az,gx,gy,gz;

    int uart_ecg_count=0;
    int count;
    int count2;
}sys_S;
extern sys_S sys;

void AddData(unsigned char chx,float data);
double GetTimeToDouble(void);
float XueYa(void);
void SaveData(QString filename);
int myexec(QString cmd, QList<QString> &resvec);
#endif // SYS_H