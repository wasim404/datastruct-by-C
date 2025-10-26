//双链表实现仅改变指针连接顺序交换节点

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

Node* createNode(int value);
LinkedList* createLinkedList();
Node* swapNode(LinkedList* list, int position);
void printLinkedList(LinkedList* list);
void freeList(LinkedList* list);
void insertAtHead(LinkedList* list, int value);

int main() {
    LinkedList* mylist = createLinkedList();

    insertAtHead(mylist, 1);
    insertAtHead(mylist, 2);
    insertAtHead(mylist, 3);
    insertAtHead(mylist, 4);
    insertAtHead(mylist, 5);

    printLinkedList(mylist); // 原始链表：5 4 3 2 1

    swapNode(mylist, 3); // 交换第3个节点和第4个节点（从1开始计数）
    printLinkedList(mylist); // 应为：5 4 2 3 1

    swapNode(mylist, 1); // 交换头部节点
    printLinkedList(mylist); // 应为：4 5 2 3 1

    freeList(mylist);
    return 0;
}

Node* createNode(int value) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->data = value;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        printf("内存分配失败\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertAtHead(LinkedList* list, int value) {
    Node* newnode = createNode(value);
    if (list->head) {
        newnode->next = list->head;
        list->head->prev = newnode;
    }
    list->head = newnode;
    list->size++;
}

Node* swapNode(LinkedList* list, int position) {
    if (!list || !list->head || position < 1) {
        printf("错误：链表未初始化或位置无效。\n");
        return NULL;
    }

    // 情况1：交换头节点和其后一个节点
    if (position == 1) {
        Node* a = list->head;
        Node* b = a->next;
        if (!b) return a; // 只有一个节点，无法交换

        a->next = b->next;
        if (b->next) b->next->prev = a;

        b->prev = NULL;
        b->next = a;
        a->prev = b;
        list->head = b;
        return list->head;
    }

    // 情况2：交换中间位置节点
    Node* prev = list->head;
    for (int i = 1; i < position - 1 && prev; i++) {
        prev = prev->next;
    }

    if (!prev || !prev->next || !prev->next->next) {
        // 越界或没有相邻节点
        return list->head;
    }

    Node* a = prev->next;
    Node* b = a->next;

    // 交换 prev <-> a <-> b <-> bnext
    a->next = b->next;
    if (b->next)
        b->next->prev = a;

    b->prev = prev;
    b->next = a;
    a->prev = b;
    prev->next = b;

    return list->head;
}

void printLinkedList(LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(LinkedList* list) {
    Node* curr = list->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}
