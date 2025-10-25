//双向链表

#include <stdio.h>
#include <stdlib.h>
#include"node.h"

//双向链表结构，逻辑上维护头/尾节点
typedef struct DoublyLinkedList
{
    Node* head; //头节点
    Node* tail; //尾节点
}DoublyLinkedList;

DoublyLinkedList* createList();
void insertAtHead(DoublyLinkedList* list,Elemtype value); //插入数据函数都要先检查是否为空
void insertAtTail(DoublyLinkedList* list,Elemtype value);
Node* findNode(DoublyLinkedList* list,int data);
void deleteNode(DoublyLinkedList* list,int data);
void freeList(DoublyLinkedList* list);


DoublyLinkedList* createList()
{
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if(!list)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    list->head = NULL; //初始化头尾指针为NULL
    list->tail = NULL;
    return list;
}

void insertAtHead(DoublyLinkedList* list,Elemtype value)
{
    Node* newnode = createNode(value); //创建新节点
    if(list->head == NULL)
    {
        list->head = list->tail = newnode; //若链表为空，则新节点既是头节点也是尾节点
    }
    else
    {
        newnode->next = list->head; //新节点下一个节点指向头节点
        list->head->prev = newnode; //头节点前一个节点指向
        list->head = newnode; //逻辑上，显式更新当前节点为头节点
    }
}

void insertAtTail(DoublyLinkedList* list,Elemtype value)
{
    Node* newnode = createNode(value);
    if(list->tail == NULL)
    {
        list->head = list->tail = newnode;
    }
    else
    {
        newnode->prev = list->tail; //新节点prev指针指向链表尾
        list->tail->next = newnode; //链表尾节点指向新节点
        list->tail = newnode; //逻辑上，显式更新新节点为尾节点
    }
}

Node* findNode(DoublyLinkedList* list,int data)
{
    Node* cur = list->head; //从头节点开始遍历
    while(cur!=NULL)
    {
        if(cur->value.data==data)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void deleteNode(DoublyLinkedList* list,int data)
{
    Node* target = findNode(list,data); //找到对应的节点
    if(target == NULL)
    {
        printf("未找到节点\n");
        return;
    }
    if(target == list->head) //要删除的是头节点
    {
        list->head = target->next; //显式更新头节点为下一个节点
    }
    else
    {
        target->prev->next = target->next; //待删除节点的前一个节点直接指向待删除节点的下一个节点（跳过当前待删除节点，实现删除效果）
    }
    if(target == list->tail) //要删除的是尾节点
    {
        list->tail = target->prev; //显式更新尾节点为前一个节点
    }
    else
    {
        target->next->prev = target->prev;
    }
    free(target);
}

void freeList(DoublyLinkedList* list)
{
    Node* cur = list->head;
    Node* next;
    while(cur!=NULL)
    {
        next = cur->next; //缓存标记待释放节点的下一个节点
        free(cur);
        cur = next; //移动待删除节点指向下一个节点
    }
    free(list); //释放整个链表
}