#include "filter.h"
#include "iostream"
double fir_mb[50]={
-0.000940895795466934,-0.000723570825009934,-0.000504858254411897,-0.000205597964749794,0.000256665082358683,0.000963097433562612,0.00198887648068588,0.00339861775569270,0.00524217453689476,0.00755104018952045,0.0103355571964583,0.0135830990571389,0.0172573440022303,0.0212987051836878,0.0256259234593074,0.0301387691653926,0.0347217415240330,0.0392486016509205,0.0435875303594374,0.0476066675397240,0.0511797677337802,0.0541916978920272,0.0565435087301224,0.0581568304052170,0.0589773754550483,0.0589773754550483,0.0581568304052170,0.0565435087301224,0.0541916978920272,0.0511797677337802,0.0476066675397240,0.0435875303594374,0.0392486016509205,0.0347217415240330,0.0301387691653926,0.0256259234593074,0.0212987051836878,0.0172573440022303,0.0135830990571389,0.0103355571964583,0.00755104018952045,0.00524217453689476,0.00339861775569270,0.00198887648068588,0.000963097433562612,0.000256665082358683,-0.000205597964749794,-0.000504858254411897,-0.000723570825009934,-0.000940895795466934
};//lowpass w0=5Hz
double fir_ecg[100]={
-0.000160232219925400,-0.000396715128249458,-0.000568031764349966,-0.000630377417003998,-0.000549666811734168,-0.000312918192167551,5.85475621761466e-05,0.000499914194083347,0.000904542744119532,0.00114138804272611,0.00108814140279621,0.000673608938756269,-8.29663036853890e-05,-0.00105061231384578,-0.00199614235127918,-0.00262986469563130,-0.00268180194862902,-0.00199105865057657,-0.000582572915964725,0.00129617333166248,0.00319898648350920,0.00457097135151080,0.00489085697856464,0.00383296345707765,0.00140395841921784,-0.00199116335551971,-0.00558663348733729,-0.00840511620850969,-0.00949567630946660,-0.00820831140993986,-0.00443391750676334,0.00126317893011205,0.00767471355081205,0.0131587548119272,0.0160037051588548,0.0148744047522766,0.00923741120995978,-0.000345740702648811,-0.0121491358098523,-0.0234839986418946,-0.0311570380755938,-0.0321079298580049,-0.0240979109868432,-0.00629781977134058,0.0203653632503466,0.0531997308650417,0.0881037947432736,0.120232598212974,0.144850027309309,0.158197074816843,0.158197074816843,0.144850027309309,0.120232598212974,0.0881037947432736,0.0531997308650417,0.0203653632503466,-0.00629781977134058,-0.0240979109868432,-0.0321079298580049,-0.0311570380755938,-0.0234839986418946,-0.0121491358098523,-0.000345740702648811,0.00923741120995978,0.0148744047522766,0.0160037051588548,0.0131587548119272,0.00767471355081205,0.00126317893011205,-0.00443391750676334,-0.00820831140993986,-0.00949567630946660,-0.00840511620850969,-0.00558663348733729,-0.00199116335551971,0.00140395841921784,0.00383296345707765,0.00489085697856464,0.00457097135151080,0.00319898648350920,0.00129617333166248,-0.000582572915964725,-0.00199105865057657,-0.00268180194862902,-0.00262986469563130,-0.00199614235127918,-0.00105061231384578,-8.29663036853890e-05,0.000673608938756269,0.00108814140279621,0.00114138804272611,0.000904542744119532,0.000499914194083347,5.85475621761466e-05,-0.000312918192167551,-0.000549666811734168,-0.000630377417003998,-0.000568031764349966,-0.000396715128249458,-0.000160232219925400
};
double firC[100]={
9.42508722928507e-05,0.000135733453116674,0.000183399561849090,0.000240118102447089,0.000308847911601491,0.000392599288723631,0.000494393826997792,0.000617223031878781,0.000764006236098878,0.000937548336605267,0.00114049788860443,0.00137530609485412,0.00164418722441558,0.00194908098424640,0.00229161734935748,0.00267308433294401,0.00309439914718836,0.00355608316866479,0.00405824107987594,0.00460054451092099,0.00518222045320473,0.00580204466108099,0.00645834019807135,0.00714898122254635,0.00787140204427462,0.00862261141883337,0.00939921198234945,0.0101974246652236,0.0110131178611994,0.0118418410681757,0.0126788626602984,0.0135192113978493,0.0143577212329644,0.0151890789259000,0.0160078739489994,0.0168086501241936,0.0175859584152206,0.0183344102781156,0.0190487309631457,0.0197238121584125,0.0203547633698764,0.0209369614445362,0.0214660976628081,0.0219382218525561,0.0223497830104278,0.0226976659557365,0.0229792235876295,0.0231923043671247,0.0233352747011612,0.0234070359654009,0.0234070359654009,0.0233352747011612,0.0231923043671247,0.0229792235876295,0.0226976659557365,0.0223497830104278,0.0219382218525561,0.0214660976628081,0.0209369614445362,0.0203547633698764,0.0197238121584125,0.0190487309631457,0.0183344102781156,0.0175859584152206,0.0168086501241936,0.0160078739489994,0.0151890789259000,0.0143577212329644,0.0135192113978493,0.0126788626602984,0.0118418410681757,0.0110131178611994,0.0101974246652236,0.00939921198234945,0.00862261141883337,0.00787140204427462,0.00714898122254635,0.00645834019807135,0.00580204466108099,0.00518222045320473,0.00460054451092099,0.00405824107987594,0.00355608316866479,0.00309439914718836,0.00267308433294401,0.00229161734935748,0.00194908098424640,0.00164418722441558,0.00137530609485412,0.00114049788860443,0.000937548336605267,0.000764006236098878,0.000617223031878781,0.000494393826997792,0.000392599288723631,0.000308847911601491,0.000240118102447089,0.000183399561849090,0.000135733453116674,9.42508722928507e-05
};

