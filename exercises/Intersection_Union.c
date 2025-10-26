#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

// 顺序表定义
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;

// 初始化线性表
void InitList(SqList *L) {
    L->length = 0;
}

// 返回表长度
int ListLength(SqList L) {
    return L.length;
}

// 取第 i 个元素（1-based）
int GetElem(SqList L, int i, ElemType *e) {
    if (i < 1 || i > L.length) return 0;
    *e = L.data[i - 1];
    return 1;
}

// 在线性表第 i 个位置插入元素 e
int ListInsert(SqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) return 0;
    if (L->length >= MAXSIZE) return 0;
    for (int k = L->length - 1; k >= i - 1; k--) {
        L->data[k + 1] = L->data[k];
    }
    L->data[i - 1] = e;
    L->length++;
    return 1;
}

// 打印线性表
void PrintList(SqList L) {
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

// 求交集：L3 = L1 ∩ L2
void ListIntersection(SqList L1, SqList L2, SqList *L3) {
    InitList(L3);
    int i = 1, j = 1;
    ElemType e1, e2;
    while (i <= ListLength(L1) && j <= ListLength(L2)) {
        GetElem(L1, i, &e1);
        GetElem(L2, j, &e2);
        if (e1 < e2) {
            i++;
        } else if (e1 > e2) {
            j++;
        } else {
            ListInsert(L3, ListLength(*L3) + 1, e1);
            i++;
            j++;
        }
    }
}

// 求并集：L3 = L1 ∪ L2
void ListUnion(SqList L1, SqList L2, SqList *L3) {
    InitList(L3);
    int i = 1, j = 1;
    ElemType e1, e2;
    while (i <= ListLength(L1) && j <= ListLength(L2)) {
        GetElem(L1, i, &e1);
        GetElem(L2, j, &e2);
        if (e1 < e2) {
            ListInsert(L3, ListLength(*L3) + 1, e1);
            i++;
        } else if (e1 > e2) {
            ListInsert(L3, ListLength(*L3) + 1, e2);
            j++;
        } else {
            ListInsert(L3, ListLength(*L3) + 1, e1);
            i++;
            j++;
        }
    }
    // 处理剩余部分
    while (i <= ListLength(L1)) {
        GetElem(L1, i++, &e1);
        ListInsert(L3, ListLength(*L3) + 1, e1);
    }
    while (j <= ListLength(L2)) {
        GetElem(L2, j++, &e2);
        ListInsert(L3, ListLength(*L3) + 1, e2);
    }
}

int main() {
    SqList L1, L2, L3;
    InitList(&L1);
    InitList(&L2);

    // 构造两个有序表
    int a1[] = {1, 3, 5, 7, 9};
    int a2[] = {3, 4, 5, 8, 9, 10};
    for (int i = 0; i < 5; i++) ListInsert(&L1, i + 1, a1[i]);
    for (int i = 0; i < 6; i++) ListInsert(&L2, i + 1, a2[i]);

    printf("L1: ");
    PrintList(L1);
    printf("L2: ");
    PrintList(L2);

    // 求交集
    ListIntersection(L1, L2, &L3);
    printf("L1 ∩ L2 = ");
    PrintList(L3);

    // 求并集
    ListUnion(L1, L2, &L3);
    printf("L1 ∪ L2 = ");
    PrintList(L3);

    return 0;
}
