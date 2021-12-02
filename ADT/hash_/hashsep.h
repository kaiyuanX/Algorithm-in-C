/* Interface for separate chaining hash table */
/* 注意我们的关键字是 int */
/* 若想实现关键字为 char 的散列，请修改 typedef int ElementType; 为 typedef char ElementType;*/
/* 且在某些函数实现处做相应修改 */
/* 比如 Find() 函数的循环里 */

typedef int ElementType;

typedef unsigned int Index;

#ifndef _HashSep_H
#define _HashSep_H
//

/* 链表定义 */
struct ListNode;
typedef struct ListNode *Position;

/* hash 定义 */
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);

Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);

/* Routines such as Delete are MakeEmpty are omitted */

//
#endif