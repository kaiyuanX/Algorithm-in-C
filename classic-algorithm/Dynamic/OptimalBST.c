/* 最优二叉查找树 ( 附中序遍历 ) */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX INT_MAX

/* num排序个数 p概率 c期望 r根 */
void OptimalBST(int num, double *p, double **c, int **r)
{
    int d, i, j, k, s, kmin;
    double temp, sum;

    /* 主表和根表的初始化 */
    for (i = 1; i < num + 1; i++)
    {
        c[i][i - 1] = 0;
        c[i][i] = p[i];
        r[i][i] = i;
    }

    // c[num + 1][num] = 0;  ????

    /* d+1 整合元素的个数 */
    for (d = 1; d <= num - 1; d++)
    {
        /* i 为 left , j 为 right */
        for (i = 1; i <= num - d; i++)
        {
            j = i + d;

            temp = MAX;

            /* 找最优根 获取Cleft,i-1 + Ci+1,right */
            for (k = i; k <= j; k++)
            {
                if (c[i][k - 1] + c[k + 1][j] < temp)
                {
                    temp = c[i][k - 1] + c[k + 1][j];
                    kmin = k;
                }
            }

            r[i][j] = kmin; //记录最优根

            sum = p[i];
            for (s = i + 1; s <= j; s++)
            {
                sum += p[s];
            }

            c[i][j] = temp + sum;
        }
    }
}

/* 采用递归方式实现最优根的输出，最优根都是保存在r[i][j]中的 */
void OptimalBSTPrint(int first, int last, int **r, int tabnum)
{
    int i;
    if (first == last)
    {
        for (i = 0; i < tabnum; i++)
        {
            printf("\t");
        }
        printf("%d\n", r[first][last]);
    }
    else if (first < last)
    {
        for (i = 0; i < tabnum; i++)
        {
            printf("\t");
        }
        printf("%d\n", r[first][last]);
        OptimalBSTPrint(first, r[first][last] - 1, r, tabnum + 1);
        OptimalBSTPrint(r[first][last] + 1, last, r, tabnum + 1);
    }
}
