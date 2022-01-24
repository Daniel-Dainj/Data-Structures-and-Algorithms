#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// 构建底层基本函数体原型功能的实现（仓库）
Status List_Find(SqListPtr L, int pos, Ptr* pAddr);

// 初始化、创建线性表
Status List_Init(SqListPtr L)
{
	Status s = fail;
	Ptr p = NULL; // ①
	if (*L == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // 分配内存空间
		if (p != NULL)
		{
			*L = p;
			(*L)->next = NULL;
			s = success;
		}
		return s;
	}
}

// 销毁链表（释放链表中数据元素结点和头节点所占用的存储空间，逐个删除所有结点信息）
void List_Destory(SqListPtr L)
{
	//Ptr p = NULL;
	//if (*L)
	//{
	//	p = (*L)->next; // * head->** L->*** 头节点->*** 元素节点1(p1)->*** 元素节点2(p2)...
	//	while (p)
	//	{
	//		(*L)->next = p->next;
	//		free(p);
	//		p = (*L)->next;
	//	}
	//	free(*L);
	//	*L = NULL;
	//}
	List_Clear(L);
	if (*L)
	{
		free(*L);
		*L = NULL;
	}
}

// 清空链表（释放链表中数据元素结点所占用的存储空间，但头节点的信息保留）
void List_Clear(SqListPtr L)
{
	Ptr p = NULL;
	if (*L)
	{
		p = (*L)->next; // * head->** L->*** 头节点->*** 元素节点1(p1)->*** 元素节点2(p2)...
		while (p)
		{
			(*L)->next = p->next;
			free(p);
			p = (*L)->next;
		}
	}
}

bool List_Empty(SqListPtr L)
{
	return ((*L)->next == NULL);
}

int List_Size(SqListPtr L)
{
	Ptr p = (*L)->next;
	int len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}

// 获取链表位置为pos的元素的值elem（前提要求：线性表L及p指针所指元素存在，且pos位置合法）
Status List_Retrival(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	int len = List_Size(L); // 由于while语句的循环条件中要求元素p存在，故与此语句而这任取其一即可；
	Ptr p = (*L)->next;
	int i=1;
	if (pos <= len) // 由于while语句的循环条件中要求元素p存在，故与此语句而这任取其一即可；
	{
		while (p && i < pos)
		{
			p = p->next;
			i++;
		}
		if (p && i == pos)
		{
			*elem = p->elem;
			s = success;
		}
		else
		{
			s = fail;
		}
	}
	return s;
}

// 【新增】查询元素位置函数
Status List_Find(SqListPtr L, int pos,Ptr *pAddr)
{
	Status s = fail;
	Ptr p = (*L), q = (*L)->next;
	int i = 1;
	while (q && i < pos-1)
	{
		p = q; // 或 p = p->next;
		q = q->next;
		i++;
	}
	if (q && i == pos-1) // ②!!!
	{
		*pAddr = q;
		s = success;
	}
	return s;
}

// 查询链表中元素的值为elem的位置pos（前提要求：线性表L及p指针所指元素存在）
Status List_Locate(SqListPtr L, ElemType elem, int* pos)
{
	Status s = fail;
	Ptr p = (*L)->next;
	int i = 1;
	while (p)
	{
		if (p->elem==elem)
		{
			s = success;
			*pos = i;
			break;
		}
		else
		{
			p = p->next;
			i++;
		}
	}
	return s;
}

// 在链表中位置为pos处插入新元素（前提要求：线性表L及p指针所指元素存在，且pos位置合法）
Status List_Insert(SqListPtr L, int pos, ElemType elem)
{
	Status s = fail;
	Ptr p = NULL, q=NULL;
	//Status s = fail;
	//Ptr p = (*L), q = (*L)->next;
	//int i = 1;
	//while (q && i < pos)
	//{
	//	p = q; // 或 p = p->next;
	//	q = q->next;
	//	i++;
	//}
	//if (i==pos) // ②!!!
	//{
	//	q = (Ptr)malloc(sizeof(Node));
	//	if (q)
	//	{
	//		q->elem = elem;
	//		q->next = p->next;
	//		p->next = q;
	//		s = success;
	//	}
	//	else
	//	{
	//		s = fatal;
	//	}
	//}
	if (pos > 1)
	{
		s = List_Find(L, pos, &p);
		if (s == success)
		{
			q = (Ptr)malloc(sizeof(Node));
			if (q)
			{
				q->elem = elem;
				q->next = p->next;
				p->next = q;
				s = success;
			}
			else
			{
				s = fatal;
			}
		}
	}
	else
	{
		q = (Ptr)malloc(sizeof(Node));
		q->elem = elem;
		q->next = (*L)->next;
		(*L)->next = q;
		s = success;
	}
	return s;
}

Status List_Delete(SqListPtr L, int pos)
{
	Status s = fail;
	Ptr p = NULL, q=NULL;
	//Status s = fail;
	//Ptr p = (*L), q = (*L)->next;
	//int i = 1;
	//while (q && i < pos)
	//{
	//	p = q; // 或 p = p->next;
	//	q = q->next;
	//	i++;
	//}
	//if (i == pos) // ②!!!
	//{
	//	q = (Ptr)malloc(sizeof(Node));
	//	if (q)
	//	{
	//		p->next = q->next;
	//		free(q);
	//		q = NULL;
	//		s = success;
	//	}
	//	else
	//	{
	//		s = fatal;
	//	}
	//}
	s = List_Find(L, pos, &p);
	if (s == success)
	{
		q = p->next;
		if (q)
		{
			p->next = q->next;
			free(q);
			q = NULL;
		}
		else
		{
			s = fatal;
		}
	}
	return s;
}

Status List_Prior(SqListPtr L, int pos, ElemType* elem)
{
	Status s = fail;
	Ptr p = NULL, q=NULL;
	s = List_Find(L, pos, &p);
	if (s == success)
	{
		*elem = p->elem;
	}
	else
	{
		s = fatal;
	}
	return s;
}

Status List_Next(SqListPtr L, int pos, ElemType* elem)
{
	Status s = fail;
	Ptr p = NULL, q=NULL;
	s = List_Find(L, pos, &p);
	if (s == success)
	{
		q = p->next;
		*elem = q->elem;
	}
	else
	{
		s = fatal;
	}
	return s;
}

void List_Print(SqListPtr L)
{
	Ptr p = (*L)->next;
	int i = 1;
	while (p)
	{
		printf("%d ", p->elem);
		if (i++%10==0)
		{
			printf("\n");
		}
		p = p->next;
	}
}