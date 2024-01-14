/* Bellman–Ford */
/* 无优化 */
/* 邻接表 */

#include "adj.h"

#ifndef _BF_h
#define _BF_h

#define INFINITY (1000) // (DistType_MAX)INT_MAX
#define NOTAVERTEX (-1)

int *BellmanFord(AdjList L, VertexValueType Start);

#endif