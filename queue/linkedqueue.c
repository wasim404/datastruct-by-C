#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//节点结构
typedef struct Node
{
    int data;
    struct Node* next;
}Node;

//队列结构
typedef struct Queue
{
    Node* front; //队首
    Node* rear; //队尾
}Queue;

Node* createNode(int data);
Queue* createQueue();
bool queueIsEmpty(Queue* q);
int dequeue(Queue* q);
void destroyQueue(Queue* q);

int main()
{

    return 0;
}

Node* createNode(int data)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(!newnode)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if(!q)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool queueIsEmpty(Queue* q)
{
    return q->front == NULL;
}

void enqueue(Queue* q,int value) //入队，在队尾插入
{
    Node* newnode = createNode(value);
    if(queueIsEmpty(q))
    {
        q->front = q->rear = newnode; //第一个元素，既是队首也是队尾
    }
    else
    {
        q->rear->next = newnode; //队尾节点next指针指向新节点
        newnode = q->rear; //显式更新新节点为队尾
    }
}

int dequeue(Queue* q) //出队
{
    if(queueIsEmpty(q))
    {
        perror("队列为空，无法出队");
        exit(EXIT_FAILURE);
    }
    Node* temp = q->front; //temp节点指向队首
    int value = temp->data; //获取队首元素的数据
    q->front = q->front->next; //队首更新为原队首节点的下一个节点
    if(q->front==NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

void destroyQueue(Queue* q)
{
    while(!queueIsEmpty(q)) //当队列还不是空
    {
        dequeue(q);
    }
    free(q);
}