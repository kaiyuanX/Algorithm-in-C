/* binomial queue */

typedef long ElementType;
#define Infinity (30000L)

#ifndef _BinHeap_H
#define _BinHeap_H
//

/* 宏定义队列所容纳树的棵树 */
/* 这里 MaxTrees==14 , 即意味着该队列最多存储 16383 个元素 */
#define MaxTrees (14)
#define Capacity (16383) // 2 的 14 次方 -1

struct BinNode;
typedef struct BinNode *BinTree;
struct Collection;
typedef struct Collection *BinQueue;

BinQueue Initialize(void);
void Destroy(BinQueue H);
BinQueue MakeEmpty(BinQueue H);

BinQueue Merge(BinQueue H1, BinQueue H2);
BinQueue Insert(ElementType Item, BinQueue H);

ElementType DeleteMin(BinQueue H);
ElementType FindMin(BinQueue H);

int IsEmpty(BinQueue H);
int IsFull(BinQueue H);

//
#endif
