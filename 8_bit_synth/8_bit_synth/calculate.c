//
//  calculate.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/4/8.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#include "calculate.h"
#define MAX_SIZE 100


int calculate(int num1,int num2,char c)
{
    switch(c)
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '%':
            return num1 % num2;
        case '&':
            return num1 & num2;
        case '|':
            return num1 | num2;
        case '^':
            return num1 ^ num2;
        case '<':
            return num1 << num2;
        case '>':
            return num1 >> num2;
        
            
    }
    return -1;
}

int priority(char c)//计算运算符的优先级
{
    switch(c)
    {
        case '+':
        case '-': {
            return 7;
            break;
        }
        case '*':
        case '/': {
            return 8;
            break;
        }
        case '%': {
            return 9;
            break;
        }
        case '|': {
            return 2;
            break;
        }
        case '^': {
            return 3;
            break;
        }
        case '&': {
            return 4;
            break;
        }
        case '<':
        case '>': {
            return 5;
            break;
        }
        default:
        {
            return 0;
        }
    }
    return 0;
}

void initialize_stack(int *stack,int *top)//初始化顺序栈
{
    int i;
    for(i = 0;i < MAX_SIZE;i ++)
    {
        stack[i] = 0;
    }
    *top = -1;
}
void initialize_stack2(char *stack,int *top)
{
    int i;
    for(i = 0;i < MAX_SIZE;i ++)
    {
        stack[i] = 0;
    }
    *top = -1;
}

int is_stack_full(int *top)//检查栈是不是满
{
    if(*top == MAX_SIZE - 1)
    {
        return STACK_FULL;
    }
    return STACK_OK;
}

int is_stack_empty(int *top)//检查栈是不是空
{
    if(*top == -1)
    {
        return STACK_EMPTY;
    }
    return STACK_OK;
}


int push_stack(int *stack,int *num,int *top)//入栈
{
    if(is_stack_full(top) == STACK_FULL)
    {
        return STACK_FULL;
    }
    (*top) ++;
    stack[*top] = *num;
    return PUSH_SUCCESS;
}

int push_stack2(char *stack,char *c,int *top)
{
    if(is_stack_full(top) == STACK_FULL)
    {
        return STACK_FULL;
    }
    (*top) ++;
    stack[*top] = *c;
    return PUSH_SUCCESS;
}

int pop_stack(int *stack,int *top)//出栈
{
    int num;
    if(is_stack_empty(top) == STACK_EMPTY)
    {
        return STACK_EMPTY;
    }
    num = stack[*top];
    (*top) --;
    return num;
}
char pop_stack2(char *stack,int *top)
{
    char c;
    if(is_stack_empty(top) == STACK_EMPTY)
    {
        return STACK_EMPTY;
    }
    c = stack[*top];
    (*top) --;
    return c;
}
#if 0
比较解析的运算符+-*/（）与栈顶运算符的优先级,按照规则进行各种出入栈运算
#endif
int compare_priority(char *str,char *stack2,int *top2,int *stack1,int *top1)
{
    int num,num1,total;
    char c;
    if(*str == '\0')//文件尾时，正常退出
    {
        return SUCCESS;
    }
    if(is_stack_full(top2) == STACK_FULL)
    {
        return STACK_FULL;
    }
    else if(is_stack_empty(top2) == STACK_EMPTY||*str == '(')
    {
        
        push_stack2(stack2,str,top2);
    }
    else if(*str == ')')
    {
        c = pop_stack2(stack2,top2);//从栈顶取出一运算符
        while(c != '(')
        {
            num = pop_stack(stack1,top1);//取出一操作数
            num1 = pop_stack(stack1,top1);
            total = calculate(num1,num,c);//保存运算结果
            push_stack(stack1,&total,top1);//将运算结果入栈
            c = pop_stack2(stack2,top2);
        }//出while循环即'('运算符已取出
    }
    else//解析出的运算符为+-*/时执行以下操作
    {
        c = pop_stack2(stack2,top2);
        if(c == '(')//运算符栈顶元素为'('时，解析出的运算符要入栈
        {
            push_stack2(stack2,&c,top2);
            push_stack2(stack2,str,top2);
            return SUCCESS;
        }
        num = priority(c);
        num1 = priority(*str);
        if(num1 > num)//解析出的运算符优先级大于栈顶元素优先级时，解析出的运算符要入栈
        {
            push_stack2(stack2,&c,top2);
            push_stack2(stack2,str,top2);
        }
        else
        {
            //取出栈顶运算符和操作数栈栈顶的连续两个操作数进行运算，
            //并将结果存入操作数栈，然后继续比较该运算符与栈顶运算符的优先级。
            num = pop_stack(stack1,top1);
            num1 = pop_stack(stack1,top1);
            total = calculate(num1,num,c);
            push_stack(stack1,&total,top1);
            compare_priority(str,stack2,top2,stack1,top1);
        }
    }
    return SUCCESS;
}

int cal(char * exp) {
    int num,num1,total = -1;
    char c;
    char *dest = (char *)malloc(sizeof(100));
    char *temp = dest;                        //记录分配空间的首地址
    char *str = (char *)malloc(sizeof(100));//保存需要计算的表达式字符串。
    
    int stack1[MAX_SIZE];                    //操作数栈
    int top1;
    initialize_stack(stack1,&top1);            //初始化栈
    
    char stack2[MAX_SIZE];                    //运算符栈
    int top2;
    initialize_stack2(stack2,&top2);
    
    str = exp;
    
    while(*str != '\0')
    {
        if(*str >= '0'&&*str <= '9')//解析连续的数字字符为整数，并入操作数栈
        {
            while(*str >= '0'&&*str <= '9')
            {
                *temp = *str;
                str ++;
                temp ++;
            }//while循环结束，str指向运算符或指向字符串末尾
            *temp = '\0';
            temp = dest;
            
            num = atoi(dest);//字符串转整型
            push_stack(stack1,&num,&top1);
        }
        
        //比较解析的运算符+-*/（）与栈顶运算符的优先级,按照规则进行各种出入栈运算
        compare_priority(str,stack2,&top2,stack1,&top1);
        
        if(*str == '\0')
        {
            break;
        }
        str ++;
    }
    
    /*依次取出操作数栈顶两元素与运算符栈顶一元素进行计算，结果保存在操作数栈，直至运算符栈为空
     */
    while(top2 != -1)
    {
        num = pop_stack(stack1,&top1);
        num1 = pop_stack(stack1,&top1);
        c = pop_stack2(stack2,&top2);
        total = calculate(num1,num,c);
        push_stack(stack1,&total,&top1);
    }
    return total;
}
