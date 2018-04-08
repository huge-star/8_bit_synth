//
//  main.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/3/23.
//  Copyright © 2018年 范熙来. All rights reserved.
//



//#include <stdio.h>
//#include <stdlib.h>
//
//struct sheet {
//    char * ch[4];
//};
//
//struct sheet * getinput() {
//    char * exp;
//    scanf("%s", &exp);
//    return join_numbers(separate_all(remove_space(exp)));
//}
//
//int main() {
//    printui();
//    getinput();
//    return 0;
//}

#include "main.h"


#define MAX_SIZE 100

enum usu
{
    STACK_FULL = -10,
    STACK_OK,
    STACK_EMPTY,
    SUCCESS,
    PUSH_SUCCESS
};

int calculate(int num1,int num2,char c)
{
    switch(c)
    {
        case '+':
        {
            return num1 + num2;
        }
        case '-':
        {
            return num1 - num2;
        }
        case '*':
        {
            return num1 * num2;
        }
        case '/':
        {
            return num1 / num2;
        }
            
    }
    return -1;
}

int priority(char c)//计算运算符的优先级
{
    switch(c)
    {
        case '+':
        case '-':
        {
            return 1;
            break;
        }
        case '*':
        case '/':
        {
            return 2;
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
    int num,num1,total;
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
    char *ptr = str;
    
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

//void insert_char(char ch, char * exp) {
//    int l = (int)strlen(exp);
//
//    for (; l>=0; l--) {
//        *(exp + l + 1) = *(exp + l);
//    }
//    *exp = ch;
//}
//
//void insert_string(char * ch, char * exp){
//    int l = (int)strlen(ch);
//    for (; l>0; l--) {
//        insert_char(ch[l-1], exp);
//    }
//}
//
//void del(char * exp) {
//    while (*(exp + 1)) {
//        *(exp + 1) = *(exp + 2);
//        exp++;
//    }
//}
//
//
//char * del(char * des, int index) {
//    char * ch = (char *)malloc(100);
//    int i;
//    for (i = 0; i < index; i++) {
//        *(ch + i) = *(des + i);
//    }
//    i++;
//    while (*(des+i+1)) {
//        *(ch + i) = *(des + i + 1);
//        i++;
//    }
//    return ch;
//}
//
//
//char * subs(char * exp, unsigned long int t) {
//    char * des = exp;
//    while (*exp != '\0') {
//        if (*exp == 't') {
//            des = del(des, exp - des);
////            des = insert_string(del(des, (exp - des)), num2chars(t), (exp - des));
//        }
//        exp++;
//    }
//    return exp;
//}
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
    int repstr_leng = 0;
    int searchstr_leng = 0;
    char *p1;
    char *presult = p_result;
    char *psource = p_source;
    char *prep = p_repstr;
    char *pseach = p_seach;
    int nLen = 0;
    repstr_leng = strlen(prep);
    searchstr_leng = strlen(pseach);
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
    char *p, *ptm, *pr;
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



int main()
{
    unsigned long int t;
    char * sub;
    for (t = 1; t < 441000; t++) {
        sub = subs("3+t-(5+6)*8", "t", num2chars(t));
        printf("%d\n", cal(sub) % 256);
        free(sub);
    }
    return 0;
}
