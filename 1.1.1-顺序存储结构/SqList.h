#pragma once

#define LIST_INIT_SIZE 100
#define LIST_INCREAMENT 10
#define bool int

//// ����һ��
//enum Status
//{
//	success, fail, fatal, range_error
//};

// ��������
typedef enum _status {
	success, fail, fatal, range_error
} Status;

/*
* ״ֵ̬ö��֮�������ʧ����Ϣ��
* fail ����ʧ��
* fatal �ڴ����ʧ��
* range_error ���ݷ�ΧԽ�����
*
*/

typedef int ElemType;

typedef struct _sqList
{
	ElemType* elem; // һ�������洢�ռ���׵�ַָ��
	int length;     // ���Ա�ĳ��ȣ�Ԫ�ظ�����
	int list_size;  // ���Ա�������Ĵ洢�ռ�Ĵ�С
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