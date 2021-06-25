//数组实现栈
//
typedef int ElementType;

#ifndef _Stack_h
#define _Stack_h
//
struct StackRecord;
typedef struct StackRecord *Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);

//栈的最大的容量MaxElements
Stack CreateStack(int MaxElements);
void MakeEmpty(Stack S);
void DisposeStack(Stack S);

void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
//返回弹出的元素
ElementType TopAndPop(Stack S);
//
#endif
