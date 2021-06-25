typedef int ElementType;
//
#ifndef _Tree_H
#define _Tree_H
//
//两个指针
//左子树的所有关键字小于节点，右子树的所有关键字大于节点
//平均深度为logN
//所有节点的数据不重复
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

//删除树 T
SearchTree MakeEmpty(SearchTree T);

Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);

SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);

//返回位置 p 上的数据
ElementType Retrieve(Position P);
//
#endif
