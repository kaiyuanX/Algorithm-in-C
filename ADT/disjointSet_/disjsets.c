/* Disjoint set data structure */
/* All in one file because it's so short */

#include <stdio.h>

#define FastAlg
#define NumSets 128

/* disjset.h */
#ifndef _DisjSet_H

typedef int DisjSet[NumSets + 1]; //DisjSet s;   ==>   int s[NumSets + 1];
typedef int SetType;
typedef int ElementType;

void Initialize(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(ElementType X, DisjSet S);

#endif
/* END */

void Initialize(DisjSet S)
{
    int i;

    for (i = NumSets; i > 0; i--)
    {
        S[i] = 0;
    }
}

#ifdef SlowAlg

/* Assume Root1 and Root2 are roots */
/* union is a C keyword */
/* so this routine is named SetUnion */
/* 很一般的求并 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
    S[Root2] = Root1;
}

SetType Find(ElementType X, DisjSet S)
{
    if (S[X] <= 0)
        return X;
    else
        return Find(S[X], S);
}

#else

/* 路径压缩与按高度求并不完全兼容导致 */

/* 按秩求并 */
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
    if (S[X] <= 0)
    {
        return X;
    }
    else
    {
        return S[X] = Find(S[X], S);
    }
}

#endif
/* END */

int main()
{
    DisjSet S;
    int i, j, k, Set1, Set2;

    Initialize(S);
    j = k = 1;
    while (k <= 8)
    {
        j = 1;
        while (j < NumSets)
        {
            Set1 = Find(j, S);
            Set2 = Find(j + k, S);
            SetUnion(S, Set1, Set2);
            j += 2 * k;
        }
        k *= 2;
    }
    i = 1;
    for (i = 1; i <= NumSets; i++)
    {
        Set1 = Find(i, S);
        printf("%d**", Set1);
    }
    printf("\n");
    return 0;
}
