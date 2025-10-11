#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "stack.h"

void decimaltobase(int decimal,int base);

int main()
{
    int decimal,base;
    printf("请输入一个十进制整数\n");
    scanf("%d",&decimal);
    printf("请输入要转换的进制(2-16):");
    scanf("%d",&base);
    decimaltobase(decimal,base);
    return 0;
}

void decimaltobase(int decimal,int base)
{
    int original = decimal;
    bool isNegitive = false;
    if(decimal<0)
    {
        isNegitive = true;
    }
    if(isNegitive)
    {
        decimal = -decimal;
    }
    if(decimal == 0)
    {
        printf("0(十进制)->0(%d进制)",base);
        return;
    }
    if(base<2 || base>16)
    {
        printf("超出范围\n");
        return;
    }
    Stack stack;
    initstack(&stack);
    while(decimal>0) //循环直到商为0
    {
        int result;
        result = decimal%base;
        push(&stack,result);
        decimal /= base;
    }
    printf("%d(十进制) ===> ",original);
    if(isNegitive)
    {
        printf("-");
    }
    while(!stackempty(&stack))
    {
        int value; 
        pop(&stack,&value);
        if(value<10)
        {
            printf("%d",value);
        }
        else
        {
            printf("%c",'A'+(value-10));
        }
    }
    printf("(%d进制)\n",base);
}

