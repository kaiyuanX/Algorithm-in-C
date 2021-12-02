//binary heap
typedef int ElementType;

#ifndef _BinHeap_H
#define _BinHeap_H
//
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);

void Insert(ElementType X, PriorityQueue H);
//返回根元素
ElementType DeleteMin(PriorityQueue H);

ElementType FindMin(PriorityQueue H);

int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
//
#endif