#pragma once

#define LIST_INIT_SIZE 100
#define LIST_INCREAMENT 10
#define bool int

//// 方案一：
//enum Status
//{
//	success, fail, fatal, range_error
//};

// 方案二：
typedef enum _status {
	success, fail, fatal, range_error
} Status;

/*
* 状态值枚举之具体操作失败信息：
* fail 运行失败
* fatal 内存分配失败
* range_error 数据范围越界错误
*
*/

typedef int ElemType;

typedef struct _sqList
{
	ElemType* elem; // 一块连续存储空间的首地址指针
	int length;     // 线性表的长度（元素个数）
	int list_size;  // 线性表所分配的存储空间的大小
} SqList, * Ptr, * SqListPtr;
//TODO: typedef Ptr* SqListPtr;

Status List_Init(SqListPtr L);
void List_Destory(SqListPtr L);
void List_Clear(SqListPtr L);
bool List_Empty(SqListPtr L);
int List_Size(SqListPtr L);
Status List_Retrival(SqListPtr L, int pos, ElemType* elem);
Status List_Locate(SqListPtr L, ElemType elem, int pos);
Status List_Insert(SqListPtr L, int pos, ElemType elem);
Status List_Delete(SqListPtr L, int pos);
Status List_Prior(SqListPtr L, int pos, ElemType* elem);
Status List_Next(SqListPtr L, int pos, ElemType elem);
void List_Print(SqListPtr L);