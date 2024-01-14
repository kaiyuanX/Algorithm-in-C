/* 写不出来，今天别回去了 */

#include "kruskal.h"
#include "disjsets.h"
#include <stdlib.h>

/* buildheap */
//
/* begin */
/* 从数组下标 0 开始存储 */
/* 所以一个节点的左儿子自然就是这个表达式，读者自行验证 */
#define LeftChild(i) (2 * (i) + 1)

static void Swap(struct EdgeEntry *x, struct EdgeEntry *y)
{
    struct EdgeEntry temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* 在有 N 个节点的堆中 , 下滤节点 A[i] */
static void PercDown(struct EdgeEntry *A, int i, int N)
{
    int Child;
    struct EdgeEntry Tmp;

    for (Tmp = A[i]; LeftChild(i) < N; i = Child)
    {
        Child = LeftChild(i);
        if (Child != N - 1 && A[Child + 1].weight < A[Child].weight)
        {
            /* 如果 i 有左儿子且大于右儿子，那么从右儿子的方向下滤 */
            Child++;
        }
        if (Tmp.weight > A[Child].weight)
        {
            A[i] = A[Child];
        }
        else
        {
            break;
        }
    }
    A[i] = Tmp;
}

static void BuildHeap(struct EdgeEntry A[], int N)
{
    int i;

    /* BuildHeap */
    /* 至于它的思想已在堆那一章分析过了 */
    for (i = N / 2; i >= 0; i--)
    {
        PercDown(A, i, N);
    }

    // /* DeleteMax */
    // for (i = N - 1; i > 0; i--)
    // {
    //     Swap(&A[0], &A[i]); /* DeleteMax */
    //     PercDown(A, 0, i);
    // }
}

/* 从 N 个节点的堆中删除 */
static struct EdgeEntry DeleteMin(struct EdgeEntry A[], int N)
{
    Swap(&A[0], &A[N - 1]); /* DeleteMax */
    PercDown(A, 0, N - 2);
    return A[N - 1];
}
/* end */


/* Kruskal */
Edges Kruskal(Edges allE, int edgesNumber, int vertexNumber)
{
    struct EdgeEntry tempE;

    SetType s1, s2;
    DisjSet S;
    Initialize(S);

    Edges result = malloc(sizeof(struct EdgeEntry) * (vertexNumber - 1));

    BuildHeap(allE, edgesNumber);

    int i = 0;
    int acceptedEdges = 0;
    while (acceptedEdges < vertexNumber - 1)
    {
        tempE = DeleteMin(allE, edgesNumber - i);
        i++;
        s1 = Find(tempE.v1, S);
        s2 = Find(tempE.v2, S);
        if (s1 != s2)
        {
            result[acceptedEdges] = tempE;
            acceptedEdges++;
            SetUnion(S, s1, s2);
        }
    }

    return result;
}
/* end */