//链式结构实现队列

#include"node.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//链式队列结构，维护头尾指针
typedef struct LinkedQueue
{
    Node* front;
    Node* rear;
}LinkedQueue;

LinkedQueue* createLinkedQueue();
bool QueueIsEmpty(LinkedQueue* q);
void Enqueue(LinkedQueue* q,Elemtype value);
bool Dequeue(LinkedQueue* q,Elemtype* value);
void DestroyQueue(LinkedQueue* q);
void PrintQueue(LinkedQueue* q);

int main()
{
    LinkedQueue* q = createLinkedQueue();
    if (!q) return -1;

    // 构造测试数据
    Elemtype e1 = {10, "A001"};
    Elemtype e2 = {20, "B002"};
    Elemtype e3 = {30, "C003"};
    Elemtype value;
    printf("入队三个元素:\n");
    Enqueue(q, e1);
    Enqueue(q, e2);
    Enqueue(q, e3);

    PrintQueue(q);
    Dequeue(q,&value);
    PrintQueue(q);
    DestroyQueue(q);
    printf("队列已销毁。\n");
    return 0;
}

LinkedQueue* createLinkedQueue()
{
    LinkedQueue* q = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if(!q)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool QueueIsEmpty(LinkedQueue* q)
{
    return q->front == NULL;
}

void Enqueue(LinkedQueue* q,Elemtype value)
{
    Node* newnode = createNode(value);
    if(QueueIsEmpty(q))
    {
        q->front = q->rear = newnode;
    }
    else
    {
        q->rear->next = newnode;
        q->rear = newnode;
    }
}

bool Dequeue(LinkedQueue* q,Elemtype* value) //出队可以看作释放一个节点
{
    if(QueueIsEmpty(q))
    {
        printf("队列为空，无法出队\n");
        return false;
    }
    Node* temp = q->front;
    *value = temp->value;
    q->front = q->front->next;
    if(q->front == NULL) //队列变空，更新rear
    {
        q->rear = NULL;
    }
    free(temp);
    return true;
}

void DestroyQueue(LinkedQueue* q)
{
    while(!QueueIsEmpty(q))
    {
        Elemtype temp;
        Dequeue(q,&temp);
    }
    free(q); //释放链式队列结构本身
}

void PrintQueue(LinkedQueue* q)
{
    if(!q || q->front == NULL)
    {
        printf("队列为空或未初始化\n");
        return;
    }
    Node* temp = q->front;
    while(temp)
    {
        printf("%d:%s\n",temp->value.data,temp->value.num);
        temp = temp->next;
    }
    printf("\n");
    return;
}