

#include "wavedealer.h"


void data2array(uint x, uchar a[], uchar n)
// turn data(uint) into array that can be played in .wav
{
    uchar i;
    for (i = 0; i<n; i++)
    {
        a[i] = x & 0xff;
        x = x >> 8;
    }
}
uint array2data(uchar a[], uchar n)
// turn data(uint) into array that can be played in .wav
{
    uchar i;
    uint x = 0;
    for (i = 0; i<n; i++)
    {
        x = x * 256 + a[n - 1 - i];
    }
    return x;
}


void convert_array2data()
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


uchar writetofile(uchar nameout[])
// write data(mp) to .wav file
{
    if ((fq = fopen(nameout, "wb")) == 0)
    {
        printf("create error\n");
        return 0;
    }
    if (fwrite(riff, 1, 4, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    else if (riff[0] != 'r'&&riff[0] != 'R')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(size_total, 1, 4, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(wave, 1, 4, fq) == 0)
    {
        printf("write erro\n");
        return 0;
    }
    else if (wave[0] != 'w'&&wave[0] != 'W')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(fmt, 1, 4, fq) == 0)
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_size, 1, 4, fq) == 0)
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_pcm, 1, 2, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_way, 1, 2, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_samplehz, 1, 4, fq) == 0)
    {
        printf("write erro\n");
        return 0;
    }
    if (fwrite(fmt_bytepsec, 1, 4, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_bytepsample, 1, 2, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(fmt_bitpsample, 1, 2, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(data, 1, 4, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    else if (data[0] != 'd'&&wave[0] != 'D')
    {
        printf("the file is illegal!\n");
        return 0;
    }
    if (fwrite(data_size, 1, 4, fq) == 0)
    {
        printf("write error\n");
        return 0;
    }
    if (fwrite(mp, 1, array2data(data_size, 4), fq) == 0) // important!!! write the data to the .wav file

    {
        printf("write error\n");
        return 0;
    } // These codes write the data into file step by step
    fclose(fq);
    return 1;
}
int createwave(int timelen, char * exp, int freq) // create the .wav file
{
    long int t;
    double n;
    d_way = 1;
    long int flag;
    char sub[100] = {'0'};
    d_samplehz = 44100;
    d_bitpsample = 8;
    d_bytepsample = d_bitpsample/8;
    d_bytepsec = d_bytepsample*d_samplehz;
    d_datasize = d_bytepsec * timelen;
    d_fmtsize = 16;
    d_totalsize = timelen * d_bytepsec + 36; /* set the values of several parameters
     that will be written in .wav file head */
    data2array(d_way, fmt_way, 2);
    data2array(d_samplehz, fmt_samplehz, 4);
    data2array(d_bitpsample, fmt_bitpsample, 2);
    data2array(d_bytepsample, fmt_bytepsample, 2);
    data2array(d_bytepsec, fmt_bytepsec, 4);
    data2array(d_datasize, data_size, 4);
    data2array(d_fmtsize, fmt_size, 4);
    data2array(d_totalsize, size_total, 4); /*  turn these values into array that
     can be written directly in wave file */
    mp = (uchar *)malloc(d_datasize);
    for (t = 1; t < d_datasize; t++)
    {
        flag = str_replace(sub, exp, "t", num2chars(t));
        if (flag == 0) {
            printf("\nThere is no t in the exp!\n\n"); // error description
            sleep(2);
            return 0;
        }
        flag = cal(sub);
        if (flag == -1) {
            printf("Please enter valid expression\n"); // error description
            sleep(2);
            return 0;
        }
        mp[t-1] = ((flag * d_samplehz * 163) / (256 * freq * 100)) % 256; /* sub
        stitude "t" in exp and calculate the modulated exp and assign the result
         to mp[t-1] (the number 163, ... was set to adjust the freq of the sound.
          And by default, it is adjusted to 440Hz) */
    }
    return 1;
}

void generate(char * output_name, int timelen, char * exp, int freq) {
    int flag;
    flag = createwave(timelen, exp, freq); // calculate and store the data
    if (flag == 1) {
      writetofile(output_name); // write the data to the file
      system("afplay sound.wav"); /* play the .wav file: because we have not
      find a way to play the sound in c that works on all the plotform, so
      we just call a terminal program here. */
    }
}
