#include <stdio.h>
#include <stdlib.h>
#include "topsort_queue.h"

int main()
{
    /* topsort */

    // // test1
    // AdjList L = InitializeList(6);
    // AddEdge(5, 2, 1, L);
    // AddEdge(5, 0, 1, L);
    // AddEdge(4, 0, 1, L);
    // AddEdge(4, 1, 1, L);
    // AddEdge(2, 3, 1, L);
    // AddEdge(3, 1, 1, L);
    // // check

    // // test2
    // AdjList L = InitializeList(7);
    // AddEdge(2, 5, 1, L);
    // AddEdge(6, 5, 1, L);
    // AddEdge(3, 2, 1, L);
    // AddEdge(0, 1, 1, L);
    // AddEdge(3, 6, 1, L);
    // AddEdge(4, 3, 1, L);
    // AddEdge(1, 4, 1, L);
    // // check

    // test3
    AdjList L = InitializeList(7);

    AddEdge(1, 2, WEIGHTIGNORE, L);
    AddEdge(1, 3, WEIGHTIGNORE, L);
    AddEdge(1, 4, WEIGHTIGNORE, L);
    AddEdge(2, 4, WEIGHTIGNORE, L);
    AddEdge(2, 5, WEIGHTIGNORE, L);
    AddEdge(3, 6, WEIGHTIGNORE, L);
    AddEdge(4, 3, WEIGHTIGNORE, L);
    AddEdge(4, 0, WEIGHTIGNORE, L);
    AddEdge(4, 6, WEIGHTIGNORE, L);
    AddEdge(5, 4, WEIGHTIGNORE, L);
    AddEdge(5, 0, WEIGHTIGNORE, L);
    AddEdge(0, 6, WEIGHTIGNORE, L);

    VertexValueType *result = TopSort(L);

    for (int i = 0; i < L->ListSize; i++)
    {
        printf("%d ", result[i]);
    }

    free(result);

    return 0;
}