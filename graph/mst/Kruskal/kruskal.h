/* 用邻接矩阵会是一个明智的选择 */

#ifndef _Kruskal_H
#define _Kruskal_H

typedef int VertexValueType; // 顶点映射后的值
typedef int EdgeWeight;      // 权值

/* 一条边 */
struct EdgeEntry
{
    VertexValueType v1;
    VertexValueType v2;
    EdgeWeight weight;
};

typedef struct EdgeEntry *Edges;

/* 传入所有边的数组及其个数，顶点个数 */
/* 返回生成树的边集 */
Edges Kruskal(Edges allE, int edgesNumber, int vertexNumber);

#endif