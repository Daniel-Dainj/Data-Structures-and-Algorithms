#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./LinkedList.h"

int main(int argc, char const* argv[])
{
	Status s = error;
	char OPT = 'N';
	int opt = 0;
	FILE* fp = NULL;
	Ptr list = NULL, pt = NULL, p = NULL;
	int type = 0, sum = 0, n = 0;
	char* fileName = NULL;
	char id[10], name[20];
	//TODO: �˴��Ƿ񻹿ɿ���ʹ��ö�ٷ�����������swtch���Ĵ����Զ���ȫ��䡣
	do
	{
		//system("cls");
		printf("*****��ӭʹ��ʵ�����豸��Ϣ����ϵͳ���������ṩ���¹��ܱ���******\n");
		printf("*\t\t1: ����ʵ�����豸��Ϣ\t\t\t\t*\n");
		printf("*\t\t2: ��ѯʵ�����豸��Ϣ\t\t\t\t*\n");
		printf("*\t\t3: �޸�ʵ�����豸��Ϣ\t\t\t\t*\n");//ȫ�ֶ� ����
		printf("*\t\t4: ɾ��ʵ�����豸��Ϣ\t\t\t\t*\n");//���������
		printf("*\t\t5: ͳ��ʵ�����豸��Ϣ\t\t\t\t*\n");
		printf("*\t\t6: ��ʵ�����豸������������ϵͳ����\t\t*\n");//ѡ������ѡ����������ļ�/����ԭ�ļ�
		printf("*\t\t0: ������ʵ�����豸��Ϣ����ϵͳ����\t\t*\n");//��������
		printf("*****************************************************************\n");
		s = readFile(&list, &fp, "lab_list.dat", &type, &sum);
		p = list->next;
		if (opt < 0 || opt>6)
		{
			printf("�������,��������������ʵ�ֹ��ܵ����д�����ţ�\n");
			getchar();
			scanf("%d", &opt);
		}
		if (opt == 0)
		{
			opt = -1;
			printf("����������ʵ�ֹ��ܵ����д�����ţ�\n");
			scanf("%d", &opt);
		}
		switch (opt)
		{
		case 1:
			pt = (Ptr)malloc(sizeof(Node));
			createList(&list, &pt);
			s = saveFile(&list, &fp, "lab_list.dat");
			break;
		case 2:
			if (s == success)
			{
				printf("��ѡ����Ҫ��ѯʵ�����豸��ϸ��Ϣ��;����\n");
				printf("1: ͨ���豸�������ѯ\n");
				printf("2: ͨ���豸��������ѯ\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("��������Ҫ��ѯ���豸��ţ�\n");
						scanf("%s", id);
						s = List_Locate_id(&list, id, &pt);
						if (s == success)
						{
							printf("��Ҫ��ѯ��ʵ�����豸�ĵı�š����ơ��۸��������ܼ۷ֱ��ǣ�\n");
							printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num, pt->data.sumPrice);
						}
						else
						{
							printf("��ѯʧ�ܣ����е�ϵͳ�����в���������������豸��ŵ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("��������Ҫ��ѯ���豸����\n");
						scanf("%s", name);
						s = List_Locate_name(&list, name, &pt);
						if (s == success)
						{
							printf("��Ҫ��ѯ��ʵ�����豸�ĵı�š����ơ��۸��������ܼ۷ֱ��ǣ�\n");
							printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num, pt->data.sumPrice);
						}
						else
						{
							printf("��ѯʧ�ܣ����е�ϵͳ�����в���������������豸���Ƶ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else
					{
						printf("����������������롣\n");
					}
				} while (!(n == 1 || n == 2));
				fclose(fp);
			}
			else
			{
				printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			}
			break;
		case 3:
			if (s == success)
			{
				printf("��ѡ����Ҫ�޸�ʵ�����豸��ϸ��Ϣ��;����\n");
				printf("1: ͨ���豸������޸�\n");
				printf("2: ͨ���豸�������޸�\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("��������Ҫ�޸ĵ��豸���\n");
						scanf("%s", id);
						s = List_Locate_id(&list, id, &pt);
						if (s == success)
						{
							printf("��Ҫ�޸ĵ�ʵ�����豸�ĵ�ԭ�б�š����ơ��۸�������ֱ��ǣ�\n");
							printf("%s %s %.2f %d\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num);
							printf("�밴�ձ�š����ơ��۸�������˳������������豸������ϸ��Ϣ��\n");
							scanf("%s %s %f %d", pt->data.id, pt->data.name, &pt->data.price, &pt->data.num);
							pt->data.sumPrice = pt->data.price * pt->data.num;
						}
						else
						{
							printf("�޸�ʧ�ܣ����е�ϵͳ�����в���������������豸��ŵ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("��������Ҫ�޸ĵ��豸����\n");
						scanf("%s", name);
						s = List_Locate_name(&list, name, &pt);
						if (s == success)
						{
							printf("��Ҫ�޸ĵ�ʵ�����豸�ĵ�ԭ�б�š����ơ��۸�������ֱ��ǣ�\n");
							printf("%s %s %.2f %d\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num);
							printf("�밴�ձ�š����ơ��۸�������˳������������豸������ϸ��Ϣ��\n");
							scanf("%s %s %f %d", pt->data.id, pt->data.name, &pt->data.price, &pt->data.num);
							pt->data.sumPrice = pt->data.price * pt->data.num;
						}
						else
						{
							printf("�޸�ʧ�ܣ����е�ϵͳ�����в���������������豸���Ƶ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else
					{
						printf("����������������롣\n");
					}
				} while (!(n == 1 || n == 2));
				list->next = Reverse(list->next);
				s = saveFile(&list, &fp, "lab_list.dat");
			}
			else
			{
				printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			}
			break;
		case 4:
			if (s == success)
			{
				printf("��ѡ����Ҫɾ��ʵ�����豸��ϸ��Ϣ��;����\n");
				printf("1: ͨ���豸�����ɾ��\n");
				printf("2: ͨ���豸������ɾ��\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("��������Ҫɾ�����豸���\n");
						scanf("%s", id);
						s = List_Delete_id(&list, id);
						if (s != success)
						{
							printf("ɾ��ʧ�ܣ����е�ϵͳ�����в���������������豸��ŵ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("��������Ҫɾ�����豸����\n");
						scanf("%s", name);
						s = List_Delete_name(&list, name);
						if (s != success)
						{
							printf("ɾ��ʧ�ܣ����е�ϵͳ�����в���������������豸��ŵ��豸��ϸ��Ϣ��\n");
						}
						break;
					}
					else
					{
						printf("����������������롣\n", n);
					}
				} while (!(n == 1 || n == 2));
				list->next = Reverse(list->next);
				s = saveFile(&list, &fp, "lab_list.dat");
			}
			else
			{
				printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			}
			break;
		case 5:
			if (s == success)
			{
				printf("��ѡ����Ҫͳ��ʵ�����豸��ϸ��Ϣ�����ͣ�\n");
				printf("1: ͳ��ʵ�����豸������\n");
				printf("2: ͳ��ʵ�����豸������\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("ͳ����ɣ�ʵ���ҹ���%d���豸��\n", type);
						break;
					}
					else if (n == 2)
					{
						printf("ͳ����ɣ�ʵ�����豸������Ϊ%d��\n", sum);
						break;
					}
					else
					{
						printf("����������������롣\n");
					}
				} while (!(n == 1 || n == 2));
				fclose(fp);
			}
			else
			{
				printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			}
			break;
		case 6:
			if (s == success)
			{
				QuickSort(&list);
				s = saveFile(&list, &fp, "lab_list.dat");
				fclose(fp);
			}
			else
			{
				printf("�����ļ���ʧ�ܣ�ʵ�����豸��Ϣ����ϵͳ�����ļ������ڣ�\n");
			}
			break;
		default:
			break;
		}
		if (s == success && 0 < opt && opt <= 6)
		{
			printf("���ѳɹ���ɱ��β������Ƿ����������\n������������������������Ŵ��룺0,�������ʹ������������ʵ�ֹ��ܵ�������Ŵ��������������������\n������Ŵ��룺\n");
			opt = 0;
			scanf("%d", &opt);
		}
		if (opt == 0)
		{
			printf("���ѳɹ��˳������򣬻�ӭ�����ٴ�ʹ�ã�\n");
			free(fp);
		}
		List_Destory(&list);
	} while (opt != 0);
	return 0;
}