//
//  substitude.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/8.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#include "substitude.h"

void * memorycpy(void * dest, const void *src, size_t count) {
/* Function:  memorycpy()
Description: copy src to dest in memory, return the dest address
Input: count: the number of the string that is going to be copied. */
    char *tmp = (char *) dest, *s = (char *) src;
    while (count--)
        *tmp++ = *s++;
    return dest;
}

int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr) {
/* Function: str_replace()
Description: substitude every p_seach in p_source into p_repstr and save to result to p_result */
    int c = 0; // counter to count how many strings has been substituted
    size_t repstr_leng = 0;
    size_t searchstr_leng = 0;
    char *p1;
    char *presult = p_result;
    char *psource = p_source;
    char *prep = p_repstr;
    char *pseach = p_seach;
    long nLen = 0;
    repstr_leng = (int)strlen(prep);
    searchstr_leng = (int)strlen(pseach);
    do {
        p1 = strstr(psource, p_seach);
        if (p1 == NULL) {
            strcpy(presult, psource);
            return c;
        } // return the source string if there is no p_seach in the source string
        c++;
        nLen = p1 - psource;
        memorycpy(presult, psource, nLen); /* copy the string between the previous
         spliting point and the preset one */
        memorycpy(presult + nLen, p_repstr, repstr_leng); /* copy the string that
         need substituting */
        psource = p1 + searchstr_leng;
        presult = presult + nLen + repstr_leng;
    } while (p1);
    return c;
}


int getnum(unsigned long int num, int n){
/* Description: get num's value at n'th digit*/
    int f=0,g=0;
    f = pow(10, n);
    g = pow(10, n-1);
    if (num/g == 0) {
        return -1;
    } else {
        return (num % f - num % g) / pow(10, n-1);
    }
}

int get(unsigned long int num) {
/* Description: see how many digits has num got */
    int i = 1, g = pow(10, i);
    while (num/g != 0) {
        i++;
        g = pow(10, i);
    }
    return i;
}

char* num2chars(unsigned long int t) {
/* Description: turn t(int) into char(char *)*/
    int l = get(t);
    char * ch = (char *)malloc(l+5);
    char * des = ch;
    for (; l > 0; l--) {
        *ch = (char)getnum(t, l) + (int)'0';
        ch++;
    }
    *ch = '\0';
    return des;
}
