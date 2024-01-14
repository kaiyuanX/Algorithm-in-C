#include "disjsets.h"

void Initialize(DisjSet S)
{
    int i;

    for (i = NumSets; i >= 0; i--)
    {
        S[i] = -1;
    }
}

/* 按秩 (高度) 求并 */
/* 根元素的负值表该树的高 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
    if (S[Root2] < S[Root1]) /* Root2 is deeper set */
    {
        S[Root1] = Root2; /* Make Root2 new root */
    }
    else
    {
        if (S[Root1] == S[Root2]) /* Same height, */
        {
            S[Root1]--; /* so update */
        }
        S[Root2] = Root1;
    }
}

/* 路径压缩 */
SetType Find(ElementType X, DisjSet S)
{
    if (S[X] < 0)
    {
        return X;
    }
    else
    {
        return S[X] = Find(S[X], S);
    }
}
