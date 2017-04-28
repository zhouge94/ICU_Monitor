/*************************************************************
    FileName : demo.c
    FileFunc : 测试串口应用
    Version  : V0.1
    Author   : Sunrier
    Date     : 2012-06-13
    Descp    : Linux下实现串口库
*************************************************************/
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include"unistd.h"
int main2(int argc,char *argv[])
{
    int iResult = -1;
    int fd = -1,iCommPort,iBaudRate,iDataSize,iStopBit;
    char cParity;
    int iLen;
    char szBuffer[500];

    iCommPort = 11;
    fd = open_port("/dev/ttyUSB0");
    if( fd<0 )
    {
        perror("open_port error !");
        return 1;
    }

    iBaudRate = 115200;
    iDataSize = 8;
    cParity = 'N';
    iStopBit = 1;
    iResult = set_port(fd,iBaudRate,iDataSize,cParity,iStopBit);
    if( iResult<0 )
    {
        perror("set_port error !");
        return 1;
    }

    printf("fd = %d \n",fd);
    do{
        iLen = read_port(fd,szBuffer,100);
        if(iLen)
        {
            szBuffer[iLen+1] = '\0';
            printf("iLen =  %d ,szBuffer = %s \n",iLen,szBuffer);
        }
        usleep(50000);
    }
    while(1);
    return 0;
}
