#include "leftheap.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    ElementType Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int Npl;
};

/* 直接得到 NULL */
PriorityQueue Initialize(void)
{
    //
    return NULL;
}

/* begin */
/* merge */
//
void SwapChildren(PriorityQueue H)
{
    PriorityQueue Tmp;

    Tmp = H->Left;
    H->Left = H->Right;
    H->Right = Tmp;
}

/* 核心 */
/* 这里的参数 H1->Element < H2->Element */
static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
    if (H1->Left == NULL) /* Single node */
    {
        /* 这中情况连 Npl 都不用更新 */
        H1->Left = H2; /* H1->Right is already NULL, H1->Npl is already 0 */
    }
    else
    {
        H1->Right = Merge(H1->Right, H2);

        if (H1->Left->Npl < H1->Right->Npl)
        {
            SwapChildren(H1);
        }

        H1->Npl = H1->Right->Npl + 1;
    }

    return H1;
}

/* 总例程 */
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
    if (H1 == NULL)
        return H2;

    if (H2 == NULL)
        return H1;

    /* 合并具有大根值的堆与具有小根值的堆的右子堆 */
    if (H1->Element < H2->Element)
        return Merge1(H1, H2);
    else
        return Merge1(H2, H1);
}
//
/* end */

/* 一个节点与一个堆的合并 */
PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
    PriorityQueue SingleNode;

    SingleNode = malloc(sizeof(struct TreeNode));
    if (SingleNode == NULL)
    {
        printf("Out of space!!!");
    }
    else
    {
        SingleNode->Element = X;
        SingleNode->Npl = 0;
        SingleNode->Left = SingleNode->Right = NULL;
        H = Merge(SingleNode, H);
    }

    return H;
}

/* 删掉根，合并左右子堆 */
PriorityQueue DeleteMin1(PriorityQueue H)
{
    PriorityQueue LeftHeap, RightHeap;

    if (IsEmpty(H))
    {
        printf("Priority queue is empty");
        return H;
    }

    LeftHeap = H->Left;
    RightHeap = H->Right;
    free(H);

    return Merge(LeftHeap, RightHeap);
}

ElementType FindMin(PriorityQueue H)
{
    if (!IsEmpty(H))
    {
        return H->Element;
    }
    printf("Priority Queue is Empty");
    return 0;
}

int IsEmpty(PriorityQueue H)
{
    return H == NULL;
}
