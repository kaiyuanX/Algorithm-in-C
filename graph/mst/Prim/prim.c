#include <stdlib.h>
#include <stdio.h>
#include "prim.h"

#define KNOWN (1)
#define UNKNOWN (0)

static PathInfoTable InitTable(VertexValueType Start, int NumberofVex)
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

PathInfoTable prim(AdjList L, VertexValueType Start)
{
    VertexValueType v, w;
    int tempmin;
    AdjCell tempAdjcell;
    PathInfoTable T = InitTable(Start, L->ListSize);

    if (L->ListSize == 0)
    {
        /* nonsense */
        return NULL;
    }

    while (1)
    {
        /* 求 min(V_{new},v) */
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

        T[v].Known = KNOWN;

        /* 为 v 邻接的所有点更新 */
        tempAdjcell = L->TheLists[v]->next;
        while (tempAdjcell != NULL)
        {
            // if ((T[tempAdjcell->vexValue].Known == UNKNOWN) && (T[tempAdjcell->vexValue].Dist > T[v].Dist + tempAdjcell->weight))
            if ((T[tempAdjcell->vexValue].Known == UNKNOWN) && (T[tempAdjcell->vexValue].Dist > tempAdjcell->weight)) // 不同于 dijstra 的地方
            {
                // T[tempAdjcell->vexValue].Dist = T[v].Dist + tempAdjcell->weight;
                T[tempAdjcell->vexValue].Dist = tempAdjcell->weight; // 不同于 dijstra 的地方
                T[tempAdjcell->vexValue].Last = v;
            }

            tempAdjcell = tempAdjcell->next;
        }
    }

    return T;
}