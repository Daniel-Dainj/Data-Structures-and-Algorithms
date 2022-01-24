#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// �����ײ����������ԭ�͹��ܵ�ʵ�֣��ֿ⣩
Status List_Find(SqListPtr L, int pos, Ptr* pAddr);

// ��ʼ�����������Ա�
Status List_Init(SqListPtr L)
{
	Status s = fail;
	Ptr p = NULL; // ��
	if (*L == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // �����ڴ�ռ�
		if (p != NULL)
		{
			*L = p;
			(*L)->next = NULL;
			s = success;
		}
		return s;
	}
}

// ���������ͷ�����������Ԫ�ؽ���ͷ�ڵ���ռ�õĴ洢�ռ䣬���ɾ�����н����Ϣ��
void List_Destory(SqListPtr L)
{
	//Ptr p = NULL;
	//if (*L)
	//{
	//	p = (*L)->next; // * head->** L->*** ͷ�ڵ�->*** Ԫ�ؽڵ�1(p1)->*** Ԫ�ؽڵ�2(p2)...
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

// ��������ͷ�����������Ԫ�ؽ����ռ�õĴ洢�ռ䣬��ͷ�ڵ����Ϣ������
void List_Clear(SqListPtr L)
{
	Ptr p = NULL;
	if (*L)
	{
		p = (*L)->next; // * head->** L->*** ͷ�ڵ�->*** Ԫ�ؽڵ�1(p1)->*** Ԫ�ؽڵ�2(p2)...
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

// ��ȡ����λ��Ϊpos��Ԫ�ص�ֵelem��ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ���posλ�úϷ���
Status List_Retrival(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	int len = List_Size(L); // ����while����ѭ��������Ҫ��Ԫ��p���ڣ��������������ȡ��һ���ɣ�
	Ptr p = (*L)->next;
	int i=1;
	if (pos <= len) // ����while����ѭ��������Ҫ��Ԫ��p���ڣ��������������ȡ��һ���ɣ�
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

// ����������ѯԪ��λ�ú���
Status List_Find(SqListPtr L, int pos,Ptr *pAddr)
{
	Status s = fail;
	Ptr p = (*L), q = (*L)->next;
	int i = 1;
	while (q && i < pos-1)
	{
		p = q; // �� p = p->next;
		q = q->next;
		i++;
	}
	if (q && i == pos-1) // ��!!!
	{
		*pAddr = q;
		s = success;
	}
	return s;
}

// ��ѯ������Ԫ�ص�ֵΪelem��λ��pos��ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ�
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

// ��������λ��Ϊpos��������Ԫ�أ�ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ���posλ�úϷ���
Status List_Insert(SqListPtr L, int pos, ElemType elem)
{
	Status s = fail;
	Ptr p = NULL, q=NULL;
	//Status s = fail;
	//Ptr p = (*L), q = (*L)->next;
	//int i = 1;
	//while (q && i < pos)
	//{
	//	p = q; // �� p = p->next;
	//	q = q->next;
	//	i++;
	//}
	//if (i==pos) // ��!!!
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
	//	p = q; // �� p = p->next;
	//	q = q->next;
	//	i++;
	//}
	//if (i == pos) // ��!!!
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