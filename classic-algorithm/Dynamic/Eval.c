/* 求递推关系 */
/* C(n) = (2 / n) * ( C(0) + C(1) + ... C(n-1)) + n */

#include <stdio.h>
#include <stdlib.h>

/* 递归 */
double Eval(int N)
{
    int i;
    double Sum;

    if (N == 0)
        return 1.0;
    else
    {
        Sum = 0.0;
        for (i = 0; i < N; i++)
            Sum += Eval(i);
        return 2.0 * Sum / N + N;
    }
}

/* 动态规划 O(N平方) */
double Eval(int N)
{
    int i, j;
    double Sum, Answer;
    double *C;

    C = malloc(sizeof(double) * (N + 1));
    if (C == NULL)
    {
        printf("Out of space!!!");
        return 0;
    }

    C[0] = 1.0;
    for (i = 1; i <= N; i++)
    {
        Sum = 0.0;
        for (j = 0; j < i; j++)
        {
            Sum += C[j];
        }
        C[i] = 2.0 * Sum / i + i;
    }

    Answer = C[N];
    free(C);

    return Answer;
}

/* 动态规划 O(N) */
double Eval_(int N)
{
    int i, j;
    double Sum, Answer;
    double *C;

    C = malloc(sizeof(double) * (N + 1));
    if (C == NULL)
    {
        printf("Out of space!!!");
        return 0;
    }

    C[0] = 1.0;
    Sum = C[0];
    for (i = 1; i <= N; i++)
    {
        C[i] = 2 * Sum / i + i;
        Sum += C[i];
    }

    Answer = C[N];
    free(C);

    return Answer;
}