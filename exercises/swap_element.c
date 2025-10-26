//单链表实现仅改变指针连接顺序交换节点

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
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

    printLinkedList(mylist);  // 原始：5 4 3 2 1

    swapNode(mylist, 3);      // 交换第3个和第4个节点 → 5 4 2 3 1
    printLinkedList(mylist);

    swapNode(mylist, 1);      // 交换头节点和第二个 → 4 5 2 3 1
    printLinkedList(mylist);

    swapNode(mylist, 4);      // 交换倒数两个 → 4 5 2 1 3
    printLinkedList(mylist);

    freeList(mylist);
    return 0;
}

Node* createNode(int value) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) {
        printf("内存分配失败\n");
        exit(1);
    }
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        printf("内存分配失败\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertAtHead(LinkedList* list, int value) {
    Node* newnode = createNode(value);
    newnode->next = list->head;
    list->head = newnode;
    list->size++;
}

Node* swapNode(LinkedList* list, int position) {
    if (!list || !list->head) {
        printf("链表未初始化或为空\n");
        return NULL;
    }

    if (position < 1 || !list->head->next) {
        // 无效位置 或 只有一个节点
        return list->head;
    }

    // 特殊情况：交换第1个和第2个节点
    if (position == 1) {
        Node* a = list->head;
        Node* b = a->next;
        if (!b) return list->head; // 只有一个节点无法交换
        a->next = b->next;
        b->next = a;
        list->head = b;
        return list->head;
    }

    // 一般情况
    Node* prev = list->head;
    for (int i = 1; i < position - 1 && prev->next && prev->next->next; i++) {
        prev = prev->next;
    }

    // 检查是否越界
    if (!prev->next || !prev->next->next) {
        return list->head;
    }

    Node* a = prev->next;
    Node* b = a->next;

    a->next = b->next;
    b->next = a;
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
