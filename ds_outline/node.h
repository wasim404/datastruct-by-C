#include<stdio.h>
#include<stdlib.h>

//自定义数据结构
typedef struct Elemtype
{
    int data;
    char num[10];
}Elemtype;

//节点的定义
typedef struct Node
{
    Elemtype value; //数据域：使用自定义数据结构
    struct Node* next; //指针域：指向下一个指针
    struct Node* prev; //指针域：（可选）部分数据结构需要使用到，用于指向前一个节点
}Node;

//创建节点的函数
Node* createNode(Elemtype value);