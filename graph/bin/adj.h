/* 基本邻接表的创建 */
/* 记录权值 */

#ifndef _Adj_h
#define _Adj_h

/* 当权重不在考虑范围时，为什么不尝试这个宏呢 */
#define WEIGHTIGNORE (1)

// typedef char VertexType[2];  //顶点 , 暂且默认一个顶点由两个字符表示 //暂时没用到
typedef int VertexValueType; //顶点映射后的值
typedef int EdgeWeight;      //权值

/* 邻接表一个节点的结构 */
struct AdjNode
{
    VertexValueType vexValue; //终点映射后的值
    EdgeWeight weight;        //权重
    struct AdjNode *next;
};
typedef struct AdjNode *AdjCell;

/* 邻接表 */
struct Adjlist
{
    int ListSize;
    AdjCell *TheLists;
    //有头节点
};
typedef struct Adjlist *AdjList;

struct EdgeEntry
{
    VertexValueType v1;
    VertexValueType v2;
    EdgeWeight weight;
};
typedef struct EdgeEntry *EdgeNode;
typedef struct EdgeEntry *EdgeList;

/* 为邻接表申请空间 */
AdjList InitializeList(int NumberofVex);

/* v to w */
void AddEdge(VertexValueType v, VertexValueType w, EdgeWeight weight, AdjList L);

/* generate a undirected-edge which is weight & v1 to and from v2 */
EdgeNode GenerateUndirectedEdge(VertexValueType v1, VertexValueType v2, EdgeWeight weiht);

/* return a list of EdgeEntry */
EdgeList GetEdgesFromUndirectedAdjList(AdjList L);
//
#endif