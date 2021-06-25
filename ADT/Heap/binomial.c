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
    BinTree TheTrees[MaxTrees]; //14
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
        DestroyTree(T->LeftChild);
        DestroyTree(T->NextSibling);
        free(T);
    }
}

// 无 free(H)
// 为了在 MakeEmpty 中使用
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

    MinItem = Infinity; //30000
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
        DeletedQueue->TheTrees[j]->NextSibling = NULL;
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

    MinItem = Infinity;
    for (i = 0; i < MaxTrees; i++)
    {
        if (H->TheTrees[i] &&
            H->TheTrees[i]->Element < MinItem)
            MinItem = H->TheTrees[i]->Element;
    }

    return MinItem;
}

int IsEmpty(BinQueue H)
{
    return H->CurrentSize == 0;
}

int IsFull(BinQueue H)
{
    // 2 的14次方
    return H->CurrentSize == Capacity;
}

BinTree CombineTrees(BinTree T1, BinTree T2)
{
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
    int i;                //访问每个数组
    int j;

    if (H1->CurrentSize + H2->CurrentSize > Capacity)
    {
        printf("Merge would exceed capacity");
    }

    H1->CurrentSize += H2->CurrentSize;
    for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
    {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];

        switch (!!T1 + 2 * !!T2 + 4 * !!Carry) // !!T1 == 1或0
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
    return H1;
}
