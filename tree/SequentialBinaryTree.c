#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100 

//顺序存储二叉树结构
//对于下标为i的任意节点，父节点下标：(i-1)//2 左孩子：2*i+1 右孩子：2*i+2
typedef struct SqBinaryTree
{
    int data[MAX_SIZE];
    int size; //记录当前二叉树有效节点数（按层序），也就是树目前逻辑上占用的下标范围长度
    bool used[MAX_SIZE]; //标记该位置是否被使用
}SqBinaryTree;

void initTree(SqBinaryTree* tree);
void insert(SqBinaryTree* tree,int index,int value);
void buildFormList(SqBinaryTree* tree,int values[],int n);
bool getParent(SqBinaryTree* tree,int index,int* parent);
bool getLeftChild(SqBinaryTree* tree,int index,int* left);
bool getRightChild(SqBinaryTree* tree,int index,int* right);
void preorder(SqBinaryTree* tree,int index);
void inorder(SqBinaryTree* tree,int index);
void postorder(SqBinaryTree* tree,int index);
void levelorder(SqBinaryTree* tree);
void PrintTree(SqBinaryTree* tree);

int main()
{
    SqBinaryTree tree;
    
    // 构建如下完全二叉树：
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    int values[] = {1, 2, 3, 4, 5}; // 层序输入，无空节点
    int n = sizeof(values) / sizeof(values[0]);

    buildFormList(&tree, values, n);

    printf("前序遍历: ");
    preorder(&tree, 0);
    printf("\n");

    printf("中序遍历: ");
    inorder(&tree, 0);
    printf("\n");

    printf("后序遍历: ");
    postorder(&tree, 0);
    printf("\n");

    printf("层序遍历: ");
    levelorder(&tree);
    printf("\n");

    PrintTree(&tree);

    // 测试父子关系
    int parent_val;
    if (getParent(&tree, 4, &parent_val)) {
        printf("节点5（索引4）的父节点是: %d\n", parent_val);
    }

    int left_val;
    if (getLeftChild(&tree, 1, &left_val)) {
        printf("节点2（索引1）的左孩子是: %d\n", left_val);
    }
    return 0;
}

void initTree(SqBinaryTree* tree)
{
    tree->size = 0;
    for(int i=0;i<MAX_SIZE;i++)
    {
        tree->used[i] = false; //初始时，节点均未使用，置为false
    }
}

void insert(SqBinaryTree* tree,int index,int value)
{
    if(index<0 || index>=MAX_SIZE) //检查插入位置
    {
        printf("插入位置错误\n");
        return;
    }
    tree->data[index] = value;
    tree->used[index] = true;
    if(index>=tree->size)
    {
        tree->size = index+1; //保证size永远表示“当前数组中最后一个有效节点的下标 + 1”
    }
}

void buildFormList(SqBinaryTree* tree,int values[],int n) //将数组转换成二叉树
{
    initTree(tree);
    for(int i=0;i<n && i<MAX_SIZE;i++) //n是数组长度
    {
        if(values[i] != -1) //-1表示空节点
        {
            insert(tree,i,values[i]);
        }
    }
    tree->size = n>MAX_SIZE ? MAX_SIZE : n; //如果n比MAX_SIZE大,就把tree->size限制在MAX_SIZE,否则就取n本身。
}

bool getParent(SqBinaryTree* tree,int index,int* parent)
{
    if(index<=0 || index >= tree->size || !tree->used[index])
    {
        return false;
    }
    int p = (index-1)/2; //父节点的下标
    //因为是数组存储，可能存在一种情况，父节点(i-1)/2位置的元素已被删除或没有插入，因此要检查
    if(tree->used[p])
    {
        *parent = tree->data[p];
        return true;
    }
    return false;
}

bool getLeftChild(SqBinaryTree* tree,int index,int* left)
{
    int l=2*index+1;
    if(l>=tree->size || !tree->used[l]) //检查左孩子下标是否超出范围或未使用
    {
        return false;
    }
    *left = tree->data[l];
    return true;
}

bool getRightChild(SqBinaryTree* tree,int index,int* right)
{
    int r=2*index+2;
    if(r>=tree->size || !tree->used[r]) //检查左孩子下标是否超出范围或未使用
    {
        return false;
    }
    *right = tree->data[r];
    return true;
}

void preorder(SqBinaryTree* tree,int index)
{
    if(index>=tree->size || !tree->used[index])
    {
        return;
    }
    printf("%d ",tree->data[index]);
    preorder(tree,2*index+1);
    preorder(tree,2*index+2);
}

void inorder(SqBinaryTree* tree,int index)
{
    if(index>=tree->size || !tree->used[index])
    {
        return;
    }
    inorder(tree,2*index+1);
    printf("%d ",tree->data[index]);
    inorder(tree,2*index+2);
}

void postorder(SqBinaryTree* tree,int index)
{
    if(index>=tree->size || !tree->used[index])
    {
        return;
    }
    postorder(tree, 2 * index + 1);
    postorder(tree, 2 * index + 2);
    printf("%d ", tree->data[index]);
}

void levelorder(SqBinaryTree* tree)
{
    for(int i=0;i<tree->size;i++)
    {
        if(tree->used[i])
        {
            printf("%d ",tree->data[i]);
        }
    }
}

void PrintTree(SqBinaryTree* tree)
{
    for(int i=0;i<tree->size;i++)
    {
        if(tree->used[i])
        {
            printf("%d: %d\n",i,tree->data[i]);
        }
        else
        {
            printf("%d: NULL\n",i);
        }
    }
}