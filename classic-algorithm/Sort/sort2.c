#include <stdlib.h>
typedef int ElementType;

/* buketsort */
void Bucketsort(int *unsorted, int N, int maxNumber)
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

/* radixsort */
//
/* begin */
/* 1. 辅助函数，求数据的最大位数 */
int maxbit(int data[], int n)
{
    /* 先求出最大数 */
    int maxData = data[0];
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
        {
            maxData = data[i];
        }
    }

    /* 再求位数 */
    int count = 1;
    while (1)
    {
        if ((maxData = maxData / 10) == 0)
        {
            break;
        }
        count++;
    }

    return count;
}

/* 2. 主程序 */
void Radixsort(int data[], int n)
{
    int i, j, k;
    int *tmpdata = malloc(sizeof(int) * n);
    int *bucket = malloc(sizeof(int) * 10); //计数器

    int d = maxbit(data, n);

    /* 最大元素有 d 位 , 进行 d 次排序 */
    /* i = x 的循环结束后 , 元素的第 x 位被成功排序 */
    int radix = 1;
    for (i = 1; i <= d; i++)
    {
        /* 每次分配前清空计数器 */
        for (j = 0; j < 10; j++)
        {
            bucket[j] = 0;
        }

        /* 把数分配到桶中*/
        for (j = 0; j < n; j++)
        {
            /* k 为 data[j] 从右往左第 i 位上的数 */
            k = (data[j] / radix) % 10;
            bucket[k]++;
        }

        /* 记录第 x 位相同的元素在第 x 位排序后 , 这类元素在数组的末位置 */
        /* 为下面循环的分配做铺垫 */
        /* buket[9] 在循环之后总是为 n */
        for (j = 1; j < 10; j++)
        {
            bucket[j] = bucket[j - 1] + bucket[j];
        }

        /* 依桶中的信息为数据排序并存储到 tmpdata 中 */
        for (j = n - 1; j >= 0; j--)
        {
            /* k 为 radix 位上的数 */
            k = (data[j] / radix) % 10;
            tmpdata[bucket[k] - 1] = data[j];
            bucket[k]--;
        }

        /* 将临时数组的内容复制到 data 中 */
        for (j = 0; j < n; j++)
        {
            data[j] = tmpdata[j];
        }

        radix = radix * 10;
    }

    free(tmpdata);
    free(bucket);
}
/* end */

/* heapsort */
//
/* begin */
/* 从数组下标 0 开始存储 */
/* 所以一个节点的左儿子自然就是这个表达式，读者自行验证 */
#define LeftChild(i) (2 * (i) + 1)

void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* 在有 N 个节点的堆中 , 下滤节点 A[i] */
void PercDown(ElementType A[], int i, int N)
{
    int Child;
    ElementType Tmp;

    for (Tmp = A[i]; LeftChild(i) < N; i = Child)
    {
        Child = LeftChild(i);
        if (Child != N - 1 && A[Child + 1] > A[Child])
        {
            /* 如果 i 有左儿子且大于右儿子，那么从右儿子的方向下滤 */
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
    /* 至于它的思想已在堆那一章分析过了 */
    for (i = N / 2; i >= 0; i--)
    {
        PercDown(A, i, N);
    }

    /* DeleteMax */
    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]); /* DeleteMax */
        PercDown(A, 0, i);
    }
}
/* end */

/* mergesort */
//
/* begin */
/* 1. 合并两个数组 */
/*
    Lpos LeftEnd
    Rpos RightEnd
*/
/* 分别记录 */
/* 第一个数组的起始和终点 */
/* 第二个数组的起始和终点 */
void Merge(ElementType A[], ElementType TmpArray[],
           int Lpos, int Rpos, int RightEnd)
{

    int LeftEnd;
    LeftEnd = Rpos - 1;

    /* NumElements 本次排序的元素总个数 */
    /* TmpPos 临时数组当前的填充位置 */
    int i, NumElements, TmpPos;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    /* 循环结束，要么 Lpos > LeftEnd，要么 Rpos > RightEnd */
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

/* 2. */
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

/* 3. 驱动程序 */
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
/* end */