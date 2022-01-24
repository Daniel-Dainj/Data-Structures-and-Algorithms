#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

// �����ײ����������ԭ�ͣ��ֿ⣩

//// ��ʼ�����������Ա�
//����һ��
Status List_Init(SqListPtr L)
{
	Status s = fatal;
	if (L != NULL)
	{ //TODO�������߼����⣺ȡ���� NULL ָ�롰L�������á������ѽ��
		L->elem = (ElemType*)malloc(sizeof(ElemType) * (LIST_INIT_SIZE + 1));
		if (L->elem) // �� if (L->elem != NULL)
		{
			L->list_size = LIST_INIT_SIZE;
			L->length = 0;
			s = success;
		}
	}
	return s;
}

//// ��������
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

// ������Ա��ͷſռ䣩
void List_Destory(SqListPtr L)
{
	if (L)
	{
		if (L->elem)
		{
			free(L->elem);
			//void free(void *ptr);
			//�ͷ�ptrָ��Ĵ洢�ռ䡣���ͷŵĿռ�ͨ����������ô洢���أ��Ժ���ڵ���malloc�������ٷ��䡣
			L->elem = NULL;
			L->length = 0;
		}
	}
}

// ������Ա�����û��Ѵ�������ݣ�
void List_Clear(SqListPtr L)
{
	if (L)
	{
		L->length = 0;
	}
}

// �ж����Ա����Ƿ�����û�����
bool List_Empty(SqListPtr L)
{
	return (L->length == 0);
}

// �����Ա�ĳ��ȣ�Ԫ�ظ�����
int List_Size(SqListPtr L)
{
	return L->length;
}

// ��ȡ���Ա���posλ�õ�Ԫ��ֵ
Status List_Retrival(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos <= L->length) // �ж�posλ�õĺϷ��ԡ�ע�⣺�˴�Ϊ��ʹ���ݵ��߼���ϵ��ʵ������洢��ϵһ�£������Ա�λ�ô�1��ʼ��0�����ã���Ҫ���ڳ�ʼ�����Ա�ʱ�����1����λ�Ĵ洢�ռ䡣
		{
			*elem = L->elem[pos];
			s = success;
		}
	}
	else
		s = fatal;
	return s;
}

// ��λ���Ա��е�ĳ��ֵ
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

// �����Ա��в�����Ԫ��
Status List_Insert(SqListPtr L, int pos, ElemType elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos <= (L->length + 1)) //����λ�úϷ�
		{
			if (L->length < L->list_size) //��δռ��
			{
				for (int i = L->length; i >= pos; --i) //�߼�λ����ʵ�ʴ洢λ�õ��±����
				{
					L->elem[i + 1] = L->elem[i];
				}
				L->elem[pos] = elem; //TODO:�ô�posλ�ô����ɻ󣡣����Ƿ���Ҫ+1������
				L->length++;
				s = success;
			}
		}
		else
			s = fail;
	}
	return s;
}

// �����Ա���ɾ����Ԫ��
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

// �����Ա�posλ�õ�ֱ��ǰ����Ԫ�ص�ֵ
Status List_Prior(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos > 1 && pos <= L->length) //��һ��λ��û��ǰ��
		{
			*elem = L->elem[pos - 1];
			s = success;
		}
	}
	return s;
}

// �����Ա�posλ�õ�ֱ�Ӻ�̵�Ԫ�ص�ֵ
Status List_Next(SqListPtr L, int pos, ElemType* elem)
{
	Status s = range_error;
	if (L)
	{
		if (pos >= 1 && pos < L->length)//���һ��λ��û�к��
		{
			*elem = L->elem[pos + 1]; //posλ�õ��±�Ϊpos-1����̵��±�Ϊpos
			s = success;
		}
	}
	return s;
}

// ��ӡ���Ա�
void List_Print(SqListPtr L)
{
	if (L)
	{
		for (int i = 1; i <= L->length; i++) //TODO:�ĳ�++i
		{
			printf("%d ", L->elem[i]);
			if (i % 10 == 0)
			{
				printf("\n");
			}
		}
	}
}