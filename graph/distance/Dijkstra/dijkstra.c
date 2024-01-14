#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"

#define KNOWN (1)
#define UNKNOWN (0)

static PathInfoTable InitPathInfoTable(VertexValueType Start, int NumberofVex)
{
    PathInfoTable T = malloc(sizeof(struct PathEntry) * NumberofVex);
    if (T == NULL)
    {
        printf("Out of space!");
        return NULL;
    }

    for (int i = 0; i < NumberofVex; i++)
    {
        T[i].Known = UNKNOWN;
        T[i].Dist = INFINITY;
        T[i].Last = NOTAVERTEX;
    }
    T[Start].Dist = 0;

    return T;
}

PathInfoTable Dijkstra(AdjList L, VertexValueType Start)
{
    VertexValueType v, w;
    int tempmin;
    AdjCell tempAdjcell;
    PathInfoTable T = InitPathInfoTable(Start, L->ListSize);

    if (L->ListSize == 0)
    {
        /* nonsense */
        return NULL;
    }

    while (1)
    {
        /* 1. */
        /* 找到此时的 Dist_min , 记为点 v */
        /* 等价笔记中 v = smallest unknown distance vertex; 部分 */
        v = NOTAVERTEX;
        tempmin = INFINITY;

        for (int i = 0; i < L->ListSize; i++)
        {
            if ((T[i].Known == UNKNOWN) && T[i].Dist < tempmin)
            {
                tempmin = T[i].Dist;
                v = i;
            }
        }
        if (v == NOTAVERTEX)
        {
            break; // 没找到则结束算法
        }

        /* 2. */
        T[v].Known = KNOWN;

        /* 3. */
        /* 为 v 邻接的所有点更新 */
        tempAdjcell = L->TheLists[v]->next;
        while (tempAdjcell != NULL)
        {
            if ((T[tempAdjcell->vexValue].Known == UNKNOWN) && (T[tempAdjcell->vexValue].Dist > T[v].Dist + tempAdjcell->weight))
            {
                T[tempAdjcell->vexValue].Dist = T[v].Dist + tempAdjcell->weight;
                T[tempAdjcell->vexValue].Last = v;
            }

            tempAdjcell = tempAdjcell->next;
        }
    }

    return T;
}