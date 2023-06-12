/* Compute optimal ordering of matrix multiplication */
/* O(N3次) */

#include <limits.h>
#include <stdio.h>

#define Infinity INT_MAX
#define MatrixCount (4) // 矩阵个数
typedef long int TwoDimArray[MatrixCount + 1][MatrixCount + 1];

/* C contains number of columns for each of the N matrices */
/* Minimum number of multiplications is left in M[ 1 ][ N ] */
/* Actual ordering is computed via another procedure using LastChange */
/* M and LastChange are indexed starting at 1, instead of 0 */
/* Note: Entries below main diagonals of M and LastChange are meaningless and uninitialized */

/* C[]:矩阵信息 , N:矩阵个数 , 矩阵 M[i][j] 存储的最少乘法次数 , 矩阵 LastChange[i][j] 追踪路径 */
/* 4 个矩阵 50*10 10*40 40*30 30*5 */
/* int C[] = {50, 10, 40, 30, 5}; */
/* 坐标 [0][j]&&[i][0] 没用 */
void OptMatrix(const int C[], int N, TwoDimArray M, TwoDimArray LastChange)
{
    int i, k, Left, Right;
    long ThisM;

    /* X 到 X 默认为 0 */
    for (Left = 1; Left <= N; Left++)
    {
        M[Left][Left] = 0;
    }

    for (k = 1; k < N; k++) /* k = Right - Left , k+1:子问题规模 */
    {
        for (Left = 1; Left <= N - k; Left++)
        {
            /* 第 Left 个矩阵到第 Right 个矩阵的信息 */
            Right = Left + k;
            M[Left][Right] = Infinity;

            /* 此循环后 , M[left][right] LastChange[left][right] 被成功赋值 */
            for (i = Left; i < Right; i++)
            {
                /* 将路径分为 A[left]A[left+1]...A[i] & A[i+1]A[i+2]...A[right] */
                ThisM = M[Left][i] + M[i + 1][Right] + C[Left - 1] * C[i] * C[Right];
                if (ThisM < M[Left][Right])
                {
                    /* Update min */
                    M[Left][Right] = ThisM;
                    LastChange[Left][Right] = i;
                }
            }
        }
    }
}
