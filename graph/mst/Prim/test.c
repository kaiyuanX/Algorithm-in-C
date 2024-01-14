#include "prim.h"

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
    AddEdge(4, 5, 7, L);
    AddEdge(4, 0, 4, L);
    AddEdge(5, 0, 6, L);
    AddEdge(0, 6, 1, L);

    AddEdge(2, 1, 2, L);
    AddEdge(1, 3, 4, L);
    AddEdge(3, 4, 2, L);
    AddEdge(4, 1, 1, L);
    AddEdge(4, 2, 3, L);
    AddEdge(6, 4, 8, L);
    AddEdge(6, 3, 5, L);
    AddEdge(5, 2, 10, L);
    AddEdge(5, 4, 7, L);
    AddEdge(0, 4, 4, L);
    AddEdge(0, 5, 6, L);
    AddEdge(6, 0, 1, L);

    PathInfoTable T = prim(L, 1);

    for (int i = 0; i < 7; i++)
    {
        printf("%d %d \n", T[i].Dist, T[i].Last);
    }

    free(T);

    /* check */

    return 0;
}