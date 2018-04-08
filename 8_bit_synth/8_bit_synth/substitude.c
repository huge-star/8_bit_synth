//
//  substitude.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/8.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#include "substitude.h"
//字符串替换函数
/********************************************************************
 *  Function：  my_strstr()
 *  Description: 在一个字符串中查找一个子串;
 *  Input：      ps: 源;      pd：子串
 *  Return :    0：源字符串中没有子串; 1：源字符串中有子串;
 *********************************************************************/
char * my_strstr(char * ps, char *pd) {
    char *pt = pd;
    int c = 0;
    while (*ps != '\0') {
        if (*ps == *pd) {
            while (*ps == *pd && *pd != '\0') {
                ps++;
                pd++;
                c++;
            }
        } else {
            ps++;
        }
        if (*pd == '\0') {
            return (ps - c);
        }
        c = 0;
        pd = pt;
    }
    return 0;
}

/********************************************************************
 *  Function：  memorycpy()
 *  Description: 复制一个内存区域到另一个区域;
 *  Input：      src: 源;
 count: 复制字节数.
 *  Output：      dest: 复制目的地;
 *  Return :      dest;
 *********************************************************************/
void * memorycpy(void * dest, const void *src, size_t count) {
    char *tmp = (char *) dest, *s = (char *) src;
    while (count--)
        *tmp++ = *s++;
    return dest;
}

/********************************************************************
 *  Function：  str_replace()
 *  Description: 在一个字符串中查找一个子串，并且把所有符合的子串用
 另一个替换字符串替换。
 *  Input：      p_source:要查找的母字符串； p_seach要查找的子字符串;
 p_repstr：替换的字符串;
 *  Output：      p_result:存放结果;
 *  Return :      返回替换成功的子串数量;
 *  Others:      p_result要足够大的空间存放结果，所以输入参数都要以\0结束;
 *********************************************************************/
int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr) {
    int c = 0;
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
        p1 = my_strstr(psource, p_seach);
        if (p1 == 0) {
            strcpy(presult, psource);
            return c;
        }
        c++;  //匹配子串计数加1;
        // 拷贝上一个替换点和下一个替换点中间的字符串
        nLen = p1 - psource;
        memorycpy(presult, psource, nLen);
        // 拷贝需要替换的字符串
        memorycpy(presult + nLen, p_repstr, repstr_leng);
        psource = p1 + searchstr_leng;
        presult = presult + nLen + repstr_leng;
    } while (p1);
    return c;
}

char * subs(char * a, char * b, char * c) {
    char * result_a = (char *)malloc(200);        //存放替换结果;
    char *ptm, *pr;
    char * s, * s1, * s2;
    s = a;
    s1 = b;
    s2 = c;
    ptm = s;
    pr = result_a;
    str_replace(pr, ptm, s1, s2);
    return result_a;
}

int getnum(unsigned long int num, int n){
    int f=0,g=0;
    f = pow(10, n);
    g = pow(10, n-1); /*为啥f，g不能放到里面啊？*/
    if (num/g == 0) {
        return -1;
    } else {
        return (num % f - num % g) / pow(10, n-1);
    }
}

int get(unsigned long int num) {
    int i = 0, g = pow(10, i+1);
    while (num/g != 0) {
        g = pow(10, i+1);
        i++;
    }
    return i;
}

char* num2chars(unsigned long int t) {
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
