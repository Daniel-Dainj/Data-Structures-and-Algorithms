#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./LinkedList.h"

// ��ʼ�����Ա��������Ա��ͷ��㣩
Status List_Init(LinkedListPtr pList)
{
	Status s = fatal;
	Ptr p = NULL;
	if (*pList == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // �����ڴ�ռ�
		if (p != NULL)
		{
			*pList = p;
			(*pList)->next = NULL;
			s = success;
		}
	}
	else
	{
		s = success;
	}
	return s;
}

// ��ѯ�����н����豸���Ϊid�ĵ�ַָ��pAddr
Status List_Locate_id(LinkedListPtr pList, char id[], LinkedListPtr pAddr)
{
	Status s = error;
	Ptr p = (*pList)->next;
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)
		{
			*pAddr = p;
			s = success;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return s;
}

// ��ѯ�����н����豸����Ϊname�ĵ�ַָ��pAddr
Status List_Locate_name(LinkedListPtr pList, char name[], LinkedListPtr pAddr)
{
	Status s = error;
	Ptr p = (*pList)->next;
	while (p)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			*pAddr = p;
			s = success;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return s;
}

// ��������ͷ���������Ԫ��
Status List_Insert(LinkedListPtr pList, LinkedListPtr pt)
{
	Status s = error;
	Ptr p = (*pList), q = (Ptr)malloc(sizeof(Node)), m = NULL, n = NULL;
	if (q != NULL)
	{
		if (List_Locate_id(pList, (*pt)->data.id, &m) == success)
		{
			printf("¼��ʧ�ܣ�ϵͳ���Ѵ��ھ�����ͬ��ŵ��豸��Ϣ��\n");
		}
		else if (List_Locate_name(pList, (*pt)->data.name, &n) == success)
		{
			printf("¼��ʧ�ܣ�ϵͳ���Ѵ��ھ�����ͬ���Ƶ��豸��Ϣ��\n");
		}
		else
		{
			strcpy(q->data.id, (*pt)->data.id);
			strcpy(q->data.name, (*pt)->data.name);
			q->data.price = (*pt)->data.price;
			q->data.num = (*pt)->data.num;
			q->data.sumPrice = (*pt)->data.price * (*pt)->data.num;
			q->next = p->next;
			(*pList)->next = q;
			s = success;
		}
	}
	else
	{
		printf("ϵͳ�ڴ�ռ䲻�㣬�޷�¼�뱾�������豸����ϸ��Ϣ��\n");
		s = fatal;
	}
	return s;
}

// ������������ݽ�����
int List_Size(LinkedListPtr pList)
{
	Ptr p = (*pList)->next;
	int len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}

// ��ȡ�����ļ�
Status readFile(LinkedListPtr pList, FILE** pFp, char* fileName, int* pType, int* pSum)
{
	Status s = error;
	Ptr p = (Ptr)malloc(sizeof(Node)), q = NULL;
	int i;
	//int t;
	s = List_Init(pList);
	if (s == success)
	{
		if ((*pFp = fopen(fileName, "rb")) == NULL)
		{
			printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			s = error;
			return s;
		}
		fseek(*pFp, 0, SEEK_END);
		*pType = ftell(*pFp) / sizeof(LinkedList);
		rewind(*pFp);
		printf("Ԥ��ȡϵͳ�����ļ��������豸����ϸ��Ϣ����š����ơ��۸��������ܼۣ��ֱ�������ʾ��\n"); //������ӡ������Ϣ���ܽ�������ʹ�á�
		//while (!(t = feof(*pFp)))
		for (i = 1; i <= *pType; i++)
		{
			if (p != NULL)
			{
				if (fread(p, sizeof(LinkedList), 1, *pFp) != 1)
				{
					printf("��ȡʵ�����豸��Ϣ����ϵͳ�����ļ�������%d��ʵ�����豸��ϸ��Ϣ��ȡʧ�ܣ�\n", i); //FIXME!: ������ӡ������Ϣʱ����whileѭ��������ɺ�����������ʾ��仰1�κ���ֹ��
					s = error;
				}
				else
				{
					s = List_Insert(pList, &p);
					if (s == success)
					{
						printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", p->data.id, p->data.name, p->data.price, p->data.num, p->data.sumPrice);
					}
					else
					{
						printf("ϵͳ�ڴ�ռ䲻�㣬�����ļ��е�%d��ʵ�����豸��ϸ��Ϣ��������ʧ�ܡ�\n", i);
						break;
					}
				}
			}
			else
			{
				printf("ϵͳ�ڴ�ռ䲻�㣬�޷�¼�뱾�������豸����ϸ��Ϣ��\n");
				s = fatal;
			}
		}
		q = (*pList)->next;
		while (q != NULL)
		{
			*pSum += q->data.num;
			q = q->next;
		}
		fclose(*pFp);
	}
	else
	{
		printf("���Ա��ʼ��������ͷ��㣩ʧ�ܡ�\n");
		s = error;
	}
	return s;
}

// ��������ͷ�����������Ԫ�ؽ����ռ�õĴ洢�ռ䣬��ͷ�ڵ����Ϣ������
void List_Clear(LinkedListPtr pList)
{
	Ptr p = NULL;
	if (*pList)
	{
		p = (*pList)->next; // * head->** pList->*** ͷ�ڵ�->*** Ԫ�ؽڵ�1(p1)->*** Ԫ�ؽڵ�2(p2)...
		while (p)
		{
			(*pList)->next = p->next;
			free(p);
			p = (*pList)->next;
		}
	}
}

