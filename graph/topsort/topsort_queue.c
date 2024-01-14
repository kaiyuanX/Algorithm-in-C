#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "topsort_queue.h"

// Initialize indegree[]
static int *GetIndegreeFromAdj(AdjList L)
{
    int *indegree = malloc(sizeof(int) * L->ListSize);
    if (indegree == NULL)
    {
        printf("Out of space!!!");
        return NULL;
    }

    for (int i = 0; i < L->ListSize; i++)
    {
        indegree[i] = 0;
    }

    AdjCell temp;
    for (int i = 0; i < L->ListSize; i++)
    {
        temp = L->TheLists[i]->next;
        while (temp != NULL)
        {
            indegree[temp->vexValue]++;
            temp = temp->next;
        }
    }

    return indegree;
}

VertexValueType *TopSort(AdjList L)
{
    VertexValueType v;
    AdjCell temp;
    int counter = 0;
    VertexValueType *sortResult = malloc(sizeof(VertexValueType) * L->ListSize);

    int *indegree = GetIndegreeFromAdj(L);

    Queue Q;
    Q = CreateQueue(L->ListSize);

    /* 1. 获取第一批无入度的点 */
    for (int i = 0; i < L->ListSize; i++)
    {
        if (indegree[i] == 0)
        {
            Enqueue(i, Q);
        }
    }

    /* 2. 遍历所有点进行拓扑排序 */
    while (!IsEmpty(Q))
    {
        v = FrontAndDequeue(Q);
        sortResult[counter++] = v; // 出队一次 , counter 加 1

        temp = L->TheLists[v]->next;
        while (temp != NULL)
        {
            if (--indegree[temp->vexValue] == 0)
            {
                Enqueue(temp->vexValue, Q);
            }

            temp = temp->next;
        }
    }

    /* 3. 进行排序是否成功的判断 */
    if (counter != L->ListSize)
    {
        printf("Graph has a cycle!");
        return NULL;
    }

    DisposeQueue(Q);
    free(indegree);
    
    return sortResult;
}