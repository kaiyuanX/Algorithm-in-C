#include <stdio.h>
#include "kruskal.h"
#include <stdlib.h>

int main()
{
    /* test1 */
    struct EdgeEntry test[12] = {{1, 3, 4}, {3, 6, 5}, {3, 4, 2}, {1, 4, 1}, {4, 6, 8}, {1, 2, 2}, {2, 4, 3}, {4, 7, 4}, {6, 7, 1}, {4, 5, 7}, {2, 5, 10}, {5, 7, 6}};

    Edges result = Kruskal(test, 12, 7);

    for (int i = 0; i < 6; i++)
    {
        printf("%d %d %d\n", result[i].v1, result[i].v2, result[i].weight);
    }

    free(result);
    /* check */

    return 0;
}