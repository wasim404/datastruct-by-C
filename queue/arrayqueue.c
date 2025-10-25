//循环数组形式实现队列

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100

typedef struct ArrayQueue
{
    int Queue[MAX_SIZE]; //储存队列数据
    int front; //队首
    int rear; //队尾
    int size; //队列大小
}ArrayQueue;

void createQueue(ArrayQueue *q);
bool QueueIsEmpty(ArrayQueue *q);
bool QueueIsFull(ArrayQueue *q);
bool Enqueue(ArrayQueue *q,int value);
bool Dequeue(ArrayQueue *q,int *value);


int main()
{
    ArrayQueue q;
    createQueue(&q);

    Enqueue(&q, 10);
    Enqueue(&q, 20);
    Enqueue(&q, 30);

    int val;
    while (!QueueIsEmpty(&q)) {
        Dequeue(&q, &val);
        printf("%d ", val); // 输出：10 20 30
    }
    printf("\n");
    return 0;
}

void createQueue(ArrayQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

bool QueueIsEmpty(ArrayQueue *q)
{
    return q->size == 0;
}

bool QueueIsFull(ArrayQueue *q)
{
    return q->size == MAX_SIZE;
}

bool Enqueue(ArrayQueue *q,int value)
{
    if(QueueIsFull(q))
    {
        printf("队列已满\n");
        return false;
    }
    q->Queue[q->rear] = value; //队尾入队
    q->rear = (q->rear+1)%MAX_SIZE; //队尾“指针”达到数组末尾时，自动“绕回”到开头
    q->size++;
    return true;
}

bool Dequeue(ArrayQueue *q,int *value)
{
    if(QueueIsEmpty(q))
    {
        printf("队列已空\n");
        return false;
    }
    *value = q->Queue[q->front];
    q->front = (q->front+1)%MAX_SIZE;
    q->size--;
    return true;
}