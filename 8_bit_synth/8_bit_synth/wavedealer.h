//
//  wavedealer.h
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/20.
//  Copyright © 2018年 范熙来. All rights reserved.
//

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
/*********************************/

uchar riff[4] = { "RIFF"};
uchar size_total[4];
uchar wave[4] = { "WAVE" };
uchar fmt[4] = { "fmt " };
uchar fmt_size[4];
uchar fmt_pcm[2] = { 0x01,0x00 }; // pcm œﬂ–‘±‡¬Î
uchar fmt_way[2];
//={0x01,0x00}; or ={0x02,0x00}; µ•À´…˘µ¿
uchar fmt_samplehz[4];
uchar fmt_bytepsec[4];
uchar fmt_bytepsample[2];
uchar fmt_bitpsample[2];
uchar fmt_nouse[2]; //œµÕ≥‘§¡Ù¡Ω◊÷£¨8 Œª≤…—˘ ±‘§¡Ù
uchar data[5] = { "data" };
uchar data_size[4];
uchar *mp;
//wav Œƒº˛ µº  ˝æ›
uint d_totalsize; //Œƒº˛◊‹¥Û–°
uint d_fmtsize; //fmt øÈ¥Û–°
uint d_way; //…˘µ¿ ˝
uint d_samplehz; //»°—˘∆µ¬
uint d_bytepsec; // ˝æ›¡˜¡ø£®kb/s£©
uint d_bytepsample; //»°—˘¥Û–°
uint d_bitpsample; //»°—˘Œª ˝
uint d_datasize; //wav  ˝æ›øÈ¥Û–°
//¥¥Ω®sin ≤®–Œ≤Œ ˝
uint timelen;
//uint sin_hz;
//uint sin_db;
//∆‰À˚»´æ÷±‰¡ø
uchar namei[15]; //µº»ÎŒƒº˛√˚
uchar nameo[15]; //µº≥ˆŒƒº˛√˚
FILE *fp; //∂¡»°”√Œƒº˛÷∏’Î
FILE *fq; //–¥»Î”√Œƒº˛÷∏’Î

int cal(char * exp);


#endif /* wavedealer_h */
