#include <stdio.h>
#include <stdlib.h>
#include "adj.h"

AdjList InitializeList(int NumberofVex)
{
    AdjList L;
    L = malloc(sizeof(struct Adjlist));
    if (L == NULL)
    {
        printf("Out of space!!!");
        return NULL;
    }

    L->ListSize = NumberofVex;

    L->TheLists = malloc(sizeof(AdjCell) * NumberofVex);
    if (L->TheLists == NULL)
    {
        printf("Out of space!!!");
        return NULL;
    }

    for (int i = 0; i < L->ListSize; i++)
    {
        /* L->TheLists[i] 等价 (L->TheLists)[i] */
        L->TheLists[i] = malloc(sizeof(struct AdjNode));
        if (L->TheLists[i] == NULL)
        {
            printf("Out of space!!!");
            return NULL;
        }
        else
        {
            L->TheLists[i]->next = NULL;
        }
    }

    return L;
}

void AddEdge(VertexValueType v, VertexValueType w, EdgeWeight weight, AdjList L)
{
    //头插
    //不判断是否有重复的边

    AdjCell temp = NULL;

    temp = malloc(sizeof(struct AdjNode));
    if (temp == NULL)
    {
        printf("Out of space!!!");
        return;
    }
    temp->vexValue = w;
    temp->weight = weight;

    if (L->TheLists[v]->next == NULL)
    {
        L->TheLists[v]->next = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = L->TheLists[v]->next;
        L->TheLists[v]->next = temp;
    }
}

EdgeNode GenerateUndirectedEdge(VertexValueType v1, VertexValueType v2, EdgeWeight weiht)
{
    EdgeNode E = malloc(sizeof(struct EdgeEntry));

    /* 因为无向 */
    /* 我们约定 v1 < v2 */
    if (v1 > v2)
    {
        VertexValueType vtemp = v1;
        v1 = v2;
        v2 = vtemp;
    }

    E->v1 = v1;
    E->v2 = v2;
    E->weight = weiht;

    return E;
}

EdgeList GetEdgesFromUndirectedAdjList(AdjList L)
{
    /* 我直接犯贱的预定一个关于 EdgeEntry 的数组 */
    /* 大小为 v^2 */
}
