/* 务必有个头节点 list */

//定义链表中一个节点的区域
struct SingleLinkedList
{
    int data;
    struct SingleLinkedList *next;
};

// node节点的地址(为指向struct LinkedList的指针)
typedef struct SingleLinkedList *node;
typedef struct SingleLinkedList *list; //header

//为链表的尾部添加一个节点，返回头节点
list InsertAtEnd(list l, int value); //head为链表头，value为新增节点的值

//返回 离头最近的data 所在位置
node Find(list l, int data);

//删除全部的data,返回删除个数
int Delete(list l, int data);

//
//遍历链表
/* 
    node p;
    p = head;
    while(p != NULL)
    {
        p = p->next;
    }
*/