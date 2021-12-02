#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
    return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements)
{
    Stack S;

    if (MaxElements < MinStackSize)
    {
        printf("Stack size is too small");
    }

    S = malloc(sizeof(struct StackRecord));
    if (S == NULL)
    {
        printf("Out of space!!!");
    }

    S->Array = malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL)
    {
        printf("Out of space!!!");
    }

    S->Capacity = MaxElements;

    MakeEmpty(S);

    return S;
}

void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S))
    {
        printf("Full stack");
    }
    else
    {
        S->Array[++(S->TopOfStack)] = X;
    }
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
    {
        return S->Array[S->TopOfStack];
    }
    else
    {
        printf("Empty stack");
        return 0;
    }
}

void Pop(Stack S)
{
    if (IsEmpty(S))
    {
        printf("Empty stack");
    }
    else
    {
        S->TopOfStack--;
    }
}

ElementType TopAndPop(Stack S)
{
    if (!IsEmpty(S))
    {
        return S->Array[S->TopOfStack--];
    }
    else
    {
        printf("Empty stack");
        return 0;
    }
}
