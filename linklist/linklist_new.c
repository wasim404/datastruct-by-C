#include"node.h"
#include<stdio.h>
#include<stdlib.h>

//定义链表结构体（可选）
typedef struct linklist
{
    listnode* head; //定义头指针，指向第一个结点
    int size; //当前链表节点数
}linklist;