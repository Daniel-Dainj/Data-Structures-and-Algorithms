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
	//TODO: 此处是否还可考虑使用枚举方法输出、完成swtch语句的代码自动补全填充。
	do
	{
		//system("cls");
		printf("*****欢迎使用实验室设备信息管理系统，本程序提供以下功能表列******\n");
		printf("*\t\t1: 新增实验室设备信息\t\t\t\t*\n");
		printf("*\t\t2: 查询实验室设备信息\t\t\t\t*\n");
		printf("*\t\t3: 修改实验室设备信息\t\t\t\t*\n");//全字段 部分
		printf("*\t\t4: 删除实验室设备信息\t\t\t\t*\n");//倒叙的问题
		printf("*\t\t5: 统计实验室设备信息\t\t\t\t*\n");
		printf("*\t\t6: 按实验室设备数量升序整理系统数据\t\t*\n");//选择排序，选择性输出新文件/覆盖原文件
		printf("*\t\t0: 结束本实验室设备信息管理系统程序\t\t*\n");//看清题意
		printf("*****************************************************************\n");
		s = readFile(&list, &fp, "lab_list.dat", &type, &sum);
		p = list->next;
		if (opt < 0 || opt>6)
		{
			printf("输入错误,请重新输入您需实现功能的运行代码序号：\n");
			getchar();
			scanf("%d", &opt);
		}
		if (opt == 0)
		{
			opt = -1;
			printf("请输入您需实现功能的运行代码序号：\n");
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
				printf("请选择您要查询实验室设备详细信息的途径：\n");
				printf("1: 通过设备编号来查询\n");
				printf("2: 通过设备名称来查询\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("请输入您要查询的设备编号：\n");
						scanf("%s", id);
						s = List_Locate_id(&list, id, &pt);
						if (s == success)
						{
							printf("您要查询的实验室设备的的编号、名称、价格、数量和总价分别是：\n");
							printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num, pt->data.sumPrice);
						}
						else
						{
							printf("查询失败，现有的系统数据中不包含您所输入的设备编号的设备详细信息。\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("请输入您要查询的设备名称\n");
						scanf("%s", name);
						s = List_Locate_name(&list, name, &pt);
						if (s == success)
						{
							printf("您要查询的实验室设备的的编号、名称、价格、数量和总价分别是：\n");
							printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num, pt->data.sumPrice);
						}
						else
						{
							printf("查询失败，现有的系统数据中不包含您所输入的设备名称的设备详细信息。\n");
						}
						break;
					}
					else
					{
						printf("输入错误，请重新输入。\n");
					}
				} while (!(n == 1 || n == 2));
				fclose(fp);
			}
			else
			{
				printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
			}
			break;
		case 3:
			if (s == success)
			{
				printf("请选择您要修改实验室设备详细信息的途径：\n");
				printf("1: 通过设备编号来修改\n");
				printf("2: 通过设备名称来修改\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("请输入您要修改的设备编号\n");
						scanf("%s", id);
						s = List_Locate_id(&list, id, &pt);
						if (s == success)
						{
							printf("您要修改的实验室设备的的原有编号、名称、价格和数量分别是：\n");
							printf("%s %s %.2f %d\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num);
							printf("请按照编号、名称、价格、数量的顺序依次输入该设备的新详细信息：\n");
							scanf("%s %s %f %d", pt->data.id, pt->data.name, &pt->data.price, &pt->data.num);
							pt->data.sumPrice = pt->data.price * pt->data.num;
						}
						else
						{
							printf("修改失败，现有的系统数据中不包含您所输入的设备编号的设备详细信息。\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("请输入您要修改的设备名称\n");
						scanf("%s", name);
						s = List_Locate_name(&list, name, &pt);
						if (s == success)
						{
							printf("您要修改的实验室设备的的原有编号、名称、价格和数量分别是：\n");
							printf("%s %s %.2f %d\n", pt->data.id, pt->data.name, pt->data.price, pt->data.num);
							printf("请按照编号、名称、价格、数量的顺序依次输入该设备的新详细信息：\n");
							scanf("%s %s %f %d", pt->data.id, pt->data.name, &pt->data.price, &pt->data.num);
							pt->data.sumPrice = pt->data.price * pt->data.num;
						}
						else
						{
							printf("修改失败，现有的系统数据中不包含您所输入的设备名称的设备详细信息。\n");
						}
						break;
					}
					else
					{
						printf("输入错误，请重新输入。\n");
					}
				} while (!(n == 1 || n == 2));
				list->next = Reverse(list->next);
				s = saveFile(&list, &fp, "lab_list.dat");
			}
			else
			{
				printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
			}
			break;
		case 4:
			if (s == success)
			{
				printf("请选择您要删除实验室设备详细信息的途径：\n");
				printf("1: 通过设备编号来删除\n");
				printf("2: 通过设备名称来删除\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("请输入您要删除的设备编号\n");
						scanf("%s", id);
						s = List_Delete_id(&list, id);
						if (s != success)
						{
							printf("删除失败，现有的系统数据中不包含您所输入的设备编号的设备详细信息。\n");
						}
						break;
					}
					else if (n == 2)
					{
						printf("请输入您要删除的设备名称\n");
						scanf("%s", name);
						s = List_Delete_name(&list, name);
						if (s != success)
						{
							printf("删除失败，现有的系统数据中不包含您所输入的设备编号的设备详细信息。\n");
						}
						break;
					}
					else
					{
						printf("输入错误，请重新输入。\n", n);
					}
				} while (!(n == 1 || n == 2));
				list->next = Reverse(list->next);
				s = saveFile(&list, &fp, "lab_list.dat");
			}
			else
			{
				printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
			}
			break;
		case 5:
			if (s == success)
			{
				printf("请选择您要统计实验室设备详细信息的类型：\n");
				printf("1: 统计实验室设备种类数\n");
				printf("2: 统计实验室设备总数量\n");
				do
				{
					scanf("%d", &n);
					if (n == 1)
					{
						printf("统计完成，实验室共有%d种设备。\n", type);
						break;
					}
					else if (n == 2)
					{
						printf("统计完成，实验室设备总数量为%d。\n", sum);
						break;
					}
					else
					{
						printf("输入错误，请重新输入。\n");
					}
				} while (!(n == 1 || n == 2));
				fclose(fp);
			}
			else
			{
				printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
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
				printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
			}
			break;
		default:
			break;
		}
		if (s == success && 0 < opt && opt <= 6)
		{
			printf("您已成功完成本次操作，是否结束本程序？\n（结束本程序请输入运行序号代码：0,如需继续使用请您输入需实现功能的运行序号代码以完成其他操作。）\n运行序号代码：\n");
			opt = 0;
			scanf("%d", &opt);
		}
		if (opt == 0)
		{
			printf("您已成功退出本程序，欢迎您的再次使用！\n");
			free(fp);
		}
		List_Destory(&list);
	} while (opt != 0);
	return 0;
}