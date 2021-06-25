//数组实现队列
//
typedef int ElementType;

#ifndef _Queue_h
#define _Queue_h
//
//一个队列
//尾进首出
//Rear=Front-1为空
struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);

Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);

void Enqueue(ElementType X, Queue Q);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);
//
#endif