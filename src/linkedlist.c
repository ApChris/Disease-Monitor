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
void DeleteListNode(ListNode ** head, char * dc_name)
{
    ListNode * tmp = *head;
    ListNode * prev;

    if(tmp != NULL && !strcmp(tmp -> dc_name, dc_name))
    {
        // change head
        *head = tmp -> next;
        free(tmp);
        return;
    }

    // Search for the data to be deleted
    while(tmp != NULL && !strcmp(tmp -> dc_name, dc_name))
    {
        prev = tmp;
        tmp = tmp -> next;
    }

    // if data doesn't exist in ll
    if(tmp == NULL)
    {
        return;
    }
    // unlink the node from ll
    prev -> next = tmp -> next;

    free(tmp);
}

void Reverse(ListNode ** head)
{
    ListNode * prev = NULL;
    ListNode * current = *head;
    ListNode * next = NULL;

    while(current != NULL)
    {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
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
