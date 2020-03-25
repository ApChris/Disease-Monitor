#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdio.h>
#include <stdbool.h>

typedef struct ListNode
{
    long total_patientes;
    char * dc_name;
    struct ListNode * next;
}ListNode;


void PushListNode(ListNode ** head, long new_data,char * dc_name);
void PrintList(ListNode ** head);
void DeleteList(ListNode ** head);
bool SearchInList(ListNode ** head,char * dc_name);
long LenOfList(ListNode * head);
void Reverse(ListNode ** head);

#endif
