#include<stdio.h>
#include<stdlib.h>

//AVL树，就是添加了平衡条件的BST树
// 为了保证AVL树的效率，必须要定义一个变量保存高度
typedef struct AVLtreeNode
{
    int key; //关键字
    struct AVLtreeNode* left; //左孩子
    struct AVLtreeNode* right; //右孩子
    int height; //以该节点为根的子树高度
}AVLtreeNode;

int height(AVLtreeNode* node); //获取节点的高度
int max(int a,int b); //取较大值
AVLtreeNode* createAVLtreeNode(int key); //创建新AVL树节点
int getBalance(AVLtreeNode* node); //获取平衡因子
AVLtreeNode* rightRotate(AVLtreeNode* node); //右旋
AVLtreeNode* leftRotate(AVLtreeNode* node); //左旋
AVLtreeNode* insert(AVLtreeNode* node,int key); //标准的AVL插入
void inorder(AVLtreeNode* root);

int main()
{
    AVLtreeNode* root = NULL;

    // 示例：插入一组数据，让原本会退化成链表的插入保持平衡
    int arr[] = { 10, 20, 30, 40, 50, 25 };
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    printf("中序遍历（升序）：");
    inorder(root);
    printf("\n");
    return 0;
}

int height(AVLtreeNode* node)
{
    if(node == NULL)
    {
        return 0;
    }
    return node->height;
}

int max(int a,int b)
{
    return(a>b)?a:b;
}

AVLtreeNode* createAVLtreeNode(int key)
{
    AVLtreeNode* node = (AVLtreeNode*)malloc(sizeof(AVLtreeNode));
    if(node == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; //新节点高度为1
    return node;
}

int getBalance(AVLtreeNode* node)
{
    if(node == NULL)
    {
        return 0;
    }
    return height(node->left)-height(node->right);
}

AVLtreeNode* rightRotate(AVLtreeNode* node)
{
    AVLtreeNode* left = node->left;
    AVLtreeNode* deeperRight = left->right;
    //旋转，其实就是指针的重新链接
    left->right = node;
    node->left = deeperRight;
    //更新高度，先更新底层的
    node->height = 1+max(height(node->left),height(node->right));
    left->height = 1+max(height(left->left),height(left->right));
    //返回新的根
    return left;
}

AVLtreeNode* leftRotate(AVLtreeNode* node)
{
    AVLtreeNode* right = node->right;
    AVLtreeNode* deeperLeft = right->left;
    //旋转
    right->left = node;
    node->right = deeperLeft;
    //更新高度
    node->height = 1+max(height(node->left),height(node->right));
    right->height = 1+max(height(right->left),height(right->right));
    //返回新的根
    return right;
}

AVLtreeNode* insert(AVLtreeNode* node,int key)
{
    //正常的BST插入
    //创建新节点
    if(node==NULL)
    {
        return createAVLtreeNode(key);
    }
    //连接
    if(key<node->key)
    {
        node->left = insert(node->left,key);
    }
    else if(key>node->key)
    {
        node->right = insert(node->right,key);
    }
    else
    {
        //相同key值不允许插入，可以修改
        return node;
    }

    //更新高度
    node->height = 1+max(height(node->left), height(node->right));

    //计算平衡因子，决定是否需要旋转调整
    int balance = getBalance(node);

    //旋转
    if(balance>1 && key<node->left->key) //左左型插入，右旋
    {
        return rightRotate(node);
    }
    if(balance<-1 && key>node->right->key) //右右型插入，左旋
    {
        return leftRotate(node);
    }
    if(balance>1 && key>node->left->key) //左右型插入
    {
        node->left = leftRotate(node->left); //左节点左旋
        return rightRotate(node); //整个部分右旋
    }
    if(balance<-1 && key<node->right->key) //右左型插入
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    //平衡，原样返回
    return node;
}

void inorder(AVLtreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}