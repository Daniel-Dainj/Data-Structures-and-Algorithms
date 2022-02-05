#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// 构建底层基本函数体原型功能的实现（仓库）

// 初始化、创建线性表
Status List_Init(SqListPtr L)
{
	Status s = error;
	Ptr p = NULL;
	if (*L == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // 分配内存空间
		if (p != NULL)
		{
			*L = p;
			(*L)->next = NULL;
			s = success;
		}
	}
	return s;
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

// 销毁链表（释放链表中数据元素结点和头节点所占用的存储空间，逐个删除所有结点信息）
void List_Destory(SqListPtr L)
{
	List_Clear(L);
	if (*L)
	{
		free(*L);
		*L = NULL;
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
	//int len = List_Size(L); // 由于while语句的循环条件中要求元素p存在，故与此语句而这任取其一即可；
	Ptr p = (*L)->next;
	int i = 1;
	//if (pos <= len) // 由于while语句的循环条件中要求元素p存在，故与此语句而这任取其一即可；
	//{
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
		s = error;
	}
	//}
	return s;
}

// 查询链表中元素的值为elem的位置pos（前提要求：线性表L及p指针所指元素存在）
Status List_Locate(SqListPtr L, ElemType elem, int* pos)
{
	Status s = error;
	Ptr p = (*L)->next;
	int i = 1;
	while (p)
	{
		if (p->elem == elem)
		{
			*pos = i;
			s = success;
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

//【新增】查询元素位置函数
Status List_Find(SqListPtr L, int pos, Ptr* pAddr)
{
	Status s = error;
	Ptr p = (*L)->next, q = (*L);
	int i = 1;
	while (p && i < pos)
	{
		q = p; // 或 p = p->next;
		p = p->next;
		i++;
	}
	if (p && i == pos)
	{
		*pAddr = p;
		s = success;
	}
	return s;
}

// 在链表中位置为pos处插入新元素（前提要求：线性表L及p指针所指元素存在，且pos位置合法）
Status List_Insert(SqListPtr L, int pos, ElemType elem)
{
	Status s = error;
	Ptr p = NULL, q = NULL;
	if (pos == 1)
	{
		q = (Ptr)malloc(sizeof(Node));
		if (q)
		{
			q->elem = elem;
			q->next = (*L)->next;
			(*L)->next = q;
			s = success;
		}
	}
	else
	{
		s = List_Find(L, pos - 1, &q);
		if (s == success)
		{
			p = (Ptr)malloc(sizeof(Node));
			if (p)
			{
				p->elem = elem;
				p->next = q->next;
				q->next = p;
			}
			else
			{
				s = fatal;
			}
		}
	}
	return s;
}

Status List_Delete(SqListPtr L, int pos)
{
	Status s = error;
	Ptr p = NULL, q = NULL;
	s = List_Find(L, pos - 1, &q);
	if (s == success)
	{
		p = q->next;
		if (p)
		{
			q->next = p->next;
			free(p);
			p = NULL;
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
	Status s = error;
	Ptr q = NULL;
	s = List_Find(L, pos - 1, &q);
	if (s == success)
	{
		*elem = q->elem;
	}
	else
	{
		s = fatal;
	}
	return s;
}

Status List_Next(SqListPtr L, int pos, ElemType* elem)
{
	Status s = error;
	Ptr p = NULL, q = NULL;
	s = List_Find(L, pos, &q);
	if (s == success)
	{
		if (q->next)
		{
			p = q->next;
			*elem = p->elem;
		}
		else
		{
			s = fatal;
		}
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
		if (i++ % 10 == 0)
		{
			printf("\n");
		}
		p = p->next;
	}
	printf("\n");
}