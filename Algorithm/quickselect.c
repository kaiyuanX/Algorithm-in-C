typedef int ElementType;
#define Cutoff (3)

/* Places the kth smallest element in the kth position */
/* Because arrays start at 0, this will be index k-1 */
/* 某些函数的实现详见 quicksort */
void Qselect(ElementType A[], int k, int Left, int Right)
{
    int i, j;
    ElementType Pivot;

    if (Left + Cutoff <= Right)
    {
        Pivot = Median3(A, Left, Right);
        i = Left;
        j = Right - 1;

        for (;;)
        {
            while (A[++i] < Pivot)
            {
            }
            while (A[--j] > Pivot)
            {
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

        if (k <= i)
        {
            Qselect(A, k, Left, i - 1);
        }
        else if (k > i + 1)
        {
            Qselect(A, k, i + 1, Right);
        }
    }
    else /* Do an insertion sort on the subarray */
    {
        InsertionSort(A + Left, Right - Left + 1);
    }
}
/* END */