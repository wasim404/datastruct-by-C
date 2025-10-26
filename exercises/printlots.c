//给你一个链表L和另一个链表P，它们包含以升序排列的整数。
//操作PrintLots(L,P)将打印L中那些由P所指定的位置上的元素
//例如，若P=1，3，4，6，那么，L中的第1，3，4，6个元素被打印出来
#include<stdlib.h>
#include<stdio.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

typedef struct LinkedList
{
    Node* head;
    int size;
}LinkedList;

Node* createNode(int value);
LinkedList* createLinkedList();
int LinkedListIsEmpty(LinkedList* list);
void insertAtHead(LinkedList* list,int value);
void PrintAtLocation(LinkedList* list,int position);
void PrintLots(LinkedList* L,LinkedList* P);
void freeList(LinkedList* list);

int main()
{
    LinkedList* L = createLinkedList();
    LinkedList* P = createLinkedList();
    insertAtHead(P,6);
    insertAtHead(P,4);
    insertAtHead(P,3);
    insertAtHead(P,1);

    insertAtHead(L,6);
    insertAtHead(L,5);
    insertAtHead(L,4);
    insertAtHead(L,3);
    insertAtHead(L,2);
    insertAtHead(L,1);

    PrintLots(L,P);
    printf("\n");

    freeList(L);
    freeList(P);
    return 0;
}

Node* createNode(int value)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(!newnode)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if(!list)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int LinkedListIsEmpty(LinkedList* list)
{
    return list->head == NULL;
}

void insertAtHead(LinkedList* list,int value)
{
    Node* newnode = createNode(value);
    newnode->next = list->head;
    list->head = newnode;
    list->size++;
    return;
}

void PrintAtLocation(LinkedList* list,int position)
{
    if(!list || position<1)
    {
        printf("链表未初始化或插入位置不正确\n");
        return;
    }
    if(position==1)
    {
        printf("%d ",list->head->data);
        return;
    }
    if(position>list->size)
    {
        printf("超出范围\n");
        return;
    }
    Node* temp = list->head;
    int index = 1;
    while(index!=position)
    {
        temp = temp->next;
        index++;
    }
    printf("%d ",temp->data);
    return;
}

void PrintLots(LinkedList* L,LinkedList* P)
{
    Node* temp = P->head;
    while(temp)
    {
        int num = temp->data;
        PrintAtLocation(L,num);
        temp = temp->next;
    }
    return;
}

void freeList(LinkedList* list) 
{
    Node* curr = list->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}