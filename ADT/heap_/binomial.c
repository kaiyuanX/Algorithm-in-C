#include "binomial.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct BinNode *Position;

struct BinNode
{
    ElementType Element;
    Position LeftChild;
    Position NextSibling;
};

struct Collection
{
    int CurrentSize;
    BinTree TheTrees[MaxTrees]; // TheTrees : 指针的指针
};

BinQueue Initialize(void)
{
    BinQueue H;
    int i;

    H = malloc(sizeof(struct Collection));
    if (H == NULL)
    {
        printf("Out of space!!!");
    }

    H->CurrentSize = 0;
    for (i = 0; i < MaxTrees; i++)
    {
        H->TheTrees[i] = NULL;
    }

    return H;
}

static void DestroyTree(BinTree T)
{
    if (T != NULL)
    {
        /* 后序遍历释放所有节点 */
        DestroyTree(T->LeftChild);
        DestroyTree(T->NextSibling);
        free(T);
    }
}

/* 没有 free(H) */
/* 为了兼容 MakeEmpty */
void Destroy(BinQueue H)
{
    int i;

    for (i = 0; i < MaxTrees; i++)
    {
        DestroyTree(H->TheTrees[i]);
    }
}

BinQueue MakeEmpty(BinQueue H)
{
    int i;

    Destroy(H);
    for (i = 0; i < MaxTrees; i++)
    {
        H->TheTrees[i] = NULL;
    }

    H->CurrentSize = 0;

    return H;
}

/* Not optimized for O(1) amortized performance */
BinQueue Insert(ElementType Item, BinQueue H)
{
    BinTree NewNode;
    BinQueue OneItem;

    NewNode = malloc(sizeof(struct BinNode));
    if (NewNode == NULL)
    {
        printf("Out of space!!!");
    }
    NewNode->LeftChild = NewNode->NextSibling = NULL;
    NewNode->Element = Item;

    OneItem = Initialize();
    OneItem->CurrentSize = 1;
    OneItem->TheTrees[0] = NewNode;

    return Merge(H, OneItem);
}

/* 删掉之后 , 剩余数据仍然保留在 H  */
ElementType DeleteMin(BinQueue H)
{
    int i, j;
    int MinTree; /* The tree with the minimum item */
    BinQueue DeletedQueue;
    Position DeletedTree, OldRoot;
    ElementType MinItem;

    if (IsEmpty(H))
    {
        printf("Empty binomial queue");
        return -Infinity;
    }

    /* !!! */
    /* MinItem 直接初始化为一个很大的值 */
    /* 其实多多少少是有点不安全的 */
    /* 更何况宏定义的 Infinity==30000L 不是 ElementType 数据类型的最大值 */
    /* 万一队列中最小值为 30001 ( 这是有可能的 ) , 那程序就有问题了 */
    /* 保险做法应该随机初始化队列中的某一个根值 */
    /* 不过我懒得改了 */
    MinItem = Infinity;

    for (i = 0; i < MaxTrees; i++)
    {
        if (H->TheTrees[i] &&
            H->TheTrees[i]->Element < MinItem)
        {
            /* Update minimum */
            MinItem = H->TheTrees[i]->Element;
            MinTree = i;
        }
    }

    /* 根节点是没有 NextSibling 的 */
    /* 所以记录一个 LeftChild 即可 free(root) */
    DeletedTree = H->TheTrees[MinTree];
    OldRoot = DeletedTree;
    DeletedTree = DeletedTree->LeftChild;
    free(OldRoot);

    DeletedQueue = Initialize();
    DeletedQueue->CurrentSize = (1 << MinTree) - 1; //某棵树的元素减1
    for (j = MinTree - 1; j >= 0; j--)
    {
        // H->TheTrees[MinTree] 中有 MinTree 个子树
        DeletedQueue->TheTrees[j] = DeletedTree;
        DeletedTree = DeletedTree->NextSibling;
        DeletedQueue->TheTrees[j]->NextSibling = NULL; //根节点是没有 NextSibling 的
    }

    H->TheTrees[MinTree] = NULL;
    H->CurrentSize -= DeletedQueue->CurrentSize + 1;

    Merge(H, DeletedQueue);

    return MinItem;
}

ElementType FindMin(BinQueue H)
{
    int i;
    ElementType MinItem;

    if (IsEmpty(H))
    {
        printf("Empty binomial queue");
        return 0;
    }

    /* !!! */
    /* MinItem 直接初始化为一个很大的值 */
    /* 其实多多少少是有点不安全的 */
    /* 更何况宏定义的 Infinity==30000L 不是 ElementType 数据类型的最大值 */
    /* 万一队列中最小值为 30001 ( 这是有可能的 ) , 那程序就有问题了 */
    /* 保险做法应该随机初始化队列中的某一个根值 */
    /* 不过我懒得改了 */
    MinItem = Infinity;

    for (i = 0; i < MaxTrees; i++)
    {
        if (H->TheTrees[i] &&
            H->TheTrees[i]->Element < MinItem)
        {
            MinItem = H->TheTrees[i]->Element;
        }
    }

    return MinItem;
}

int IsEmpty(BinQueue H)
{
    return H->CurrentSize == 0;
}

int IsFull(BinQueue H)
{
    return H->CurrentSize == Capacity;
}

BinTree CombineTrees(BinTree T1, BinTree T2)
{
    /* 保证第一个参数的根小于第二个参数的根 */
    if (T1->Element > T2->Element)
    {
        return CombineTrees(T2, T1);
    }

    T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;
    return T1;
}

/* Merge two binomial queues */
/* Not optimized for early termination */
/* H1 contains merged result */
BinQueue Merge(BinQueue H1, BinQueue H2)
{
    BinTree T1, T2;
    BinTree Carry = NULL; //上一步合成的树
    int i;                //目前访问的秩为 i 的树
    int j;                //记录循环结束条件

    /* 两个队列的总大小不能超过一个队列的最大容纳量 */
    /* 不然很明显，不能合并到一个队列 */
    if (H1->CurrentSize + H2->CurrentSize > Capacity)
    {
        printf("Merge would exceed capacity");
    }

    H1->CurrentSize += H2->CurrentSize;

    for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
    {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];

        /* 以 2 进制的模式来表示 H1 H2 以及 i-1 合成之后含秩为 i 的树的情况 */
        /* 即 T1 T2 Carry 是否存在 */
        switch (!!T1 + 2 * !!T2 + 4 * !!Carry) // (!!T1) 为了判断 T1 是否为空 , 空返回 0 , 否则返回 1
        {
        case 0: /* No trees */
        case 1: /* Only H1 */
            break;
        case 2: /* Only H2 */
            H1->TheTrees[i] = T2;
            H2->TheTrees[i] = NULL;
            break;
        case 4: /* Only Carry */
            H1->TheTrees[i] = Carry;
            Carry = NULL;
            break;
        case 3: /* H1 and H2 */
            Carry = CombineTrees(T1, T2);
            H1->TheTrees[i] = H2->TheTrees[i] = NULL;
            break;
        case 5: /* H1 and Carry */
            Carry = CombineTrees(T1, Carry);
            H1->TheTrees[i] = NULL;
            break;
        case 6: /* H2 and Carry */
            Carry = CombineTrees(T2, Carry);
            H2->TheTrees[i] = NULL;
            break;
        case 7: /* All three */
            H1->TheTrees[i] = Carry;
            Carry = CombineTrees(T1, T2);
            H2->TheTrees[i] = NULL;
            break;
        }
    }

    /* H2 未释放 */
    return H1;
}
