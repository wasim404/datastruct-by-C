# include"node.h"
//创建节点的函数，返回一个新节点
Node* createNode(Elemtype value)
{
    Node* newnode = (Node*)malloc(sizeof(Node)); //使用malloc动态分配内存
    if(!newnode)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    newnode->value = value; //给新节点的数据域赋值，注意数据类型要符合你的节点中使用的数据类型
    newnode->prev = NULL; //初始化指针都指向NULL
    newnode->next = NULL;
    return newnode;
}