/* 栈结构实现四则混合运算 */


#include <stdio.h>
#include <stdlib.h>

/* 默认待解表达式的长度最大值 */
/* 如：10+2= 长度为 4 */
#define EXPRESSSIZE (100)

/* 栈的定义开始 */
typedef int ElementType;
#define EmptyTOS (-1)
struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};
typedef struct StackRecord *Stack;
int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void MakeEmpty(Stack S);
void DisposeStack(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);
/* 栈的定义结束 */

int Isnumber(char ch)
{
    /* 数字则返回 1 */
    return ch >= 48 && ch <= 57;
}

int main()
{
    /* behind 存储后缀表达式的每个元素的值 */
    /* status 存储后缀表达式的每个元素的性质 */
    /* 比如 10+2 中 */
    /* behind[0]=10 behind[1]=2 behind[2]='+'*/
    /* status[0]=0 status[1]=0 status[2]='+' */
    /* 默认后缀表达式的最大长度为 EXPRESSSIZE */
    int behind[EXPRESSSIZE];
    char status[EXPRESSSIZE];
    for (int i = 0; i < EXPRESSSIZE; i++)
    {
        status[i] = 0;
    }

    /* 栈 operator 用于中缀到后缀的转换 */
    /* 考虑到中缀中出现超级多括号的情况 */
    /* 它的大小 == EXPRESSSIZE 非常保险 */
    Stack operator= NULL;
    operator= CreateStack(EXPRESSSIZE);

    /* 用户输入中缀表达式 */
    /* 如输入：10+2= */
    /* 长度应该为 5 */
    char input[EXPRESSSIZE * 2];
    gets(input);

    /* 其他临时变量 */
    char temp;
    int behindLen = 0;
    int i = 0;

    /* 中缀到后缀转换的主要过程 */
    while ((temp = input[i]) != '=')
    {
        if (temp >= '0' && temp <= '9')
        {
            /* 如果遇到数字，则将整数值赋给 behind[k] */
            sscanf(&input[i], "%d", &behind[behindLen]);
            status[behindLen] = 0;
            behindLen++;
            while (input[i] >= '0' && input[i] <= '9')
            {
                i++;
            }
            i--;
        }
        else
        {
            if (temp == '*' || temp == '/')
            {
                /* 现在遇到 '*'||'/' 则弹出栈顶的 '*'||'/'  */
                /* 再弹入这个 '*'||'/' */
                /* 此处的 operator->TopOfStack >= 0 作用是保证不越界 */
                while (operator->TopOfStack >= 0 &&(operator->Array[operator->TopOfStack] == '*' || operator->Array[operator->TopOfStack] == '/'))
                {
                    behind[behindLen] = operator->Array[operator->TopOfStack];
                    status[behindLen] = operator->Array[operator->TopOfStack--];
                    behindLen++;
                }
                operator->Array[++operator->TopOfStack] = temp;
            }
            else if (temp == '+' || temp == '-')
            {
                /* 现在遇到 '+'||'-' 则弹出栈顶的元素除了 '('  */
                /* 再弹入这个 '+'||'-' */
                while (operator->TopOfStack >= 0 && operator->Array[operator->TopOfStack] != '(')
                {
                    behind[behindLen] = operator->Array[operator->TopOfStack];
                    status[behindLen] = operator->Array[operator->TopOfStack--];
                    behindLen++;
                }
                operator->Array[++operator->TopOfStack] = temp;
            }
            else if (temp == '(')
            {
                operator->Array[++operator->TopOfStack] = temp;
            }
            else if (temp == ')')
            {
                /* 遇到 ')' 不断弹出直到遇到 '(' */
                while (operator->Array[operator->TopOfStack] != '(')
                {
                    behind[behindLen] = operator->Array[operator->TopOfStack];
                    status[behindLen] = operator->Array[operator->TopOfStack--];
                    behindLen++;
                }
                operator->TopOfStack--;
            }
        }

        i++;
    }

    /* 余下运算符出栈 */
    while (operator->TopOfStack >= 0)
    {
        behind[behindLen] = operator->Array[operator->TopOfStack];
        status[behindLen] = operator->Array[operator->TopOfStack--];
        behindLen++;
    }

    int sum = 0;

    /* 后缀表达式到结果 */
    /* 循环结束之后结果存储在 operator 栈顶且此时栈中就它一个元素 */
    for (int i = 0; i < behindLen; i++)
    {
        if (status[i] == '\0')
        {
            Push(behind[i], operator);
        }
        else
        {
            if (status[i] == '+')
            {
                sum = TopAndPop(operator);
                sum += TopAndPop(operator);
                Push(sum, operator);
            }
            else if (status[i] == '-')
            {
                sum = TopAndPop(operator);
                sum = TopAndPop(operator) - sum;
                Push(sum, operator);
            }
            else if (status[i] == '*')
            {
                sum = TopAndPop(operator);
                sum *= TopAndPop(operator);
                Push(sum, operator);
            }
            else if (status[i] == '/')
            {
                sum = TopAndPop(operator);
                sum = TopAndPop(operator) / sum;
                Push(sum, operator);
            }
        }
    }

    printf("%d", TopAndPop(operator));

    return 0;
}

/*  */
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

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}