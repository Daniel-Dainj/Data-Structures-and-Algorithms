#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./LinkedList.h"

// 初始化线性表（创建线性表的头结点）
Status List_Init(LinkedListPtr pList)
{
	Status s = fatal;
	Ptr p = NULL;
	if (*pList == NULL)
	{
		p = (Ptr)malloc(sizeof(Node)); // 分配内存空间
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

// 查询链表中结点的设备编号为id的地址指针pAddr
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

// 查询链表中结点的设备名称为name的地址指针pAddr
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

// 给链表中头结点后插入新元素
Status List_Insert(LinkedListPtr pList, LinkedListPtr pt)
{
	Status s = error;
	Ptr p = (*pList), q = (Ptr)malloc(sizeof(Node)), m = NULL, n = NULL;
	if (q != NULL)
	{
		if (List_Locate_id(pList, (*pt)->data.id, &m) == success)
		{
			printf("录入失败，系统中已存在具有相同编号的设备信息。\n");
		}
		else if (List_Locate_name(pList, (*pt)->data.name, &n) == success)
		{
			printf("录入失败，系统中已存在具有相同名称的设备信息。\n");
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
		printf("系统内存空间不足，无法录入本次新增设备的详细信息。\n");
		s = fatal;
	}
	return s;
}

// 计算链表的数据结点个数
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

// 读取数据文件
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
			printf("数据文件打开失败，实验室设备信息管理系统数据文件不存在！\n");
			s = error;
			return s;
		}
		fseek(*pFp, 0, SEEK_END);
		*pType = ftell(*pFp) / sizeof(LinkedList);
		rewind(*pFp);
		printf("预读取系统数据文件中所有设备的详细信息（编号、名称、价格、数量和总价）分别如下所示：\n"); //遍历打印数据信息功能仅供测试使用。
		//while (!(t = feof(*pFp)))
		for (i = 1; i <= *pType; i++)
		{
			if (p != NULL)
			{
				if (fread(p, sizeof(LinkedList), 1, *pFp) != 1)
				{
					printf("读取实验室设备信息管理系统数据文件出错，第%d种实验室设备详细信息读取失败！\n", i); //FIXME!: 遍历打印数据信息时若按while循环运行完成后，最后仍输出显示这句话1次后终止。
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
						printf("系统内存空间不足，数据文件中第%d种实验室设备详细信息存入链表失败。\n", i);
						break;
					}
				}
			}
			else
			{
				printf("系统内存空间不足，无法录入本次新增设备的详细信息。\n");
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
		printf("线性表初始化（建立头结点）失败。\n");
		s = error;
	}
	return s;
}

// 清空链表（释放链表中数据元素结点所占用的存储空间，但头节点的信息保留）
void List_Clear(LinkedListPtr pList)
{
	Ptr p = NULL;
	if (*pList)
	{
		p = (*pList)->next; // * head->** pList->*** 头节点->*** 元素节点1(p1)->*** 元素节点2(p2)...
		while (p)
		{
			(*pList)->next = p->next;
			free(p);
			p = (*pList)->next;
		}
	}
}

// 销毁链表（释放链表中数据元素结点和头节点所占用的存储空间，逐个删除所有结点信息） //TODO：仍可能存在问题
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

// 保存数据文件
Status saveFile(LinkedListPtr pList, FILE** pFp, char* fileName)
{
	Status s = error;
	Ptr p = (*pList)->next;
	int i, SIZE;
	if (p != NULL)
	{
		if ((*pFp = fopen(fileName, "wb")) == NULL)
		{
			printf("新数据文件建立失败，原实验室设备信息管理系统数据文件丢失！\n");
			return s;
		}
		SIZE = List_Size(pList);
		for (i = 1; i <= SIZE; i++)
		{
			if (fwrite(p, sizeof(LinkedList), 1, *pFp) != 1)
			{
				printf("写入实验室设备信息管理系统数据文件出错，第%d种实验室设备详细信息写入失败！\n", i);
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
		printf("链表中的内容为空，无法完成写入实验室设备信息管理系统数据文件操作！\n");
	}
	return s;
}

// 建立链表
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
			printf("请输入您本次录入几种新增设备？\n");
			scanf("%d", &n);
			for (i = 1; i <= n; i++)
			{
				printf("请您输入第%d种新增设备的编号、名称、价格、数量：\n", i);
				scanf("%s %s %f %d", (*pt)->data.id, (*pt)->data.name, &(*pt)->data.price, &(*pt)->data.num);
				s = List_Insert(pList, pt);
				if (s != success)
				{
					printf("系统内存空间不足，第%d种新增设备的详细信息录入失败。\n", i);
					break;
				}
			}
		}
		else
		{
			printf("系统内存空间不足，无法录入本次新增设备的详细信息。\n");
			s = fatal;
		}
		if (s == success)
		{
			p = (*pList)->next;
			printf("已成功%d种录入新增设备的详细信息。\n", --i);
			for (i = 1; i <= n; i++)
			{
				printf("第%d种新增设备的编号、名称、价格、数量和总价分别是：\n", i);
				printf("%s,\t%s,\t%5.2f,\t%5d,\t%5.2f\n", p->data.id, p->data.name, p->data.price, p->data.num, p->data.sumPrice);
				p = p->next;
			}
		}
	}
	else
	{
		printf("线性表初始化（建立头结点）失败。\n");
	}
}

// 删除链表中设备编号为id[]的结点
Status List_Delete_id(LinkedListPtr pList, char id[]) // 建议加一个缓冲链表或使用双向双头结点链表输出，保持位置不变
{
	Status s = error;
	Ptr p = (*pList)->next, q = *pList;
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)
		{
			if (p)
			{
				printf("已成功删除设备的详细信息。\n被删除设备的编号、名称、价格、数量和总价分别是：\n");
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

// 删除链表中设备名称为name[]的结点
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
				printf("已成功删除设备的详细信息。\n被删除设备的编号、名称、价格、数量和总价分别是：\n");
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

// 反转链表各数据节点的信息
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

//*链表快速排序功能*
//交换结点数据文件函数
void SwapNode(Ptr pt1, Ptr pt2)
{
	LinkedList temp;
	temp = pt1->data;
	pt1->data = pt2->data;
	pt2->data = temp;
}
//子排序：（使用递归算法）
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
		SwapNode(head, i_pre);// 此处也可是i的pre的pre
		SubSort(head, i_pre);
		SubSort(i, tail);
	}
}
//主排序
void QuickSort(LinkedListPtr pList)
{
	Ptr head = (*pList)->next, tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	SubSort(head, tail);
}