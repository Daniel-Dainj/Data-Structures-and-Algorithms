#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"

int main(int argc, char const* argv[])
{
    Ptr head = NULL;
    Status s;
    s = List_Init(&head);
    if (head==NULL)
    {
        if (s!=success)
        {
            printf("�����ʼ��ʧ�ܣ���ͷָ��Ϊ�ա�\n");
        }
        else
        {
            printf("�����ʼ���ɹ�����ͷָ��Ϊ�ա�\n");
        }
    }
    else
    {
        printf("�����ʼ���ɹ�����ͷָ�벻Ϊ�ա�\n");
    }

    return 0;
}