/*
	File Name 	: bst .c
	Author 		: Christoforos Apostolopoulos
	Project 	: Number -> 1 , System Programming 2019-2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/bst.h"


Node * CreateNode(PatientInfo * info)
{
    Node * node;
    if( (node = (Node *)malloc(sizeof(Node))) == NULL)
    {
        perror("Error(CreateNode): ");
        exit(EXIT_FAILURE);
    }
    // if( (node -> entryDate = (Date *)malloc(sizeof(Date))) == NULL)
    // {
    //     perror("Error(CreateNode): ");
    //     exit(EXIT_FAILURE);
    // }
    node -> entryDate = info -> entryDate;
    node -> info = info;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

BST * CreateBST()
{
    BST * bst;
    if(((bst = (BST *)malloc(sizeof(BST))) == NULL))
    {
        perror("Error(CreateBST): ");
        exit(EXIT_FAILURE);
    }
    bst -> root = NULL;
    bst -> totalNodes = 0;
    return bst;
}

void inorder(Node * node)
{
    if(node != NULL)
    {
        inorder(node -> left);
        printf("%ld-%ld-%ld -> ", node -> entryDate -> day,node -> entryDate -> month, node -> entryDate -> year);
        PatientInfo_Print(node -> info);
        inorder(node -> right);
    }
}

void getCurrentPatients(Node * node)
{
    if(node != NULL)
    {
        getCurrentPatients(node -> left);
        if(node -> info -> exitDate -> day == TAG)
        {
            tResult++;
            // PatientInfo_Print(node -> info);
        }
        getCurrentPatients(node -> right);
    }
}

void getPatientsInThatPeriod(Node * node, Date * date1, Date * date2)
{
    if(node != NULL)
    {
        getPatientsInThatPeriod(node -> left, date1, date2);
        if( (Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
        {
            tResult++;
        }
        getPatientsInThatPeriod(node -> right, date1, date2);
    }
}

// A function which finds the patients from specific country in spesific period
void getPatientsInThatPeriod_SpecifiCountry(Node * node, Date * date1, Date * date2, char * country)
{
    if(node != NULL)
    {
        getPatientsInThatPeriod_SpecifiCountry(node -> left, date1, date2, country);
        if(!strcmp(node -> info -> country, country))
        {
            // check date
            if( (Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
            {
                tResult++;
            }
        }

        getPatientsInThatPeriod_SpecifiCountry(node -> right, date1, date2, country);
    }
}

Node * PushBST(Node * node, Date * entryDate, PatientInfo * info)
{
    if(node == NULL)
    {
        Node * newNode = CreateNode(info);
        node = newNode;
        return node;
    }

    if(Compare_Date(entryDate, node -> entryDate) == -1)
    {
        node -> left = PushBST(node -> left, entryDate, info);
    }
    else
    {
        node -> right = PushBST(node -> right, entryDate, info);
    }
    return node;
}

Node * minvNode(Node * node)
{
    Node * current = node;
    while(current && current -> left != NULL)
    {
        current = current -> left;
    }

    return current;
}



Node * DeleteNode(Node * node, Date * entryDate)
{
    if(node == NULL)
    {
        return node;
    }
    long result = Compare_Date(entryDate, node -> entryDate);
    if(result == -1)
    {
        node -> left = DeleteNode(node -> left, entryDate);
    }
    else if(result == 1)
    {
        node -> right = DeleteNode(node -> right, entryDate);
    }
    else
    {
        if(node -> left == NULL)
        {
            Node * tmp = node -> right;
            free(node);
            return tmp;
        }
        else if(node -> right == NULL)
        {
            Node * tmp = node -> left;
            free(node);
            return tmp;
        }

        Node * tmp = minvNode(node -> right);
        node -> entryDate = tmp -> entryDate;

        node -> right = DeleteNode(node -> right, node -> entryDate);

    }
    return node;
}

void inorderSearchNInsert(Node * node,ListNode ** head)
{
    if(node != NULL)
    {
        inorderSearchNInsert(node -> left, head);
        if(*head == NULL)
        {
            PushListNode(head, 1, node -> info -> diseaseID);
        }
        else
        {
            if(!SearchInList(head,node -> info -> diseaseID))
                PushListNode(head, 1, node -> info -> diseaseID);
        }
        inorderSearchNInsert(node -> right, head);
    }
}

void inorderSearchNInsertDate(Node * node,ListNode ** head, Date * date1, Date * date2)
{
    if(node != NULL)
    {
        inorderSearchNInsertDate(node -> left, head, date1, date2);
        if(*head == NULL)
        {
            if((Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
            {
                PushListNode(head, 1, node -> info -> diseaseID);
            }
        }
        else
        {
            if((Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
            {
                if(!SearchInList(head,node -> info -> diseaseID))
                    PushListNode(head, 1, node -> info -> diseaseID);
            }
        }
        inorderSearchNInsertDate(node -> right, head, date1, date2);
    }
}

void inorderSearchNInsertCountry(Node * node,ListNode ** head)
{
    if(node != NULL)
    {
        inorderSearchNInsertCountry(node -> left, head);
        if(*head == NULL)
        {
            PushListNode(head, 1, node -> info -> country);
        }
        else
        {
            if(!SearchInList(head,node -> info -> country))
                PushListNode(head, 1, node -> info -> country);
        }
        inorderSearchNInsertCountry(node -> right, head);
    }


}

void inorderSearchNInsertCountryDate(Node * node,ListNode ** head, Date * date1, Date * date2)
{
    if(node != NULL)
    {
        inorderSearchNInsertCountryDate(node -> left, head, date1, date2);
        if(*head == NULL)
        {
            if((Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
            {
                PushListNode(head, 1, node -> info -> country);
            }
        }
        else
        {
            if((Compare_Date(node -> info -> entryDate, date1) != -1) && (Compare_Date(node -> info -> entryDate, date2) != 1) )
            {
                if(!SearchInList(head,node -> info -> country))
                    PushListNode(head, 1, node -> info -> country);
            }
        }
        inorderSearchNInsertCountryDate(node -> right, head, date1, date2);
    }


}

void DeallocateBST(Node * temp)
{
    if(temp == NULL)
    {
        return;
    }
    DeallocateBST(temp -> left);
    DeallocateBST(temp -> right);
    free(temp);

}
