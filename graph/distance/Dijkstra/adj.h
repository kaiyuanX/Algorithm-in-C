/* 基本邻接表的创建 */
/* 记录权值 */
/* 基本假设是顶点有个名称，会被唯一映射为一个值，类似学号之类的，方便数组操作 */

#ifndef _Adj_h
#define _Adj_h

// 当权重不在考虑范围时，为什么不尝试这个宏呢
#define WEIGHTIGNORE (1)

typedef char VertexType[2];           // 顶点 , 暂且默认一个顶点由两个字符表示      // 暂时没用到
typedef unsigned int VertexValueType; // 顶点映射后的值
typedef int EdgeWeight;               // 权值

// 邻接表一个节点的结构
struct AdjNode
{
    VertexValueType vexValue; // 终点映射后的值
    EdgeWeight weight;        // 权重
    struct AdjNode *next;
};
typedef struct AdjNode *AdjCell;

// 邻接表
struct Adjlist
{
    int ListSize;       // 顶点个数
    AdjCell *TheLists;  // 有头节点
};
typedef struct Adjlist *AdjList;

// 为邻接表申请空间
AdjList InitializeList(int NumberofVex);

// v to w
void AddEdge(VertexValueType v, VertexValueType w, EdgeWeight weight, AdjList L);

//
#endif