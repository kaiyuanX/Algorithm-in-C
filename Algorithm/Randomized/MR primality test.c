/* Miller–Rabin primality test */

/* If Witness does not return 1, N is definitely composite */
/* Do this by computing ( A ^ i ) mod N and looking for non-trivial square roots of 1 along the way */
/* We are assuming very large numbers, so this is pseudocode */

/* IsPrime: Test if N >= 3 is prime using one value of A */
/* Repeat this procedure as many times as needed for desired error rate */

#include <stdio.h>
#include <stdlib.h>

typedef long HugeInt;

/* 返回的数 [Low , High] */
HugeInt RandInt(HugeInt Low, HugeInt High)
{
    return rand() % (High - Low + 1) + Low;
}

/* A 底数 ; i 指数 ; N 待判定数 */
/* 1 2 3 求幂过程 , 即 A^(N-1) */
HugeInt Witness(HugeInt A, HugeInt i, HugeInt N)
{
    HugeInt X, Y;

    if (i == 0)
    {
        return 1;
    }

    /* 1 */
    X = Witness(A, i / 2, N);

    if (X == 0) /* If N is recursively composite, stop */
    {
        return 0;
    }

    /* 2 */
    Y = (X * X) % N;

    /* N is not prime if we find a non-trivial root of 1 */
    /* Miller-Rabin 优化 */
    if (Y == 1 && X != 1 && X != N - 1)
    {
        return 0;
    }

    /* 3 */
    /* 为奇 */
    if (i % 2 != 0)
    {
        Y = (A * Y) % N;
    }

    return Y;
}

int IsPrime(HugeInt N)
{
    return Witness(RandInt(2, N - 2), N - 1, N) == 1;
}
/* END */