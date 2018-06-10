

#ifndef wavedealer_h
#define wavedealer_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculate.h"
#include "substitude.h"

#define uchar unsigned char
#define uint unsigned int
#define maxsize 10240


uchar riff[4] = { "RIFF"};
uchar size_total[4];
uchar wave[4] = { "WAVE" };
uchar fmt[4] = { "fmt " };
uchar fmt_size[4];
uchar fmt_pcm[2] = { 0x01,0x00 };
uchar fmt_way[2];
uchar fmt_samplehz[4];
uchar fmt_bytepsec[4];
uchar fmt_bytepsample[2];
uchar fmt_bitpsample[2];
uchar fmt_nouse[2];
uchar data[5] = { "data" };
uchar data_size[4];
uchar *mp; // global variable: to store the calculated value
uint d_totalsize;
uint d_fmtsize;
uint d_way;
uint d_samplehz;
uint d_bytepsec;
uint d_bytepsample;
uint d_bitpsample;
uint d_datasize;
uint timelen;
 // several head file parameters. Because of it is a standard and it will be use in a lot functions I wrote, so I set it as global variable.

FILE *fq; // file pointer points to the .wav file going to write

long int cal(char * exp); // because we need cal() to calculate the value
int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr);

#endif /* wavedealer_h */
