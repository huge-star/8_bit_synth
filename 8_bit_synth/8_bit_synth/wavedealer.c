//
//  wavedealer.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/20.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#include "wavedealer.h"


/*************************************/
/*============ ˝æ›◊™ªª◊”∫Ø ˝=============*/
void data2array(uint x, uchar a[], uchar n)           //∞— ˝æ›◊™ªª≥…◊÷∑˚–Œ Ω
//Ω´ µº  ˝æ›◊™ªØŒ™ƒ⁄¥Ê¥¢¥Ê–Œ Ω
{
    uchar i;
    for (i = 0; i<n; i++)
    {
        a[i] = x & 0xff;
        x = x >> 8;
    }
}
uint array2data(uchar a[], uchar n)
//Ω´ ˝◊Èƒ⁄–≈œ¢ªπ‘≠Œ™ µº  ˝æ›
{
    uchar i;
    uint x = 0;
    for (i = 0; i<n; i++)
    {
        x = x * 256 + a[n - 1 - i];
    }
    return x;
}
/*============∂¡»°π¶ƒ‹∫Ø ˝=============*/

void convert_array2data()
//◊™ªªÀ˘∂¡»°Œƒº˛ ˝æ›  ∞—Œﬁ∑˚∫≈’˚–Õ◊™ªª≥…Œﬁ∑˚∫≈◊÷∑˚
{
    d_totalsize = array2data(size_total, 4);
    d_fmtsize = array2data(fmt_size, 4);
    d_way = array2data(fmt_way, 2);
    d_samplehz = array2data(fmt_samplehz, 4);
    d_bytepsec = array2data(fmt_bytepsec, 4);
    d_bytepsample = array2data(fmt_bytepsample, 2);
    d_bitpsample = array2data(fmt_bitpsample, 2);
    d_datasize = array2data(data_size, 4);
}
/*============¥¥Ω®Œƒº˛∫Ø ˝=============*/
uchar writetofile(uchar nameout[])
//–¥»Î ˝æ›µΩ–¬Œƒº˛
{
    if ((fq = fopen(nameout, "wb")) == 0)
    {
        printf("create error\n");
        return 0;
    }
    if (fwrite(riff, 1, 4, fq) == 0) //–¥»Îriff
    {
        printf("write error\n");
        return 0;
    }
    else if (riff[0] != 'r'&&riff[0] != 'R')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(size_total, 1, 4, fq) == 0) //–¥»Î◊‹¥Û–°
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(wave, 1, 4, fq) == 0) //–¥»Îwave
    {
        printf("write erro\n");
        return 0;
    }
    else if (wave[0] != 'w'&&wave[0] != 'W')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(fmt, 1, 4, fq) == 0) //–¥»Îfmt
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_size, 1, 4, fq) == 0) //–¥»Îwave
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_pcm, 1, 2, fq) == 0) //–¥»Îpcm
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_way, 1, 2, fq) == 0) //–¥»Î…˘µ¿ ˝
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_samplehz, 1, 4, fq) == 0) //–¥»Î≤…—˘∆µ¬
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_bytepsec, 1, 4, fq) == 0) //–¥»Î ˝æ›¡˜¡ø
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_bytepsample, 1, 2, fq) == 0) //–¥»Î≤…—˘¥Û–°
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_bitpsample, 1, 2, fq) == 0) //–¥»Î≤…—˘Œª ˝
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(data, 1, 4, fq) == 0) //–¥»Îdata
    {
        printf("write error\n");
        return 0;
    }
    else if (data[0] != 'd'&&wave[0] != 'D')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(data_size, 1, 4, fq) == 0) //–¥»Îdatasize
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(mp, 1, array2data(data_size, 4), fq) == 0) //–¥»Îmusic
        
    {
        printf("write error\n");
        return 0;
    }
    fclose(fq);
    return 1;
}
void createwave(int timelen, char * exp, int freq) //¥¥Ω®≤®–Œ∫Ø ˝
{
    long int t;
    double n;
    d_way = 1;
    d_samplehz = 44100;
    d_bitpsample = 8;
    d_bytepsample = d_bitpsample/8;
    d_bytepsec = d_bytepsample*d_samplehz;
    d_datasize = d_bytepsec * timelen;
    d_fmtsize = 16;
    d_totalsize = timelen * d_bytepsec + 36;
    data2array(d_way, fmt_way, 2);
    data2array(d_samplehz, fmt_samplehz, 4);
    data2array(d_bitpsample, fmt_bitpsample, 2);
    data2array(d_bytepsample, fmt_bytepsample, 2);
    data2array(d_bytepsec, fmt_bytepsec, 4);
    data2array(d_datasize, data_size, 4);
    data2array(d_fmtsize, fmt_size, 4);
    data2array(d_totalsize, size_total, 4);
    mp = (uchar *)malloc(d_datasize);
    for (t = 1; t<d_datasize; t++)
    {
        mp[t-1] = (((cal(subs(exp, "t", num2chars(t)))) * d_samplehz) / (256 * freq)) % 256;
    }
    system("clear");
}

void generate(char * output_name, int timelen, char * exp, int freq) {
    createwave(timelen, exp, freq);
    printf("the file you create has been ready!\n");
    printf(" \ninput the name of the output file:");
    writetofile(output_name);
    printf("\n\nmission complete!\n\n");
    system("clear");
}


