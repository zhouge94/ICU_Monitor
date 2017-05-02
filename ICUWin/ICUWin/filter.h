#ifndef FILTER_H
#define FILTER_H
class FIR_Filter
{
public:
    FIR_Filter();
    ~FIR_Filter();
    double RealFIR(float v);
    void SetFilterA(double *AA, int N);
private:
    double *A;
    float V[500];
    int count=0;
    int N;
};
class FindMinMax
{
public:
    FindMinMax();
    ~FindMinMax();
    bool input(double key, float in);
    void Set(double difflevel);
    float level_diff_;
    float level_v_;
    float min;
    float max;
    double minkey;
    double maxkey;
    double DiffMaxKey;
    double DiffMinKey;
    double DiffMinMaxKey;
    double DiffMaxMinKey;
    void Set2(int n0, int n, float Level);
private:
    int index;
    bool IsFindLevel;
    float Diff[2];
    float LastV;
    float Min;
    float Max;
    double LastKey;
    double Lastminkey;
    double Lastmaxkey;
    int count=0;
    int N;
    int N0;
    int MinN;
    int MaxN;
    double MinKey;
    double  MaxKey;

};
extern class FIR_Filter filter_bandpass1;
extern class FIR_Filter filter_bandpass2;
extern class FIR_Filter filter_low1;
extern class FindMinMax FindMinMax_mb;
extern class FindMinMax FindMinMax_ecg;

extern double firA[50];
extern double firB[250];
extern double firC[100];
double ZhongZhiFilter(int N,double *DATE_RAW );

#endif // FILTER_H
