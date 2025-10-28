#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//二叉树节点的结构
typedef struct TreeNode
{
    int data;
    struct TreeNode* left; //左孩子指针
    struct TreeNode* right; //右孩子指针
}TreeNode;

//队列节点，用于层序遍历，其中数据域是指向TreeNode的指针
typedef struct QueueNode
{
    TreeNode* treeNode;
    struct QueueNode* next;
}QueueNode;

//队列
typedef struct Queue
{
    QueueNode* front;
    QueueNode* rear;
}Queue;

TreeNode* createTreeNode(int value);
Queue* createQueue();
QueueNode* createQueueNode(TreeNode* node);
void enqueue(Queue* q,TreeNode* node);
TreeNode* dequeue(Queue* q);
bool queueIsEmpty(Queue* q);
void preorder(TreeNode* node);
void inorder(TreeNode* node);
void postorder(TreeNode* node);
void levelorder(TreeNode* node);
int height(TreeNode* node);
int countNodes(TreeNode* node);
void freeTree(TreeNode* node);

TreeNode* buildSampleTree() {
    TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    return root;
}

int main()
{
    TreeNode* root = buildSampleTree();

    printf("先序遍历: ");
    preorder(root);
    printf("\n");

    printf("中序遍历: ");
    inorder(root);
    printf("\n");

    printf("后序遍历: ");
    postorder(root);
    printf("\n");

    printf("层序遍历: ");
    levelorder(root);
    printf("\n");

    printf("树的高度: %d\n", height(root));
    printf("节点总数: %d\n", countNodes(root));

    // 释放内存
    freeTree(root);
    return 0;
}

TreeNode* createTreeNode(int value)
{
    TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
    if(!newnode)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if(!q)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

QueueNode* createQueueNode(TreeNode* node)
{
    QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
    if(!newnode)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->treeNode = node;
    newnode->next = NULL;
    return newnode;
}

void enqueue(Queue* q,TreeNode* node)
{
    QueueNode* temp = createQueueNode(node);
    if(q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

TreeNode* dequeue(Queue* q)
{
    if(q->front == NULL)
    {
        printf("队列已空\n");
        return NULL;
    }
    QueueNode* temp = q->front;
    TreeNode* node = temp->treeNode;
    q->front = q->front->next;
    if(q->front == NULL) //若队列恰好就一个节点
    {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

bool queueIsEmpty(Queue* q)
{
    return q->front == NULL;
}

void preorder(TreeNode* node)
{
    if(node != NULL)
    {
        printf("%d ",node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(TreeNode* node)
{
    if(node != NULL)
    {
        preorder(node->left);
        printf("%d ",node->data);
        preorder(node->right);
    }
}

void postorder(TreeNode* node)
{
    if(node != NULL)
    {
        preorder(node->left);
        preorder(node->right);
        printf("%d ",node->data);
    }
}

void levelorder(TreeNode* node)
{
    if(node==NULL)
    {
        return;
    }
    Queue* q = createQueue();
    enqueue(q,node);
    while(!queueIsEmpty(q))
    {
        TreeNode* cur = dequeue(q);
        printf("%d ",cur->data);
        if(cur->left)
        {
            enqueue(q,cur->left);
        }
        if(cur->right)
        {
            enqueue(q,cur->right);
        }
    }
    free(q);
}

int height(TreeNode* node)
{
    if(node==NULL)
    {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return(leftHeight>rightHeight?leftHeight:rightHeight)+1;
}

int countNodes(TreeNode* node)
{
    if(node==NULL)
    {
        return 0;
    }
    return 1+countNodes(node->left)+countNodes(node->right);
}

void freeTree(TreeNode* node)
{
    if(node==NULL)
    {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}