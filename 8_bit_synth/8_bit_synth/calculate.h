//
//  calculate.h
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/8.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#ifndef calculate_h
#define calculate_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

enum usu
{
    STACK_FULL = -10,
    STACK_OK,
    STACK_EMPTY,
    SUCCESS,
    PUSH_SUCCESS
};

int calculate(int num1,int num2,char c);
int cal(char * exp);
int priority(char c);
void initialize_stack(int *stack,int *top);
void initialize_stack2(char *stack,int *top);
int is_stack_full(int *top);
int is_stack_empty(int *top);
int push_stack(int *stack,int *num,int *top);
int push_stack2(char *stack,char *c,int *top);
int pop_stack(int *stack,int *top);
char pop_stack2(char *stack,int *top);
int compare_priority(char *str,char *stack2,int *top2,int *stack1,int *top1);

#endif /* calculate_h */
