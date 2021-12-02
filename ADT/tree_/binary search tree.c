#include "binary search tree.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }

    return NULL;
}

/* 返回 X 所在位置；或 NULL 当 X 不在树上时 */
Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        return NULL;
    }

    if (X < T->Element)
    {
        return Find(X, T->Left);
    }
    else if (X > T->Element)
    {
        return Find(X, T->Right);
    }
    else
    {
        /* 即 X == T->Element */
        return T;
    }
}

/* 递归找 Min */
Position FindMin(SearchTree T)
{
    /* 有一个树是否为空的判断总是好的 */
    if (T == NULL)
    {
        return NULL;
    }
    else if (T->Left == NULL)
    {
        return T;
    }
    else
    {
        return FindMin(T->Left);
    }
}

/* 非递归找 Max */
Position FindMax(SearchTree T)
{
    if (T != NULL)
    {
        /* 循环结束后 T->right == NULL */
        while (T->Right != NULL)
        {
            T = T->Right;
        }
    }

    return T;
}

/* 递归插入 */
/* 因为我没有创建初始化函数 */
/* 所以这个函数一定程度上还有类似初始化的作用 */
/* 以及正常插入时，返回值将用于存储之前信息 */
/* 所以为了这个特性，返回值时必须的 */
SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct TreeNode));
        if (T == NULL)
        {
            printf("Out of space!!!");
        }
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
    }
    /* Else X is in the tree already; we'll do nothing */

    return T; /* Do not forget this line!! */
}

/* 具体的算法原理这里不做讲解 */
SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;

    if (T == NULL)
    {
        printf("Element not found");
    }
    else if (X < T->Element) /* Go left */
    {
        T->Left = Delete(X, T->Left);
    }
    else if (X > T->Element) /* Go right */
    {
        T->Right = Delete(X, T->Right);
    }
    else if (T->Left && T->Right) /* Found element to be deleted     Two children */
    {
        /* Replace with smallest in right subtree */
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else /* One or zero children */
    {
        TmpCell = T;
        if (T->Left == NULL)
        {
            T = T->Right;
        }
        else if (T->Right == NULL)
        {
            T = T->Left;
        }
        free(TmpCell);
    }

    return T;
}

ElementType Retrieve(Position P)
{
    if (P != NULL)
    {
        return P->Element;
    }

    /* 用个 -1 表 P 无效 */
    return -1;
}
