#include <stdio.h>
//递归求幂
//
//logN
#define IsEven(N) ((N) % 2 == 0)

long int Pow(long int X, unsigned int N)
{
    if (N == 0)
    {
        return 1;
    }
    if (N == 1)
    {
        return X;
    }
    if (IsEven(N))
    {
        return Pow(X * X, N / 2);
    }
    else
    {

        return Pow(X * X, N / 2) * X;
    }
}
