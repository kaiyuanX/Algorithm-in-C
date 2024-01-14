/* 队列实现拓扑排序 */
/* 邻接表中还记录了权值 */
/* 但有无权值似乎对我的拓扑排序没有影响 */

#include "adj.h"

#ifndef _Topsort_h
#define _Topsort_h
//

// 将排序结果记录在一个数组中返回
// remember to free(sortResult)
VertexValueType *TopSort(AdjList L);

//
#endif