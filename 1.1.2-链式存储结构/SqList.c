#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// �����ײ����������ԭ�͹��ܵ�ʵ�֣��ֿ⣩

// ��ʼ�����������Ա�
Status List_Init(SqListPtr L)
{
	Status s = error;
	Ptr p = NULL;
	if (*L == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // �����ڴ�ռ�
		if (p != NULL)
		{
			*L = p;
			(*L)->next = NULL;
			s = success;
		}
	}
	return s;
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

// ���������ͷ�����������Ԫ�ؽ���ͷ�ڵ���ռ�õĴ洢�ռ䣬���ɾ�����н����Ϣ��
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

// ��ȡ����λ��Ϊpos��Ԫ�ص�ֵelem��ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ���posλ�úϷ���
Status List_Retrival(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	//int len = List_Size(L); // ����while����ѭ��������Ҫ��Ԫ��p���ڣ��������������ȡ��һ���ɣ�
	Ptr p = (*L)->next;
	int i = 1;
	//if (pos <= len) // ����while����ѭ��������Ҫ��Ԫ��p���ڣ��������������ȡ��һ���ɣ�
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

// ��ѯ������Ԫ�ص�ֵΪelem��λ��pos��ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ�
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

//����������ѯԪ��λ�ú���
Status List_Find(SqListPtr L, int pos, Ptr* pAddr)
{
	Status s = error;
	Ptr p = (*L)->next, q = (*L);
	int i = 1;
	while (p && i < pos)
	{
		q = p; // �� p = p->next;
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

// ��������λ��Ϊpos��������Ԫ�أ�ǰ��Ҫ�����Ա�L��pָ����ָԪ�ش��ڣ���posλ�úϷ���
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