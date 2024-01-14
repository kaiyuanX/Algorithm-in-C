/* Disjoint set data structure */
/* All in one file because it's so short */

#ifndef _Disjsets_H
#define _Disjsets_H

/* 保底大于顶点的个数 */
#define NumSets 20

typedef int DisjSet[NumSets]; // DisjSet s;   <==>   int s[NumSets];
typedef int SetType;
typedef int ElementType;

void Initialize(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(ElementType X, DisjSet S);

#endif
/* END */