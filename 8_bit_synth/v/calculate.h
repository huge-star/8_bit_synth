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
    PUSH_SUCCESS,
    FAIL
};

long int calculate(long int num1,long int num2,char c);
long int cal(char * exp);
long int priority(char c);
void initialize_stack(long int *stack,long int *top);
void initialize_stack2(char *stack,long int *top);
long int is_stack_full(long int *top);
long int is_stack_empty(long int *top);
long int push_stack(long int *stack,long int *num,long int *top);
long int push_stack2(char *stack,char *c,long int *top);
long int pop_stack(long int *stack,long int *top);
char pop_stack2(char *stack,long int *top);
long int compare_priority(char *str,char *stack2,long int *top2,long int *stack1,long int *top1);

#endif /* calculate_h */
