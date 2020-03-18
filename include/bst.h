#ifndef __BST_H_
#define __BST_H_

#include "date.h"
#include "hash.h"

typedef struct Node
{
    Date * entryDate;
    PatientInfo * info;
    struct Node * left;
    struct Node * right;
}Node;

typedef struct BST
{
    Node * root;
}BST;

Node * CreateNode(Date * entryDate, PatientInfo * info);
BST * CreateBST();
Node * PushBST(Node * node, Date * entryDate, PatientInfo * info);
void inorder(Node * node);
Node * DeleteNode(Node * node, Date * entryDate);
long SearchBST(BST * root,Date * entryDate, PatientInfo * info);
void DeallocateBST(BST * temp);
#endif
