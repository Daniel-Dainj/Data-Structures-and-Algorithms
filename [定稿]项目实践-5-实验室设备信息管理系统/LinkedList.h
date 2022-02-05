#pragma once

typedef enum _status {
	success, error, fatal, range_error
} Status;

/*
* 状态值枚举之具体操作失败信息：
* error 程序运行失败
* fatal 内存分配失败
* range_error 数据范围越界错误
*/

typedef struct _linkedList {
	char id[10];
	char name[20];
	float price;
	int num;
	float sumPrice;
} LinkedList;

typedef struct _node
{
	LinkedList data;
	struct _node* next;
} Node, * Ptr, ** LinkedListPtr;

/* //待升级点·链表反转函数回传指针
typedef struct _list {
	Node* head;
	Node* tail;
} List;
*/

Status List_Init(LinkedListPtr pList);
Status List_Locate_id(LinkedListPtr pList, char id[], LinkedListPtr pAddr);
Status List_Locate_name(LinkedListPtr pList, char name[], LinkedListPtr pAddr);
Status List_Insert(LinkedListPtr pList, LinkedListPtr pt);
int List_Size(LinkedListPtr pList);
Status readFile(LinkedListPtr pList, FILE** pFp, char* fileName, int* pType, int* pSum);
void List_Clear(LinkedListPtr pList);
void List_Destory(LinkedListPtr pList);
Status saveFile(LinkedListPtr pList, FILE** pFp, char* fileName);
void createList(LinkedListPtr pList, LinkedListPtr pt);
Status List_Delete_id(LinkedListPtr pList, char id[]);
Status List_Delete_name(LinkedListPtr pList, char name[]);
Ptr Reverse(Ptr list);
void SwapNode(Ptr pt1, Ptr pt2);
void SubSort(Ptr head, Ptr tail);
void QuickSort(LinkedListPtr pList);