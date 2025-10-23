#include"node.h"
#include<stdio.h>
#include<stdlib.h>
//gcc .\linklist\linklist.c .\ds_outline\node.c -I ds_outline -o linklist

//定义链表结构体
typedef struct linklist
{
    Node* head; //定义头指针，指向第一个结点
    int size; //当前链表节点数
}linklist;

linklist* createList();
int insertAtHead(linklist* list,Elemtype value);
int insertAtTail(linklist* list,Elemtype value);
bool linklistIsEmpty(linklist* list);
void printList(linklist* list);
void destroyList(linklist* list);
int findNode(linklist* list,int target);
int getLength(linklist* list);
int insertAtPosition(linklist* list,int position,Elemtype value);
int deleteAtPosition(linklist* list,int position);
int deleteByData(linklist* list,int target);
bool getAtPosition(linklist* list,int position,Elemtype* value);
void clearList(linklist* list);


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
    printList(myList);
    printf("10号在链表中第%d个位置\n",findNode(myList,10));
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

bool linklistIsEmpty(linklist* list)
{
    return list->size == 0;
}

void printList(linklist* list)
{
    if(linklistIsEmpty(list))
    {
        printf("链表为空\n");
        return;
    }
    Node* cur = list->head;
    while(cur != NULL)
    {
        printf("%d:%s\n",cur->value.data,cur->value.num);
        cur = cur->next;
    }
    printf("\n");
}

void destroyList(linklist* list)
{
    Node* cur = list->head;
    Node* next;
    while(cur!=NULL)
    {
        next = cur->next; //储存当前节点的下一个节点
        free(cur);
        cur = next;
    }
    printf("链表已销毁\n");
}

int findNode(linklist* list,int target)
{
    Node* cur = list->head;
    int index = 1;
    while(cur!=NULL)
    {
        if(cur->value.data == target)
        {
            return index;
        }
        cur = cur->next;
        index++;
    }
    return -1;
}

int insertAtPosition(linklist* list,int position,Elemtype value)
{
    //检查插入的位置
    if(position<1 || position>list->size+1)
    {
        perror("插入位置错误");
        return 0;
    }
    Node* newnode = createNode(value);
    if(position==1) //在头部插入
    {
        newnode->next = list->head;
        list->head = newnode;
    }
    else
    {
        Node* cur = list->head; //head对应索引值这里认为是1
        for(int i=1;i<position-1;i++)
        {
            cur = cur->next;
        }
        newnode->next = cur->next;
        cur->next = newnode;
    }
    list->size++;
    return 1;
}

int deleteAtPosition(linklist* list,int position)
{
    if(position<1 || position>list->size)
    {
        perror("删除位置错误");
        return 0;
    }
    Node* cur;
    if(position==1)
    
}
int deleteByData(linklist* list,int target);
bool getAtPosition(linklist* list,int position,Elemtype* value);
void clearList(linklist* list);