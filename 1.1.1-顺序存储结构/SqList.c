#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// 构建底层基本函数体原型（仓库）

//// 初始化、创建线性表
//方案一：
Status List_Init(SqListPtr L)
{
	Status s = fatal;
	if (L != NULL)
	{ //TODO：存在逻辑问题：取消对 NULL 指针“L”的引用。——已解决
		L->elem = (ElemType*)malloc(sizeof(ElemType) * (LIST_INIT_SIZE + 1));
		if (L->elem) // 或 if (L->elem != NULL)
		{
			L->list_size = LIST_INIT_SIZE;
			L->length = 0;
			s = success;
		}
	}
	return s;
}

//// 方案二：
//Status List_Init(SqListPtr L)
//{
//	Status s = success;
//	L->list_size = LIST_INIT_SIZE;
//	L->length = 0;
//	L->elem = (ElemType*)malloc(sizeof(ElemType) * (LIST_INIT_SIZE + 1));
//	if (L->elem == NULL)
//		s = fatal;
//	return s;
//}

// 清除线性表（释放空间）
void List_Destory(SqListPtr L)
{
	if (L)
	{
		if (L->elem)
		{
			free(L->elem);
			//void free(void *ptr);
			//释放ptr指向的存储空间。被释放的空间通常被送入可用存储区池，以后可在调用malloc函数来再分配。
			L->elem = NULL;
			L->length = 0;
		}
	}
}

// 清空线性表（清空用户已处理的数据）
void List_Clear(SqListPtr L)
{
	if (L)
	{
		L->length = 0;
	}
}

// 判断线性表中是否存在用户数据
bool List_Empty(SqListPtr L)
{
	return (L->length == 0);
}

// 求线性表的长度（元素个数）
int List_Size(SqListPtr L)
{
	return L->length;
}

// 读取线性表中pos位置的元素值
Status List_Retrival(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos <= L->length) // 判断pos位置的合法性。注意：此处为了使数据的逻辑关系与实际物理存储关系一致，即线性表位置从1开始，0处不用，则要求在初始化线性表时多分配1个单位的存储空间。
		{
			*elem = L->elem[pos];
			s = success;
		}
	}
	else
		s = fatal;
	return s;
}

// 定位线性表中的某个值
Status List_Locate(SqListPtr L, ElemType elem, int* pos) //FIXME!!!
{
	Status s = range_error;
	if (L)
	{
		for (int i = 1; i <= L->length; i++)
		{
			if (L->elem[i] == elem)
			{
				*pos = i;
				s = success;
				break;
			}
		}
	}
	else
		s = fatal;
	return s;
}

// 在线性表中插入新元素
Status List_Insert(SqListPtr L, int pos, ElemType elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos <= (L->length + 1)) //插入位置合法
		{
			if (L->length < L->list_size) //表未占满
			{
				for (int i = L->length; i >= pos; --i) //逻辑位置与实际存储位置的下标相符
				{
					L->elem[i + 1] = L->elem[i];
				}
				L->elem[pos] = elem; //TODO:该处pos位置存在疑惑！！！是否需要+1？？？
				L->length++;
				s = success;
			}
		}
		else
			s = fail;
	}
	return s;
}

// 在线性表中删除旧元素
Status List_Delete(SqListPtr L, int pos)
{
	Status s = range_error;
	if (L && L->length > 0)
	{
		if (pos >= 1 && pos <= L->length)
		{
			for (int i = pos + 1; i <= L->length; ++i)
			{
				L->elem[i - 1] = L->elem[i];
			}
			L->length--;
			s = success;
		}
		else
			s = fail;
	}
	return s;
}

// 求线性表pos位置的直接前驱的元素的值
Status List_Prior(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos > 1 && pos <= L->length) //第一个位置没有前驱
		{
			*elem = L->elem[pos - 1];
			s = success;
		}
	}
	return s;
}

// 求线性表pos位置的直接后继的元素的值
Status List_Next(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos < L->length)//最后一个位置没有后继
		{
			*elem = L->elem[pos + 1]; //pos位置的下标为pos-1，后继的下标为pos
			s = success;
		}
	}
	return s;
}

// 打印线性表
void List_Print(SqListPtr L)
{
	if (L)
	{
		for (int i = 1; i <= L->length; i++) //TODO:改成++i
		{
			printf("%d ", L->elem[i]);
			if (i % 10 == 0)
			{
				printf("\n");
			}
		}
	}
}