// ���������ͷ�����������Ԫ�ؽ���ͷ�ڵ���ռ�õĴ洢�ռ䣬���ɾ�����н����Ϣ�� //TODO���Կ��ܴ�������
void List_Destory(LinkedListPtr pList)
{
	List_Clear(pList);
	Ptr p = (*pList)->next;
	if (p)
	{
		free(*pList);
		*pList = NULL;
	}
}

// ���������ļ�
Status saveFile(LinkedListPtr pList, FILE** pFp, char* fileName)
{
	Status s = error;
	Ptr p = (*pList)->next;
	int i, SIZE;
	if (p != NULL)
	{
		if ((*pFp = fopen(fileName, "wb")) == NULL)
		{
			printf("�������ļ�����ʧ�ܣ�ԭʵ�����豸��Ϣ����ϵͳ�����ļ���ʧ��\n");
			return s;
		}
		SIZE = List_Size(pList);
		for (i = 1; i <= SIZE; i++)
		{
			if (fwrite(p, sizeof(LinkedList), 1, *pFp) != 1)
			{
				printf("д��ʵ�����豸��Ϣ����ϵͳ�����ļ�������%d��ʵ�����豸��ϸ��Ϣд��ʧ�ܣ�\n", i);
				return s;
			}
			else
			{
				p = p->next;
			}
		}
		s = success;
		fclose(*pFp);
	}
	else
	{
		printf("�����е�����Ϊ�գ��޷����д��ʵ�����豸��Ϣ����ϵͳ�����ļ�������\n");
	}
	return s;
}

// ��������
void createList(LinkedListPtr pList, LinkedListPtr pt)
{
	Status s = error;
	Ptr p = NULL;
	int i, n;
	s = List_Init(pList);
	if (s == success)
	{
		if (*pt)
		{
			printf("������������¼�뼸�������豸��\n");
			scanf("%d", &n);
			for (i = 1; i <= n; i++)
			{
				printf("���������%d�������豸�ı�š����ơ��۸�������\n", i);
				scanf("%s %s %f %d", (*pt)->data.id, (*pt)->data.name, &(*pt)->data.price, &(*pt)->data.num);
				s = List_Insert(pList, pt);
				if (s != success)
				{
					printf("ϵͳ�ڴ�ռ䲻�㣬��%d�������豸����ϸ��Ϣ¼��ʧ�ܡ�\n", i);
					break;
				}
			}
		}
		else
		{
			printf("ϵͳ�ڴ�ռ䲻�㣬�޷�¼�뱾�������豸����ϸ��Ϣ��\n");
			s = fatal;
		}
		if (s == success)
		{
			p = (*pList)->next;
			printf("�ѳɹ�%d��¼�������豸����ϸ��Ϣ��\n", --i);
			for (i = 1; i <= n; i++)
			{
				printf("��%d�������豸�ı�š����ơ��۸��������ܼ۷ֱ��ǣ�\n", i);
				printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", p->data.id, p->data.name, p->data.price, p->data.num, p->data.sumPrice);
				p = p->next;
			}
		}
	}
	else
	{
		printf("���Ա��ʼ��������ͷ��㣩ʧ�ܡ�\n");
	}
}

// ɾ���������豸���Ϊid[]�Ľ��
Status List_Delete_id(LinkedListPtr pList, char id[]) // �����һ�����������ʹ��˫��˫ͷ����������������λ�ò���
{
	Status s = error;
	Ptr p = (*pList)->next, q = *pList;
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)
		{
			if (p)
			{
				printf("�ѳɹ�ɾ���豸����ϸ��Ϣ��\n��ɾ���豸�ı�š����ơ��۸��������ܼ۷ֱ��ǣ�\n");
				printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", p->data.id, p->data.name, p->data.price, p->data.num, p->data.sumPrice);
				q->next = p->next;
				free(p);
				p = NULL;
				s = success;
			}
			else
			{
				s = fatal;
			}
			break;
		}
		else
		{
			q = p;
			p = q->next;
		}
	}
	return s;
}

// ɾ���������豸����Ϊname[]�Ľ��
Status List_Delete_name(LinkedListPtr pList, char name[])
{
	Status s = error;
	Ptr p = (*pList)->next, q = *pList;
	while (p)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			if (p)
			{
				printf("�ѳɹ�ɾ���豸����ϸ��Ϣ��\n��ɾ���豸�ı�š����ơ��۸��������ܼ۷ֱ��ǣ�\n");
				printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", p->data.id, p->data.name, p->data.price, p->data.num, p->data.sumPrice);
				q->next = p->next;
				free(p);
				p = NULL;
				s = success;
			}
			else
			{
				s = fatal;
			}
			break;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	return s;
}

// ��ת��������ݽڵ����Ϣ
Ptr Reverse(Ptr head)
{
	if (head == NULL || head->next == NULL)
	{
		return head;
	}
	Ptr last = Reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return last;
}

//*�������������*
//������������ļ�����
void SwapNode(Ptr pt1, Ptr pt2)
{
	LinkedList temp;
	temp = pt1->data;
	pt1->data = pt2->data;
	pt2->data = temp;
}
//�����򣺣�ʹ�õݹ��㷨��
void SubSort(Ptr head, Ptr tail)
{
	if (head != NULL && tail != NULL && head != tail)
	{
		int pivot = head->data.num;
		Ptr i_pre = head, i = head->next, j = head->next;
		while (j != tail->next)
		{
			if (j->data.num < pivot)
			{
				SwapNode(i, j);
				// track the previous Node of i
				i_pre = i;
				i = i->next;
			}
			j = j->next;
		}
		SwapNode(head, i_pre);// �˴�Ҳ����i��pre��pre
		SubSort(head, i_pre);
		SubSort(i, tail);
	}
}
//������
void QuickSort(LinkedListPtr pList)
{
	Ptr head = (*pList)->next, tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	SubSort(head, tail);
}