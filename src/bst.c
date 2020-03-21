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


Node * CreateNode(Date * entryDate, PatientInfo * info)
{
    Node * node;
    if( (node = (Node *)malloc(sizeof(Node))) == NULL)
    {
        perror("Error(CreateNode): ");
        exit(EXIT_FAILURE);
    }
    if( (node -> entryDate = (Date *)malloc(sizeof(Date))) == NULL)
    {
        perror("Error(CreateNode): ");
        exit(EXIT_FAILURE);
    }
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
            PatientInfo_Print(node -> info);
        }
        getCurrentPatients(node -> right);
    }
}

void getPatientsInThatPeriod(Node * node, Date * entryDate, Date * exitDate)
{
    if(node != NULL)
    {
        getPatientsInThatPeriod(node -> left, entryDate, exitDate);
        if( (Compare_Date(node -> info -> entryDate, entryDate) != -1) && (Compare_Date(node -> info -> exitDate, exitDate) != 1) )
        {
            tResult++;
            PatientInfo_Print(node -> info);
        }
        getPatientsInThatPeriod(node -> right, entryDate, exitDate);
    }
}

// A function which finds the patients from specific country in spesific period
void getPatientsInThatPeriod_SpecifiCountry(Node * node, Date * entryDate, Date * exitDate, char * country)
{
    if(node != NULL)
    {
        getPatientsInThatPeriod_SpecifiCountry(node -> left, entryDate, exitDate, country);
        if(!strcmp(node -> info -> country, country))
        {
            // check date
            if( (Compare_Date(node -> info -> entryDate, entryDate) != -1) && (Compare_Date(node -> info -> exitDate, exitDate) != 1) )
            {
                tResult++;
                PatientInfo_Print(node -> info);
            }
        }

        getPatientsInThatPeriod_SpecifiCountry(node -> right, entryDate, exitDate, country);
    }
}

Node * PushBST(Node * node, Date * entryDate, PatientInfo * info)
{
    Node * newNode = CreateNode(entryDate, info);
    if(node == NULL)
    {
        node = newNode;
        return node;
    }

    printf("%ld-%ld-%ld -> ", node -> entryDate -> day,node -> entryDate -> month, node -> entryDate -> year);
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

//
// long SearchBST(BST * root, Date * entryDate)
// {
//     BST * tempNode;
//     tempNode = root;
//     while(tempNode != NULL)
//     {
//         if(tempNode -> entryDate == entryDate)
//         {
//             printf("\n%ld has been found!!\n",tempNode -> entryDate -> day);
//             return 1;
//         }
//
//         if(Compare_Date_Time(entryDate, tempNode -> entryDate))
//         {
//             tempNode = tempNode -> left;
//         }
//         else
//         {
//             tempNode = tempNode -> right;
//         }
//     }
//     return 0;
//
// }
//
//
// void DeallocateBST(BST * temp)
// {
//     if(temp != NULL)
//     {
//         free(temp);
//
//         BST_Deallocate_Preorder(temp -> left);
//         BST_Deallocate_Preorder(temp -> right);
//     }
// }
