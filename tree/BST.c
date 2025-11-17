//二叉排序树
//左子树所有节点都小于当前节点，右子树所有节点都大于当前节点
//中序遍历二叉排序树就可以得到一个升序排序的数组
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* createTreeNode(int value);
TreeNode* insertNode(TreeNode* node,int value);
void inorder(TreeNode* node);

int main()
{
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    TreeNode* root = NULL;
    for (int i = 0; i < 7; i++)
        root = insertNode(root, arr[i]);

    printf("中序遍历结果：");
    inorder(root);
    printf("\n");
    return 0;
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

TreeNode* insertNode(TreeNode* node,int value)
{
    if(node == NULL) //来到叶子节点下方，新建一个节点
    {
        return createTreeNode(value); 
    }
    if(value<node->data)
    {
        node->left = insertNode(node->left,value);
    }
    else if(value > node->data)
    {
        node->right = insertNode(node->right, value);
    }
    return node;
}

void inorder(TreeNode* node)
{
    if(node == NULL)
    {
        return;
    }
    inorder(node->left);
    printf("%d ",node->data);
    inorder(node->right);
}
