//
//  main.h
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/8.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


char * my_strstr(char * ps, char *pd);
void * memorycpy(void * dest, const void *src, size_t count);
int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr);
char * subs(char * a, char * b, char * c);
int getnum(unsigned long int num, int n);
int get(unsigned long int num);
char* num2chars(unsigned long int t);
int generate(char * output_name, int timelen, char * exp, int freq);

#endif /* main_h */
