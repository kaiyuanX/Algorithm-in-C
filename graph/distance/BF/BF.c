#include "BF.h"
#include <stdio.h>
#include <stdlib.h>

int *BellmanFord(AdjList L, VertexValueType Start)
{
    int n = L->ListSize;
    int *distance = malloc(sizeof(int) * n);

    // 初始化图
    for (int i = 0; i < n; i++)
    {
        if (i == Start)
        {
            distance[i] = 0;
        }
        else
        {
            distance[i] = INFINITY;
        }
    }

    AdjCell *es = L->TheLists;
    AdjCell tempAdjcell;

    // 主循环，松弛操作
    for (int i = 0; i < n - 1; i++)
    {
        for (int v = 0; v < n; v++)
        {
            tempAdjcell = es[v]->next;
            while (tempAdjcell != NULL)
            {
                if (distance[v] + tempAdjcell->weight < distance[tempAdjcell->vexValue])
                {
                    distance[tempAdjcell->vexValue] = distance[v] + tempAdjcell->weight;
                }
                tempAdjcell = tempAdjcell->next;
            }
        }
    }

    // 检查负圈
    for (int v = 0; v < n; v++)
    {
        tempAdjcell = es[v]->next;
        while (tempAdjcell != NULL)
        {
            if (distance[v] + tempAdjcell->weight < distance[tempAdjcell->vexValue])
            {
                printf("negative cycle");
            }
            tempAdjcell = tempAdjcell->next;
        }
    }

    return distance;
}
