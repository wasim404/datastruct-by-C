//单链表

#include"node.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
    if (!myList) {
        return -1;
    }

    Elemtype e1 = {10, "A001"};
    Elemtype e2 = {20, "B002"};
    Elemtype e3 = {30, "C003"};
    Elemtype e4 = {40, "D004"};
    Elemtype e5 = {50, "E005"};

    // 头插法插入
    printf("=== 头插法插入 e1, e2 ===\n");
    insertAtHead(myList, e1);
    insertAtHead(myList, e2);
    printList(myList);

    // 尾插法插入
    printf("=== 尾插法插入 e3 ===\n");
    insertAtTail(myList, e3);
    printList(myList);

    // 插入到指定位置（位置从1开始）
    printf("=== 在位置2插入 e4 ===\n");
    insertAtPosition(myList, 2, e4);
    printList(myList);

    // 查找节点
    printf("=== 查找数据为10的节点位置 ===\n");
    int pos = findNode(myList, 10);
    if (pos != -1)
        printf("10号在链表中第 %d 个位置\n", pos);
    else
        printf("未找到数据为10的节点\n");

    // 获取指定位置的值
    printf("=== 获取第3个位置的值 ===\n");
    Elemtype val;
    if (getAtPosition(myList, 3, &val)) {
        printf("第3个节点的值为: %d:%s\n", val.data, val.num);
    } else {
        printf("获取失败\n");
    }

    // 删除指定位置节点
    printf("=== 删除第1个位置的节点 ===\n");
    deleteAtPosition(myList, 1);
    printList(myList);

    // 删除指定数据的节点
    printf("=== 删除数据为30的节点 ===\n");
    if (deleteByData(myList, 30)) {
        printf("删除成功\n");
    } else {
        printf("未找到数据为30的节点\n");
    }
    printList(myList);

    // 清空链表
    printf("=== 清空链表 ===\n");
    clearList(myList);
    printList(myList);

    // 再次插入测试销毁
    printf("=== 插入一个节点用于测试销毁 ===\n");
    insertAtHead(myList, e5);
    printList(myList);

    // 销毁链表（释放所有节点内存）
    printf("=== 销毁链表 ===\n");
    destroyList(myList);
    free(myList); // 释放链表结构体本身
    myList = NULL;

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
    if(!list||position<1 || position>list->size)
    {
        printf("删除位置错误\n");
        return 0;
    }
    Node* toDelete;
    if(position==1)
    {
        toDelete = list->head;
        list->head = list->head->next;
    }
    else
    {
        Node* prev = list->head;
        for(int i=1;i<position-1;i++)
        {
            prev = prev->next; //退出循环时，prev指向待删除节点的前一个节点
        }
        toDelete = prev->next; //cur指向待删除节点
        prev->next = toDelete->next;
    }
    free(toDelete); //统一释放内存节点
    list->size--;
    return 1;
}

int deleteByData(linklist* list,int target)
{
    if(!list || list->size == 0)
    {
        return 0;
    }
    Node* cur = list->head;
    Node* prev = NULL;
    while(cur!=NULL && cur->value.data!=target)
    {
        prev = cur; //指向cur前一个节点
        cur = cur->next; //往下移动，最终cur指向待删除节点
    }
    if(cur==NULL) //未找到
    {
        return 0;
    }
    if(prev == NULL) //若头节点就是要删除的节点
    {
        list->head = cur->next;
    }
    else
    {
        prev->next = cur->next;
    }
    free(cur);
    list->size--;
    return 1;
}

bool getAtPosition(linklist* list,int position,Elemtype* value)
{
    if(!list || position<1 || position>list->size || !value)
    {
        return false;
    }
    Node* cur = list->head;
    for(int i=1;i<position;i++)
    {
        cur = cur->next; //cur指向当前位置节点
    }
    *value = cur->value;
    return true;
}

void clearList(linklist* list)
{
    if(!list)
    {
        return;
    }
    destroyList(list);
    list->head = NULL;
    list->size = 0;
}