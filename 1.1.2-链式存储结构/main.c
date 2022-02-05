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
	//TODO: �˴��Ƿ񻹿ɿ���ʹ��ö�ٷ�����������swtch���Ĵ����Զ���ȫ��䡣
	do
	{
		printf("*****�������б�*****\n");
		printf("1: ���Խ������Ա�\n");
		printf("2: ����������Ա�\n");
		printf("3: ������ĳ��λ�õ����Ա�Ԫ�ص�ֵ����ǰ���ͺ�̵�ֵ\n");
		printf("4: ���Բ�ѯĳ��Ԫ�ص�λ��\n");
		printf("5: ������ĳ�����Ա�ĳ���\n");
		printf("6: ��������\n");
		printf("������ѡ�\n");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			printf("���������Ա�ĳ��ȣ�\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("�������������Ա������Ԫ�أ�\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s != success)
			{
				printf("�������Ա�ʧ�ܡ�\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 2:
			printf("���������Ա�ĳ��ȣ�\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("�������������Ա������Ԫ�أ�\n");
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
				printf("ִ��������Ա�ָ��ǰ���������Ա�ʧ�ܡ�\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 3:
			printf("���������Ա�ĳ��ȣ�\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("�������������Ա������Ԫ�أ�\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				printf("���������ѯԪ�ص�λ�ã�\n");
				scanf("%d", &pos);
				Test_RetrivalPriorNext(&list, pos);
			}
			else
			{
				printf("ִ����ĳ��λ�õ����Ա�Ԫ�ص�ֵ����ǰ���ͺ�̵�ֵָ��ǰ���������Ա�ʧ�ܡ�\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 4:
			printf("���������Ա�ĳ��ȣ�\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("�������������Ա������Ԫ�أ�\n");
			for (int i = 1; i <= size; i++)
			{
				scanf("%d", &data[i]);
			}
			s = createList(&list, data, size);
			if (s == success)
			{
				printf("���������ѯԪ�ص�ֵ��\n");
				scanf("%d", &e);
				Test_Locate(&list, e);
			}
			else
			{
				printf("ִ�в�ѯĳ��Ԫ�ص�λ��ָ��ǰ���������Ա�ʧ�ܡ�\n");
			}
			free(data);
			List_Destory(&list);
			break;
		case 5:
			printf("���������Ա�ĳ��ȣ�\n");
			scanf("%d", &size);
			data = (ElemType*)malloc(sizeof(ElemType) * (size + 1));
			if (data == NULL)
			{
				break;
			}
			printf("�������������Ա������Ԫ�أ�\n");
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
				printf("ִ����ĳ�����Ա�ĳ���ָ��ǰ���������Ա�ʧ�ܡ�\n");
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