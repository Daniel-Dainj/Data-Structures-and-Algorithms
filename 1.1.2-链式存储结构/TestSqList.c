#include <stdio.h>
#include <stdlib.h>
#include "TestSqList.h"

Status createList(SqListPtr list, ElemType data[], int n)
{
	Status s = error;
	s = List_Init(list);
	if (s == success)
	{
		printf("�ѳ�ʼ�������Ա��ɹ�����ͷ�ڵ㣩��\n");
		for (int i = 1; i <= n; ++i)
		{
			s = List_Insert(list, i, data[i]);
			if (s != success)
			{
				break;
			}
		}
		List_Print(list);
	}
	return s;
}

Status Test_ClearList(SqListPtr list)
{
	Status s = error;
	if (!List_Empty(list))
	{
		List_Clear(list);
		if (List_Empty(list))
		{
			printf("����ո����Ա�\n");
			s = success;
		}
	}
	return s;
}

Status Test_RetrivalPriorNext(SqListPtr list, int pos)
{
	Status s = range_error;
	ElemType e;
	s = List_Retrival(list, pos, &e);
	if (s == success)
	{
		printf("%d��Ԫ����%d\n", pos, e);
		s = List_Prior(list, pos, &e);
		if (s == success)
		{
			printf("%d��ֱ��ǰ��Ԫ����%d\n", pos, e);
		}
		else
		{
			printf("��Ԫ��û�ж�Ӧ��ֱ��ǰ��Ԫ�ء�\n");
		}
		s = List_Next(list, pos, &e);
		if (s == success)
		{
			printf("%d��ֱ�Ӻ��Ԫ����%d��\n", pos, e);
		}
		else
		{
			printf("��Ԫ��û�ж�Ӧ��ֱ�Ӻ��Ԫ�ء�\n");
		}
	}
	else
	{
		printf("��Ԫ�ص�λ�ò��Ϸ���\n");
	}
	return s;
}

Status Test_Locate(SqListPtr list, ElemType e)
{
	Status s;
	int pos = -1;
	s = List_Locate(list, e, &pos);
	if (s == success && pos != -1)
	{
		printf("%d��λ����%d��\n", e, pos);
	}
	else
	{
		printf("��Ԫ�ص�λ�ò���ʧ�ܡ�\n");
	}
	return s;
}

void Test_Size(SqListPtr list)
{
	int len;
	len = List_Size(list);
	printf("���Ա�ĳ���Ϊ%d��\n", len);
}