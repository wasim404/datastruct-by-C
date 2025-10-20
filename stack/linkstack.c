#include<stdio.h>
#include<stdlib.h>

typedef struct stacknode
{
    int data;
    struct stacknode* next;
}stacknode;

typedef struct linkstack
{
    stacknode* head;
    int size;
}linkstack;

linkstack* initlinkstack();
stacknode* createstacknode(int value);
int push(linkstack* stack,int value);
int pop(linkstack* stack,int* value);

int main()
{
    return 0;
}

//初始化栈
linkstack* initlinkstack()
{
    linkstack* stack = (linkstack*)malloc(sizeof(linkstack));
    if(!stack)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

//创建新的节点
stacknode* createstacknode(int value)
{
    stacknode* newnode = (stacknode*)malloc(sizeof(stacknode));
    if(!newnode)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

//入栈
int push(linkstack* stack,int value)
{
    if (stack == NULL) {
        printf("错误：栈未初始化或为空指针！\n");
        return -1;
    }
    stacknode* newnode = createstacknode(value);
    newnode->next = stack->head;
    stack->head = newnode;
    stack->size++;
    return 0;
}

//出栈
int pop(linkstack* stack, int* value)
{
    if (stack == NULL || value == NULL || stack->head == NULL) {
        return -1;
    }
    stacknode* temp = stack->head;
    *value = temp->data;
    stack->head = temp->next;
    stack->size--;
    free(temp);
    return 0;
}