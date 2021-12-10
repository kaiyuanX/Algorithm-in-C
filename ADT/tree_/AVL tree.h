/* AVL */
/* Insert 之外的函数实现与 binary search tree 一样 */
/* 单旋转双旋转的函数没写在头文件，请前往 AVL tree.c查看 */

typedef int ElementType;

#ifndef _AvlTree_H
#define _AvlTree_H
//

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

/* 释放树上的所有数据 */
AvlTree MakeEmpty(AvlTree T);

Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);

AvlTree Insert(ElementType X, AvlTree T);

/* Sorry; Delete is unimplemented; */
AvlTree Delete(ElementType X, AvlTree T);

ElementType Retrieve(Position P);

//
#endif