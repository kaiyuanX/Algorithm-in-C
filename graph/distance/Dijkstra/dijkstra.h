/* 没有优化的 dijkstra 求单源最短路径 */
/* 邻接表 */
/* 没有负边，该算法总能顺利完全 */

#include "adj.h"

#ifndef _Dijstra_h
#define _Dijstra_h
//

#define INFINITY (1000) // (DistType_MAX)INT_MAX
#define NOTAVERTEX (-1)

typedef int DistType;

struct PathEntry
{
    int Known;
    DistType Dist;
    VertexValueType Last;
};

typedef struct PathEntry *PathInfoTable;

/* 程序顺利结束后，路径信息都存储在 T 中 , 返回 T */
/* 调用 Dijkstra() 的程序 free(T) */
PathInfoTable Dijkstra(AdjList L, VertexValueType Start);

//
#endif