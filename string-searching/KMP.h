/* the Knuth–Morris–Pratt string-searching algorithm */

/* lsp[] : longest proper prefix */
/* eg: S="abcab" */
/* lsp[0] = 0 , always */
/* lsp[1] = 0 */
/* lsp[3] = 1 */
/* lsp[4] = 2 */

#ifndef _KMP_H
#define _KMP_H

// 在 txt 里面找 pat
// Prints occurrences of txt[] in pat[]
void KMPSearch(char *pat, char *txt);

#endif

/* reference : https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/ */