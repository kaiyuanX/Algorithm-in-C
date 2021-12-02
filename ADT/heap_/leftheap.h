//
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

//返回 Min
ElementType FindMin(PriorityQueue H);

//返回 新的H
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

//插入  X  返回 新的H
//删掉 Min 返回 新的H
#define Insert(X, H) (H = Insert1((X), H))
#define DeleteMin(H) (H = DeleteMin1(H))

PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);
//
#endif
