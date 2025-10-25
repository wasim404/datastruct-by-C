#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100
typedef struct Stack
{
    int data[MAX_SIZE];
    int top;
}Stack;
void initstack(Stack* stack);
bool stackempty(Stack* stack);
bool stackfull(Stack* stack);
bool push(Stack* stack,int value);
bool pop(Stack* stack,int* value);

#endif