#include "KMP.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Fills lps[] for given patttern pat[0...M-1]
// name 'lps' indicates longest proper prefix which is also suffix
static void ComputeLPS(char *pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    // 即记录了前后缀的公共长度 , 也表示前缀后一位的位置序号
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                // 跳出与自己的匹配
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int *lps = malloc(sizeof(int) * M);

    // Preprocess the pattern (calculate lps[] array)
    ComputeLPS(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            // 末 - 初 + 1 = 中间的元素个数
            // 例如 s[1] 到 s[3] 中间的元素个数为 3 - 1 + 1

            // 初 == ( i - 1 ) - M + 1
            printf("Found pattern at index %d \n", i - M);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) // mismatch after j matches
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }

    free(lps);
}

// int main()
// {

// /* test1 */
// char s[] = "ababacabcacbab";
// char t[] = "aba";
// /* check */

// /* test2 */
// char s[] = "aaaaaaaaaaa";
// char t[] = "aa";
// /* check */

// KMPSearch(t, s);

// }
