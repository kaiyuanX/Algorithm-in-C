#include "single linked list.h"
#include <stdio.h>
#include <stdlib.h>
//
//
list InsertAtEnd(list l, int value)
{
    node temp, p;
    if ((temp = (node)malloc(sizeof(struct SingleLinkedList))) == NULL)
    {
        printf("创建失败,内存不足。");
    }
    temp->next = NULL;
    temp->data = value; //为新增的节点赋值

    p = l;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;

    return l;
}

node Find(list l, int data)
{
    node p = l->next;
    while (p != NULL && p->data != data)
    {
        p = p->next;
    }
    return p;
}

int Delete(list l, int data)
{
    node p = l;
    int n = 0;

    while ((p->next) != NULL)
    {
        if ((p->next)->data == data)
        {
            node temp = p->next;
            p->next = (p->next)->next;
            free(temp);
            n++;
            continue;
        }
        p = p->next;
    }

    return n;
}

