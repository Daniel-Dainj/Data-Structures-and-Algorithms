#pragma once

#define LIST_INIT_SIZE 100
#define LIST_INCREAMENT 10
#define bool int

// 声明枚举类型状态函数
//// 方案一：
//enum Status
//{
//	success, fail, fatal, range_error
//};

// 方案二：
typedef enum _status {
	success, error, fatal, range_error
} Status;

/*
* 状态值枚举之具体操作失败信息：
* fail 运行失败
* fatal 内存分配失败
* range_error 数据范围越界错误
*/

typedef int ElemType; // 或使用宏定义，即 #define ElemType int

typedef struct _node //结点，以“结点的序列”表示线性表——称作链表
{
	ElemType elem; // 数据域（数据元素）
	struct _node* next; // 指针域（指示后继元素存储位置）
} Node, * Ptr;
typedef Ptr* SqListPtr;

Status List_Init(SqListPtr L);
void List_Clear(SqListPtr L);
void List_Destory(SqListPtr L);
bool List_Empty(SqListPtr L);
int List_Size(SqListPtr L);
Status List_Retrival(SqListPtr L, int pos, ElemType* elem);
Status List_Locate(SqListPtr L, ElemType elem, int* pos);
Status List_Find(SqListPtr L, int pos, Ptr* pAddr);
Status List_Insert(SqListPtr L, int pos, ElemType elem);
Status List_Delete(SqListPtr L, int pos);
Status List_Prior(SqListPtr L, int pos, ElemType* elem);
Status List_Next(SqListPtr L, int pos, ElemType* elem);
void List_Print(SqListPtr L);