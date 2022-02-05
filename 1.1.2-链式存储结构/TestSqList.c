#include <stdio.h>
#include <stdlib.h>
#include "TestSqList.h"

Status createList(SqListPtr list, ElemType data[], int n)
{
	Status s = error;
	s = List_Init(list);
	if (s == success)
	{
		printf("已初始化该线性表（成功建立头节点）。\n");
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
			printf("已清空该线性表。\n");
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
		printf("%d的元素是%d\n", pos, e);
		s = List_Prior(list, pos, &e);
		if (s == success)
		{
			printf("%d的直接前驱元素是%d\n", pos, e);
		}
		else
		{
			printf("该元素没有对应的直接前驱元素。\n");
		}
		s = List_Next(list, pos, &e);
		if (s == success)
		{
			printf("%d的直接后继元素是%d。\n", pos, e);
		}
		else
		{
			printf("该元素没有对应的直接后继元素。\n");
		}
	}
	else
	{
		printf("该元素的位置不合法。\n");
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
		printf("%d的位置是%d。\n", e, pos);
	}
	else
	{
		printf("该元素的位置查找失败。\n");
	}
	return s;
}

void Test_Size(SqListPtr list)
{
	int len;
	len = List_Size(list);
	printf("线性表的长度为%d。\n", len);
}