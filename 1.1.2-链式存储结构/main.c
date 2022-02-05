#include <stdio.h>
#include <stdlib.h>
#include "TestSqList.h"

int main(int argc, char const* argv[])
{
	int opt;
	Ptr list=NULL;
	int pos, size;
	ElemType e, * data;
	Status s;
	//TODO: 此处是否还可考虑使用枚举方法输出、完成swtch语句的代码自动补全填充。
	do
	{
		printf("*****程序功能列表*****\n");
		printf("1: 测试建立线性表\n");
		printf("2: 测试清空线性表\n");
		printf("3: 测试求某个位置的线性表元素的值及其前驱和后继的值\n");
		printf("4: 测试查询某个元素的位置\n");
		printf("5: 测试求某个线性表的长度\n");
		printf("6: 结束程序\n");
		printf("请输入选项：\n");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			printf("请输入线性表的长度：\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("请依次输入线性表的所有元素：\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s != success)
			{
				printf("建立线性表失败。\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 2:
			printf("请输入线性表的长度：\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("请依次输入线性表的所有元素：\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				s = Test_ClearList(&list);
			}
			else
			{
				printf("执行清空线性表指令前，建立线性表失败。\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 3:
			printf("请输入线性表的长度：\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("请依次输入线性表的所有元素：\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				printf("请输入待查询元素的位置：\n");
				scanf("%d", &pos);
				Test_RetrivalPriorNext(&list, pos);
			}
			else
			{
				printf("执行求某个位置的线性表元素的值及其前驱和后继的值指令前，建立线性表失败。\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 4:
			printf("请输入线性表的长度：\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("请依次输入线性表的所有元素：\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				printf("请输入待查询元素的值：\n");
				scanf("%d", &e);
				Test_Locate(&list, e);
			}
			else
			{
				printf("执行查询某个元素的位置指令前，建立线性表失败。\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 5:
			printf("请输入线性表的长度：\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("请依次输入线性表的所有元素：\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				Test_Size(&list);
			}
			else
			{
				printf("执行求某个线性表的长度指令前，建立线性表失败。\n");
			}
			free(data);
			List_Destory(&list);
			break;
		default:
			break;
		}
	} while (opt != 6);
	return 0;
}