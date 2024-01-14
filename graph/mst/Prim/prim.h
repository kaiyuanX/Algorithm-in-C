/* 没有优化的 dijkstra 为基础实现 prim */
/* 邻接表 */
/* 与 dijstra 的不同仅在 prim() 函数中 , 已标注 */
/* 1. dist 更新的条件以及更新的内容 */
/* 2. 如果希望 prim 返回生成树的所有边 , 应在 Find_Dist_min 时进行边的记录 ( 代码中并无具体实现，我太 TM 懒了 ) */

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

/* 程序顺利结束后，路径信息都存储在 T 中，返回 T */
/* 调用 prim() 的程序 free(T) */
PathInfoTable prim(AdjList L, VertexValueType Start);

//
#endif