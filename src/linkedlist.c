#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/linkedlist.h"

void PushListNode(ListNode ** head, long total_patientes, char * dc_name)
{
    ListNode * node = (ListNode *)malloc(sizeof(ListNode));

    // Set data
    node -> total_patientes = total_patientes;

    node -> dc_name = ( char *)malloc(1 + sizeof(char) * strlen(dc_name));
    strcpy(node -> dc_name,(const  char *)dc_name);

    // The next pointer of new node
    node -> next = (* head);

    // Set head to point to the new node
    (*head) = node;

}

bool SearchInList(ListNode ** head, char * dc_name)
{

    ListNode * tmp = *head;
    while(tmp != NULL)
    {
        if(!strcmp(tmp -> dc_name, dc_name))
        {
            tmp -> total_patientes++;
            // printf("to vrhka\n");
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

long LenOfList(ListNode * head)
{
    long counter = 0;
    // Set current pointer to points at head
    ListNode * current = head;

    // for every list node
    while(current != NULL)
    {
        counter++;
        current = current -> next;
    }
    return counter;
}
void DeleteList(ListNode ** head)
{
    ListNode * current = * head;
    ListNode * next;

    while(current != NULL)
    {
        // change head
        next = current -> next;
        free(current -> dc_name);
        free(current);
        current = next;
    }


    *head = NULL;
}


void PrintList(ListNode ** head)
{
    ListNode * tmp = *head;
    while(tmp != NULL)
    {
        printf("%s -> %ld\n",tmp -> dc_name, tmp -> total_patientes);
        tmp = tmp -> next;
    }
    printf("\n");
}
