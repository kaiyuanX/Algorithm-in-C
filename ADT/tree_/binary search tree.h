/* binary search tree */
/* 两个指针 */
/* 左子树的所有关键字小于节点，右子树的所有关键字大于节点 */
/* 平均深度为 logN */
/* 所有节点的数据不重复 */

typedef int ElementType;

#ifndef _Tree_H
#define _Tree_H
//

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

/* 释放树 T 的数据 */
/* 这里的话，应该是有无返回值都无所谓 */
SearchTree MakeEmpty(SearchTree T);

/* 返回 X 对应的位置 */
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);

SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);

/* 返回位置 p 上的数据 */
ElementType Retrieve(Position P);

//
#endif
