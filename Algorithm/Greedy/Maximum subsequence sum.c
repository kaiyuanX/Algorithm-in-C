#include <stdio.h>
//最大子序列
//
//递归
//N
int MaxSubsequenceSum(const int A[], int N)
{
    int ThisSum, MaxSum, j;

    ThisSum = MaxSum = 0;
    for (j = 0; j < N; j++)
    {
        ThisSum += A[j];

        if (ThisSum > MaxSum)
        {
            MaxSum = ThisSum;
        }
        else if (ThisSum < 0)
        {
            ThisSum = 0;
        }
    }
    return MaxSum;
}
//
//线性
//N*logN
static int Max3(int A, int B, int C)
{
    return A > B ? A > C ? A : C : B > C ? B
                                         : C;
}

static int MaxSubSum(const int A[], int Left, int Right)
{
    int MaxLeftSum, MaxRightSum;
    int MaxLeftBorderSum, MaxRightBorderSum;
    int LeftBorderSum, RightBorderSum;
    int Center, i;

    if (Left == Right) /* Base case */
    {
        if (A[Left] > 0)
        {
            return A[Left];
        }
        else
        {
            return 0;
        }
    }

    Center = (Left + Right) / 2;
    MaxLeftSum = MaxSubSum(A, Left, Center);
    MaxRightSum = MaxSubSum(A, Center + 1, Right);

    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for (i = Center; i >= Left; i--)
    {
        LeftBorderSum += A[i];
        if (LeftBorderSum > MaxLeftBorderSum)
        {
            MaxLeftBorderSum = LeftBorderSum;
        }
    }

    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for (i = Center + 1; i <= Right; i++)
    {
        RightBorderSum += A[i];
        if (RightBorderSum > MaxRightBorderSum)
        {
            MaxRightBorderSum = RightBorderSum;
        }
    }

    return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}



/* END */
