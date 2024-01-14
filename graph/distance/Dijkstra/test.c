#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* test01 */
    AdjList L = InitializeList(7);
    AddEdge(1, 2, 2, L);
    AddEdge(3, 1, 4, L);
    AddEdge(4, 3, 2, L);
    AddEdge(1, 4, 1, L);
    AddEdge(2, 4, 3, L);
    AddEdge(4, 6, 8, L);
    AddEdge(3, 6, 5, L);
    AddEdge(2, 5, 10, L);
    AddEdge(4, 5, 2, L);
    AddEdge(4, 0, 4, L);
    AddEdge(5, 0, 6, L);
    AddEdge(0, 6, 1, L);

    PathInfoTable T = Dijkstra(L, 1);

    for (int i = 0; i < 7; i++)
    {
        printf("%d %d \n", T[i].Dist, T[i].Last);
    }

    /* 打印 1 到 w 的路径 */
    VertexValueType w = 1;
    do
    {
        printf("%d <-- ", w);
        w = T[w].Last;

    } while ((w != NOTAVERTEX));

    free(T);

    /* check */

    return 0;
}