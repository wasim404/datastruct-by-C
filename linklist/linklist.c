#include"node.h"
#include<stdio.h>
#include<stdlib.h>
//gcc main.c other.c -I 目录路径 -o 输出文件名

//定义链表结构体
typedef struct linklist
{
    Node* head; //定义头指针，指向第一个结点
    int size; //当前链表节点数
}linklist;

linklist* createList();
int insertAtHead(linklist* list,Elemtype value);
int insertAtTail(linklist* list,Elemtype value);


int main()
{
    linklist* myList = createList();
    Elemtype e1 = {10, "A001"};
    Elemtype e2 = {20, "B002"};
    Elemtype e3 = {30, "C003"};
    // 头插法插入
    printf("头插法插入 e1, e2:\n");
    insertAtHead(myList, e1);
    insertAtHead(myList, e2);
    // 尾插法插入
    printf("\n尾插法插入 e3:\n");
    insertAtTail(myList, e3);
    free(myList);
    return 0;
}

linklist* createList()
{
    linklist* List = (linklist*)malloc(sizeof(linklist)); //动态分配内存用于创建链表
    if(!List)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    List->head = NULL; //初始化头节点为NULL
    List->size = 0; //初始时，链表节点数为0
    return List;
}

int insertAtHead(linklist* list,Elemtype value)
{
    Node* newnode = createNode(value);
    newnode->next =list->head; //将新节点指向链表的头节点
    list->head = newnode; //更新链表头节点为新节点
    list->size++;
    return 1;
}

int insertAtTail(linklist* list,Elemtype value)
{
    Node* newnode = createNode(value);
    if(!list->head)
    {
        list->head = newnode;
    }
    else
    {
        Node* temp = list->head; //设置一个变量，从第一个节点开始，用于遍历链表
        while(temp->next) //当变量的指针域不为NULL，也就是还未遍历到最后一个节点时
        {
            temp = temp->next; 
        }
        temp->next = newnode; //遍历到最后一个节点时，退出循环
    }
    list->size++;
    return 1;
}