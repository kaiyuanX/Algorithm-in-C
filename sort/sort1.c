#include <stdlib.h>
typedef int ElementType;

void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* insertion sort */
void InsertionSort(ElementType A[], int N)
{
    int j, P;
    ElementType Tmp;

    for (P = 1; P < N; P++)
    {
        Tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > Tmp; j--)
        {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}

/* Shellsort */
//
/* begin */
/* 1. 希尔增量序列实现希尔排序 */
void Shellsort(ElementType A[], int N)
{
    int i, j, Increment;
    ElementType Tmp;

    /* 排序间隔从 N/2 到 1 */
    for (Increment = N / 2; Increment > 0; Increment /= 2)
    {
        /* 这里便是你熟悉的插入排序的思想 */
        for (i = Increment; i < N; i++)
        {
            Tmp = A[i];
            for (j = i; j >= Increment; j -= Increment)
            {
                if (Tmp < A[j - Increment])
                {
                    A[j] = A[j - Increment];
                }
                else
                {
                    break;
                }
            }
            A[j] = Tmp;
        }
    }
}
/* 2. Sedgewick 增量序列实现希尔排序 */
void Shellsort_Sedgewick(ElementType A[], int N)
{
    int Si, i, j, Increment;
    ElementType Tmp;

    /* 这里 Sedgewick 增量只列出了一部分 , 最大间隔只有 929 , 你应该根据你自己的需求添加 929 之后的间隔 */
    /* 这里多一个 0 是为了给出一个排序截止信号 */
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for (Si = 0; Sedgewick[Si] >= N; Si++)
    {
        /* 这个循环截断多余的大的间隔，因为间隔的值起码不能大于待判定数组元素的个数吧 */
        ;
    }

    for (Increment = Sedgewick[Si]; Increment > 0; Increment = Sedgewick[++Si])
    {
        for (i = Increment; i < N; i++)
        {
            Tmp = A[i];
            for (j = i; j >= Increment && A[j - Increment] > Tmp; j -= Increment)
            {
                A[j] = A[j - Increment];
            }
            A[j] = Tmp;
        }
    }
}
/* end */

/* quicksort */
//
/* begin */
/* 1. 三值的判断与分配 */
/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */
ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;

    /* 前两个 if 之后 , 成功赋值 A[Left] 为最小 */
    /* 最后一个 if 之后 , A[Right] 最大 , A[Center] 中是 Pivot */
    if (A[Left] > A[Center])
    {
        Swap(&A[Left], &A[Center]);
    }
    if (A[Left] > A[Right])
    {
        Swap(&A[Left], &A[Right]);
    }
    if (A[Center] > A[Right])
    {
        Swap(&A[Center], &A[Right]);
    }

    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

    Swap(&A[Center], &A[Right - 1]); /* Hide pivot */

    return A[Right - 1]; /* Return pivot */
}

/* 设置截止范围 */
#define Cutoff (10)

/* 2. 核心递归 */
/* 为 Right - Left + 1 个元素排序 */
void Qsort(ElementType A[], int Left, int Right)
{
    int i, j;
    ElementType Pivot;

    if (Left + Cutoff <= Right) /* Cutoff < Right - Left + 1 */
    {
        Pivot = Median3(A, Left, Right);
        i = Left;
        j = Right - 1;

        for (;;)
        {
            /* 我们的分割策略是等于时也停止 */
            while (A[++i] < Pivot)
            {
                /* 结束循环后 A[i] >= Pivot */
            }
            while (A[--j] > Pivot)
            {
                /* 结束循环后 A[j] <= Pivot */
            }
            if (i < j)
            {
                Swap(&A[i], &A[j]);
            }
            else
            {
                break;
            }
        }

        Swap(&A[i], &A[Right - 1]); /* Restore pivot */

        Qsort(A, Left, i - 1);
        Qsort(A, i + 1, Right);
    }
    else /* Do an insertion sort on the subarray */
    {
        InsertionSort(A + Left, Right - Left + 1);
    }
}

/* 3. 驱动程序 */
void Quicksort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}

/* This code doesn't work */
/*
    如果 A[i] = A[j] = Pivot , 那么就会陷入无限循环

    i = Left + 1;
    j = Right - 2;
    for (;;)
    {
        while (A[i] < Pivot)
            i++;
        while (A[j] > Pivot)
            j--;
        if (i < j)
            Swap(&A[i], &A[j]);
        else
            break;
    }
*/

/* end */
