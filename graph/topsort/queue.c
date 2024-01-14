#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct QueueRecord
{
    int Capacity;
    int Size;

    int Front;
    int Rear;

    ElementType *Array;
};

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements)
{
    Queue Q;

    Q = malloc(sizeof(struct QueueRecord));
    if (Q == NULL)
    {
        printf("Out of space!!!");
    }

    Q->Array = malloc(sizeof(ElementType) * MaxElements);
    if (Q->Array == NULL)
    {
        printf("Out of space!!!");
    }

    Q->Capacity = MaxElements;
    MakeEmpty(Q);

    return Q;
}

void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

void DisposeQueue(Queue Q)
{
    if (Q != NULL)
    {
        free(Q->Array);
        free(Q);
    }
}

/* Value自增 */
/* 如果当前为 Capacity-1 返回 0 */
/* 相当于 (++Value) % Capacity */
static int Succ(int Value, Queue Q)
{
    if (++Value == Q->Capacity)
    {
        Value = 0;
    }
    return Value;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q))
    {
        printf("Full queue");
    }
    else
    {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

void Dequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Empty queue");
    }
    else
    {
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

ElementType Front(Queue Q)
{
    if (!IsEmpty(Q))
    {
        return Q->Array[Q->Front];
    }
    else
    {
        printf("Empty queue");
        return 0;
    }
}

ElementType FrontAndDequeue(Queue Q)
{
    ElementType X = 0;

    if (IsEmpty(Q))
    {
        printf("Empty queue");
    }
    else
    {
        Q->Size--;
        X = Q->Array[Q->Front];
        Q->Front = Succ(Q->Front, Q);
    }
    
    return X;
}
