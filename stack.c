#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "stack.h"

void initstack(Stack* stack);
bool stackempty(Stack* stack);
bool stackfull(Stack* stack);
bool push(Stack* stack,int value);
bool pop(Stack* stack,int* value);

void initstack(Stack* stack)
{
    stack->top = -1;
    return;
}

bool stackempty(Stack* stack)
{
    return stack->top == -1;
}

bool stackfull(Stack* stack)
{
    return stack->top == MAX_SIZE-1;
}

bool push(Stack* stack,int value)
{
    if(stackfull(stack))
    {
        printf("stack is overflow!\n");
        return false;
    }
    stack->data[++stack->top] = value;
    return true;
}

bool pop(Stack* stack,int* value)
{
    if(stackempty(stack))
    {
        printf("stack is empty!\n");
        return false;
    }
    *value = stack->data[stack->top--];
    return true;
}