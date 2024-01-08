/* Floyd-Warshall */
/* Compute All-Shortest Paths */

#include <stdio.h>

#define NotAVertex (-1)
typedef int TwoDimArray[4][4];

/* A[ ][ ] contains the adjacency matrix with A[ i ][ i ] presumed to be zero */
/* D[ ][ ] contains the values of the shortest path */
/* N is the number of vertices */

/* Actual path can be computed using Path[ ] */
/* A negative cycle exists iff D[ i ][ i ] is set to a negative value */
/* All arrays are indexed starting at 0 */

void AllPairs(TwoDimArray A, TwoDimArray D, TwoDimArray Path, int N)
{
    int i, j, k;

    /* Initialize D and Path */
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            D[i][j] = A[i][j];
            Path[i][j] = NotAVertex;
        }
    }

    /* Conider each vertex as an intermediate */
    /* 当 k 为中点时 , i j 的路径 */
    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    /* Update shortest path */
                    D[i][j] = D[i][k] + D[k][j];
                    /* k 记录了 i 到 j 最短路径所经过的中间顶点 */
                    Path[i][j] = k;
                }
            }
        }
    }
}