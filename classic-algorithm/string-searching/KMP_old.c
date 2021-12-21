#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KMP_old.h"

/* 这个函数的时间复杂度为 O(m^2) */
/* 根据模式串 tstr , 计算 next 数组 , 字符串的起始位置从 0 开始 */
/* 核心 : 计算部分匹配值 */
static void Next(char tstr[], int next[])
{
    /* 两个指针不为空 */
    /* 否则没意义 */
    if ((tstr == 0) || (next == 0))
    {
        return;
    }

    /* 模式串的长度 */
    int tlen = strlen(tstr);

    /* 如果模式串的长度小于 3 , 无需计算 next 数组 , 直接返回特定值 */
    /* 理由：前缀后缀没有或不重要 */
    if (tlen == 0)
    {
        return;
    }
    else if (tlen == 1)
    {
        next[0] = -1;
        return;
    }
    else if (tlen == 2)
    {
        next[0] = -1;
        next[1] = 0;
        return;
    }

    next[0] = -1; // 位置 0 直接填入-1
    next[1] = 0;  // 位置 1 直接填入0

    /* next[ii] : tstr[0] ~ tstr[ii-1] 的部分匹配值 */
    char *p1 = malloc(sizeof(char) * tlen);
    char *p2 = malloc(sizeof(char) * tlen);

    /* ii 是 next[] 的下标 , 也是待分析子串的长度 */
    /* jj 遍历前缀后缀的长度 */
    int ii, jj;
    for (ii = 2; ii < tlen; ii++)
    {
        /* 记录最长公共前后缀的长度 */
        int maxlen = 0;

        /* 用一个循环，得到全部的前缀和后缀，并判断最长公共前后缀 */
        for (jj = 1; jj < ii; jj++)
        {
            memset(p1, 0, sizeof(p1));
            memset(p2, 0, sizeof(p2));

            strncpy(p1, tstr, jj);             // 取前缀
            strncpy(p2, (tstr + ii) - jj, jj); // 取后缀

            /* 判断前后缀是否相同，相同就记下 jj 的值 */
            if (strcmp(p1, p2) == 0)
            {
                maxlen = jj;
            }
        }

        next[ii] = maxlen;
    }
}

/* tstr 在 sstr 中进行匹配 */
/* 返回第一次匹配成功的位置 */
/* 失败返回 1 */
int KMP(char sstr[], char tstr[])
{
    /* sstr 和 tstr 都不为空 */
    if ((sstr == 0) || (tstr == 0))
    {
        return -1;
    }

    int slen = strlen(sstr);
    int tlen = strlen(tstr);

    /* 获取next数组 */
    int *next = malloc(sizeof(int) * tlen);
    Next(tstr, next);

    /* 循环结束 , 要么 ii == slen , 匹配失败 ; 要么 jj == tlen , 匹配成功 */
    int ii = 0, jj = 0;
    while ((ii < slen) && (jj < tlen))
    {
        if ((jj == -1) || (sstr[ii] == tstr[jj]))
        {
            /* 要么 sstr[ii] == tstr[jj] 继续往下匹配 */
            /* 要么 jj == -1 代表第一次匹配就不成功 , jj++ 变成 0 , ii++ , 因此 tstr[0] 与 sstr[j+1] 匹配 */
            ii++;
            jj++;
        }
        else
        {
            jj = next[jj]; // 根据 next 数组模式串指针回溯
        }
    }

    /* free() 是个好习惯 */
    free(next);

    if (jj == tlen)
    {
        /* 末 - 初 + 1 = 中间的元素个数 */
        /* 例如 s[1] 到 s[3] 中间的元素个数为 3 - 1 + 1 */

        /* ( ii - 1 ) - begin + 1 = jj */
        /* return begin; */
        return ii - jj;
    }

    return -1;
}

// /* test */
// int main()
// {
//     char s[] = "ababdcabcacbab";
//     char t[] = "fooffofoo";
//     int x = KMP(s, t);
//     printf("%c %c %c", s[x], s[x + 1], s[x + 2]);
// }
// /* check */