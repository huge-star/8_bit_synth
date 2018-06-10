#include "calculate.h"
#define MAX_SIZE 100


long int calculate(long int num1,long int num2,char c)
{
/* Description: for given two numbers and a operator, return "num1 c num2". for example (1, 2, +) => "1 + 2" => "3" => return 3 */
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

long int priority(char c)
/* Description: calculate the priority of the operator */
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

void initialize_stack(long int *stack,long int *top)
/* Description: initialize the ordered stack */
{
    long int i;
    for(i = 0;i < MAX_SIZE;i ++)
    {
        stack[i] = 0;
    }
    *top = -1;
}
void initialize_stack2(char *stack,long int *top)
/* Description: initialize the stack used to store operator */
{
    long int i;
    for(i = 0;i < MAX_SIZE;i ++)
    {
        stack[i] = 0;
    }
    *top = -1;
}

long int is_stack_full(long int *top)
/* Description: check whether the stack is full */
{
    if(*top == MAX_SIZE - 1)
    {
        return STACK_FULL;
    }
    return STACK_OK;
}

long int is_stack_empty(long int *top)
/* Description: check whether the stack is empty */
{
    if(*top == -1)
    {
        return STACK_EMPTY;
    }
    return STACK_OK;
}


long int push_stack(long int *stack,long int *num,long int *top)
/* Description: Push "num"(long int) into the "stack" */
{
    if(is_stack_full(top) == STACK_FULL)
    {
        return STACK_FULL;
    }
    (*top) ++;
    stack[*top] = *num;
    return PUSH_SUCCESS;
}

long int push_stack2(char *stack,char *c,long int *top)
/* Description: Push "c"(char *) into the "stack" */
{
    if(is_stack_full(top) == STACK_FULL)
    {
        return STACK_FULL;
    }
    (*top) ++;
    stack[*top] = *c;
    return PUSH_SUCCESS;
}

long int pop_stack(long int *stack,long int *top)
/* Description: Pop the top element(long int) out of "stack" */
{
    long int num;
    if(is_stack_empty(top) == STACK_EMPTY)
    {
        return STACK_EMPTY;
    }
    num = stack[*top];
    (*top) --;
    return num;
}
char pop_stack2(char *stack,long int *top)
/* Description: Pop the top element(char) out of "stack" */
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

long int compare_priority(char *str,char *stack2,long int *top2,long int *stack1,long int *top1)
/* Description: compare the priority of the operators and push and pop element from the stack */
{
    long int num,num1,total;
    char c;
    if(*str == '\0')
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
        c = pop_stack2(stack2,top2); // pop a operator from the top of stack2(stack that store the operators)
        while(c != '(')
        {
            num = pop_stack(stack1,top1); // pop a number from the top of stack1(stack that store the numbers)
            num1 = pop_stack(stack1,top1); // pop another number from the top of stack1
            total = calculate(num1,num,c);// assign the calculation result to total
            push_stack(stack1,&total,top1);// push "total" into stack1
            c = pop_stack2(stack2,top2);
        }
    }
    else if(*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '%' ||
            *str == '&' || *str == '|' || *str == '^' || *str == '<' || *str == '>' ||
            *str == '(' || *str == ')')
    {
        c = pop_stack2(stack2,top2); // pop a operator from the stack2(operator stack)
        if(c == '(') // push the operator into the stack2 (operator stack) when the character is '('
        {
            push_stack2(stack2,&c,top2);
            push_stack2(stack2,str,top2);
            return SUCCESS;
        }
        num = priority(c);
        num1 = priority(*str);
        if(num1 >= num) // push the operator into the stack2 (operator stack) when the priority of the character is high than that of the top element
        {
            push_stack2(stack2,&c,top2);
            push_stack2(stack2,str,top2);
        }
        else
        {
            num = pop_stack(stack1,top1);
            num1 = pop_stack(stack1,top1);
            total = calculate(num1,num,c);
            push_stack(stack1,&total,top1);
            compare_priority(str,stack2,top2,stack1,top1);
            // pick 2 numbers from the top of stack1 and 1 operator from the top of stack2 and calculate and save the result to the number stack.
            // and then continue to compare recursively
        }
    }
    else
    {
        printf("Please enter supported operator ('+', '-', '*', '/', '&', '|', '^', '<', '>', '%%')\n");
        return FAIL;
    }
    return SUCCESS;
}

long int cal(char * exp) {
/* Description: calculate given exp(char *)*/
    long int num,num1 = -1;
    long int total = -1;
    char c;
    char *dest = (char *)malloc(sizeof(100));
    char *temp = dest; // to record the address of the memory being allocated

    long int stack1[MAX_SIZE]; // num stack
    long int top1;

    char stack2[MAX_SIZE]; // operator stack
    long int top2;

    initialize_stack(stack1, &top1);
    initialize_stack2(stack2, &top2); // initialize these stacks

    while(*exp != '\0')
    {
        if(*exp >= '0'&& *exp <= '9') // put numbers into stack1 (number stack)
        {
            while(*exp >= '0'&& *exp <= '9')
            {
                *temp = *exp;
                exp ++;
                temp ++;
            }
            *temp = '\0'; // add '\0' to the number string
            temp = dest;

            num = atoi(dest); // turn string to int for example: "328" => 328 (int)
            push_stack(stack1, &num, &top1);
        }

        if (compare_priority(exp, stack2, &top2, stack1, &top1) == FAIL)
        {
            return -1;
        }

        if(*exp == '\0') // if touch the end of the string, break
        {
            break;
        }
        exp ++;
    }


    while(top2 != -1)
    {
        if (top1 == -1) {
          return -1;
        }
        num = pop_stack(stack1, &top1);
        num1 = pop_stack(stack1, &top1);
        c = pop_stack2(stack2, &top2);
        total = calculate(num1, num, c);
        push_stack(stack1, &total, &top1); // pick 2 numbers from the top of stack1 and 1 operator from the top of stack2 and calculate and save the result to the number stack until the operator stack is NULL
    }
    return total;
}
