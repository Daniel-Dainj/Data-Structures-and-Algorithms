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
            printf("链表初始化失败，且头指针为空。\n");
        }
        else
        {
            printf("链表初始化成功，但头指针为空。\n");
        }
    }
    else
    {
        printf("链表初始化成功，且头指针不为空。\n");
    }

    return 0;
}