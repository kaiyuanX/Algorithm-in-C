#include <stdlib.h>
typedef int ElementType;

/* buketsort */
void bucketsort(int *unsorted, int N, int maxNumber)
{
    int i, j;
    int *bucket = malloc(sizeof(int) * (maxNumber + 1));

    if (bucket != NULL)
    {
        for (i = 0; i < maxNumber + 1; i++)
        {
            bucket[i] = 0;
        }

        for (i = 0; i < N; i++)
        {
            bucket[unsorted[i]]++;
        }

        for (i = 0, j = 0; i < maxNumber + 1; i++)
        {
            while (bucket[i]--)
            {
                unsorted[j] = i;
                j++;
            }
        }

        free(bucket);
    }
}

/* heapsort */
//
//从数组下标 0 开始存储
#define LeftChild(i) (2 * (i) + 1)

void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// N 个元素 , 第 i+1 个节点下降 ( 数组中的元素 A[i] )
void PercDown(ElementType A[], int i, int N)
{
    int Child;
    ElementType Tmp;

    for (Tmp = A[i]; LeftChild(i) < N; i = Child)
    {
        Child = LeftChild(i);
        if (Child != N - 1 && A[Child + 1] > A[Child])
        {
            Child++;
        }
        if (Tmp < A[Child])
        {
            A[i] = A[Child];
        }
        else
        {
            break;
        }
    }
    A[i] = Tmp;
}

void Heapsort(ElementType A[], int N)
{
    int i;

    /* BuildHeap */
    for (i = N / 2; i >= 0; i--)
    {
        PercDown(A, i, N);
    }

    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]); /* DeleteMax */
        PercDown(A, 0, i);
    }
} 

/* mergesort */
//
void Merge(ElementType A[], ElementType TmpArray[],
           int Lpos, int Rpos, int RightEnd)
{
    //Lpos LeftEnd
    //Rpos RightEnd

    int LeftEnd;
    LeftEnd = Rpos - 1;

    // NumElements 本次排序的元素总个数
    // TmpPos 临时数组当前的填充位置
    int i, NumElements, TmpPos;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while (Lpos <= LeftEnd && Rpos <= RightEnd)
    {
        if (A[Lpos] <= A[Rpos])
        {
            TmpArray[TmpPos++] = A[Lpos++];
        }
        else
        {
            TmpArray[TmpPos++] = A[Rpos++];
        }
    }

    while (Lpos <= LeftEnd) /* Copy rest of first half */
    {
        TmpArray[TmpPos++] = A[Lpos++];
    }
    while (Rpos <= RightEnd) /* Copy rest of second half */
    {
        TmpArray[TmpPos++] = A[Rpos++];
    }

    /* Copy TmpArray back */
    for (i = 0; i < NumElements; i++, RightEnd--)
    {
        A[RightEnd] = TmpArray[RightEnd];
    }
}

void MSort(ElementType A[], ElementType TmpArray[],
           int Left, int Right)
{
    int Center;

    if (Left < Right)
    {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

void Mergesort(ElementType A[], int N)
{
    ElementType *TmpArray;

    TmpArray = malloc(N * sizeof(ElementType));
    if (TmpArray != NULL)
    {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
}
