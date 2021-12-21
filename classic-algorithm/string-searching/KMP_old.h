/* the Knuth–Morris–Pratt string-searching algorithm */
/* 求 next 的函数没被优化 , 所以这个程序被抛弃 */
/* 不过它的某些部分可以作为理解 KMP 的方式 */

/* next[] 解释  */
/* 约定从左到右 , 在 sstr 中找 tstr */
/* next[i] : 匹配在 tstr[i] == sstr[j] 处失败 , 应该跳转到 tstr[next[i]] 继续与 sstr[j] 匹配 */
/* next[0] : 固定为 -1 , 是一种特殊情况 , 在 tstr[0] == sstr[j] 处匹配失败 , -1 作为标志 , 下一步为 tstr[0] 与 sstr[j+1] 匹配 */

#ifndef _KMP_H
#define _KMP_H

/* tstr 在 sstr 中进行匹配 */
/* 返回第一次匹配成功的位置 */
/* 失败返回 1 */
int KMP(char sstr[], char tstr[]);

#endif