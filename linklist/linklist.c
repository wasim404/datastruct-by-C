#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//定义数据类型
typedef struct elemtype
{
    int num;
    char data[10]; //定义一个字符串（一维字符数组）、
    char* value[2]; //定义一个数组，包含两个元素，每个元素都是一个 char* 类型的指针。
}elemtype;

//定义链表节点的结构
typedef struct listnode
{
    elemtype data; //数据域
    struct listnode* next; //指针域，指向下一个结点
}listnode;

//定义链表结构体（可选）
typedef struct linklist
{
    listnode* head; //定义头指针，指向第一个结点
    int size; //当前链表节点数
}linklist;

//函数声明
linklist* createlist();
int insertathead(linklist* list,elemtype value);
int insertattail(linklist* list,elemtype value);
int findnode(linklist* list,elemtype value);


int main()
{
    linklist* list = createlist();
    elemtype a = {1,"niko",{"123","456"}};
    elemtype b = {2,"m0NESY",{"666","999"}};
    elemtype c = {3,"donk",{"000","666"}};
    insertathead(list,b);
    insertathead(list,a);
    insertattail(list,c);
    printf("num 2 is in the %d position",findnode(list,b));
    return 0;
}

linklist* createlist()
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

int insertathead(linklist* list,elemtype value)
{
    listnode* newnode = (listnode*)malloc(sizeof(listnode)); //创建一个新的节点
    if(!newnode)
    {
        printf("内存分配失败\n");
        return 0;
    }
    newnode->data = value; //将数据传入新节点的数据域
    newnode->next =list->head; //将新节点指向链表的头节点
    list->head = newnode; //更新链表头节点为新节点
    list->size++;
    return 1;
}

int insertattail(linklist* list,elemtype value)
{
    listnode* newnode = (listnode*)malloc(sizeof(listnode));
    if(!newnode)
    {
        printf("内存分配失败\n");
        return 0;
    }
    newnode->data = value;
    newnode->next = NULL; //最后一个节点的指针域为NULL
    if(!list->head)
    {
        list->head = newnode;
    }
    else
    {
        listnode* temp = list->head; //设置一个变量，从第一个节点开始，用于遍历链表
        while(temp->next) //当变量的指针域不为NULL，也就是还未遍历到最后一个节点时
        {
            temp = temp->next; 
        }
        temp->next = newnode; //遍历到最后一个节点时，退出循环
    }
    list->size++;
    return 1;
}

int findnode(linklist* list,elemtype value)
{
    listnode* temp = list->head;
    int res = 1;
    while( temp && temp->data.num != value.num )
    {
        temp = temp->next;
        res += 1;
    }
    return res;
}

