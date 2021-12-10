/* leftist heap */

typedef int ElementType;

#ifndef _LeftHeap_H
#define _LeftHeap_H
//

struct TreeNode;
typedef struct TreeNode *PriorityQueue;

/* Minimal set of priority queue operations */
/* Note that nodes will be shared among several leftist heaps after a merge */
/* the user must make sure to not use the old leftist heaps */
PriorityQueue Initialize(void);

int IsEmpty(PriorityQueue H);

/* 返回 Min */
ElementType FindMin(PriorityQueue H);

/* 返回合并后的根节点位置 */
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

/* 由于 Insert,Delete 用到了 Merge 操作 */
/* 为了使得 Insert,Delete 与 Merge 兼容 , 我们创建了这个宏 */
/* 插入  X  返回新的 H */
/* 删掉 Min 返回新的 H */
#define Insert(X, H) (H = Insert1((X), H))
#define DeleteMin(H) (H = DeleteMin1(H))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

//
#endif