class FIR_Filter filter_hx;
class FIR_Filter filter_ecg;
class FIR_Filter filter_mbrr;
class FIR_Filter filter_mbri;

class FindMinMax FindMinMax_mb;
class FindMinMax FindMinMax_ecg;
FIR_Filter::FIR_Filter()
{
    count=0;
}

FIR_Filter::~FIR_Filter()
{

}

double FIR_Filter::RealFIR(float v)
{
    double sum=0;
    int i;
    for(i=N-1;i>0;i--)V[i]=V[i-1];
    V[0]=v;
    for(i=0;i<N;i++)sum+=(A[i])*(V[i]);
    if(count>N)return sum;
    else
    {
        count ++;
        return 0;
    }

}

void FIR_Filter::SetFilterA(double *AA,int NN)
{
    A=AA;
    N=NN;
}

FindMinMax::FindMinMax()
{
    LastV=0;
    IsFindLevel=false;
    N=500;
    N0=600;
    index=0;
    level_v_=0;
}

FindMinMax::~FindMinMax()
{
}

bool FindMinMax::input(double key, float in)
{
    bool IsFind=false;
    if(count>N0)
    {
        if(count==(N0+1))
        {
            index=count-MinN;
            /*
            std::cout<<"Min:"<<Min<<",key:"<<MinKey<<",count:"<<MinN<<std::endl;
            std::cout<<"Max:"<<Max<<",key:"<<MaxKey<<",count:"<<MaxN<<std::endl;
            std::cout<<"count:"<<count<<",Index:"<<index<<std::endl;
            std::cout<<"-------------------------------"<<std::endl;
            */
        }//init the window1
        if(index++<N)//find the max value and the first min value after the max value on the window x;
        {
            if(in>Max)
            {
                Max=in;
                MaxKey=key;
                MaxN=count;

                Min=in;
                MinKey=key;
                MinN=count;
            }else if(in<Min)
            {
                Min=in;
                MinKey=key;
                MinN=count;
            }
        }else//to confirm
        {
            if(Max<level_v_)
            {
                std::cout<<"err2"<<std::endl;
                index=count-MaxN;
                if(index>=N)index=0;
            }else if(index==N)
            {
                std::cout<<"err"<<std::endl;
                index=count-MaxN;
                if(index>=N)index=0;
            }else
            {
                maxkey=MaxKey;
                minkey=MaxKey;
                max=Max;
                min=Min;
                index=count-MaxN;
                if(index>=N)index=0;
                /*
                std::cout<<"Max:"<<Max<<",key:"<<MaxKey<<",count:"<<MaxN<<std::endl;
                std::cout<<"Min:"<<Min<<",key:"<<MinKey<<",count:"<<MinN<<std::endl;
                std::cout<<"count:"<<count<<",index:"<<index<<std::endl;
                */
                float temp;
                temp=max;
                Max=Min;
                min=temp;//exchange the max and min
                MaxKey=MinKey;
                MaxN=MinN;
                IsFind=true;
            }
        }
    }else
    {
        if(count==0)
        {
            Min=in;
            Max=in;
        }else
        {
            if(in<Min)
            {
                Min=in;
                MinKey=key;
                MinN=count;

                Max=Min;
                MaxKey=MinKey;
                MaxN=MinN;
            }

        }//to find the fisrt min value on the window0
    }
    count++;
    return IsFind;
}

void FindMinMax::Set(double difflevel)
{
    level_diff_=difflevel;
}
void FindMinMax::Set2(int n0, int n, float Level)
{
    level_v_=Level;
    N0=n0;
    N=n;
}
double ZhongZhiFilter(int N0, QList<double> DATE_RAW )
{
    double value_buf[200],temp;
    double sum=0;
    int count,i,j;
    if(N0>=DATE_RAW.count()/2)return 0;
    for(count=0;count<DATE_RAW.count();count++)
    {
        value_buf[count] = DATE_RAW[count];
    }
    for (j=0;j<DATE_RAW.count()-1;j++)
    {
        for (i=0;i<DATE_RAW.count()-j-1;i++)
        {
            if ( value_buf[i]>value_buf[i+1] )
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i+1];
                value_buf[i+1] = temp;
            }
        }
    }
    for(count=N0;count<(DATE_RAW.count()-N0);count++)
        sum += value_buf[count];
    return (double)(sum/(DATE_RAW.count()-2*N0));
}
