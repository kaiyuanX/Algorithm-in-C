#include "binheap.h"
#include <stdio.h>
#include <stdlib.h>

#define MinPQSize (10)
#define MinData (-32767)

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;

    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL)
    {
        printf("Out of space!!!");
    }

    /* Allocate the array plus one extra for sentinel */
    /* 因为我们下标从 0 开始，所以多申请一个数据位置空置 */
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL)
    {
        printf("Out of space!!!");
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; //关系到 insert 操作 ,  H->Elements[0]一定保证小于等于每一个可能的插入元素

    return H;
}

void MakeEmpty(PriorityQueue H)
{
    H->Size = 0;
}

/* H->Element[0] is a sentinel */
void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H))
    {
        printf("Priority queue is full");
        return;
    }

    /* H->Element[0] 赋值为 ElementType 类型的最小值 */
    /* 所以该循环结束后最差 i 为 1 */
    /* 当空穴在 i 时 , 它的父亲就是 i / 2 , 这是一个非常好的性质 */
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H))
    {
        printf("Priority queue is empty");
        return H->Elements[0];
    }

    /* 保存堆中最小元素和最后一个元素 , 再 H->Size 更新 */
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    /* 直到 i 没有儿子时结束循环 */
    /* 也可能通过 break 结束循环 */
    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        /* Find smaller child */
        Child = i * 2; // Child 为左儿子
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
        {
            /* 如果 i 有右儿子且 < 左儿子 */
            Child++; // Child 为右儿子
        }

        /* Percolate one level */
        if (LastElement > H->Elements[Child])
        {
            H->Elements[i] = H->Elements[Child];
        }
        else
        {
            break;
        }
    }
    H->Elements[i] = LastElement;
    
    return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
    if (!IsEmpty(H))
    {
        return H->Elements[1];
    }
    printf("Priority Queue is Empty");
    return H->Elements[0];
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
    return H->Size == H->Capacity;
}

void Destroy(PriorityQueue H)
{
    free(H->Elements);
    free(H);
}
