#ifndef __BST_H_
#define __BST_H_

#include "hash.h"
#include "binaryMaxHeap.h"
#include "linkedlist.h"

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
    size_t totalNodes;
}BST;

Node * CreateNode(PatientInfo * info);
BST * CreateBST();
Node * PushBST(Node * node, Date * entryDate, PatientInfo * info);
void inorder(Node * node);
Node * minvNode(Node * node);
Node * DeleteNode(Node * node, Date * entryDate);
long SearchBST(BST * root,Date * entryDate, PatientInfo * info);
void DeallocateBST(Node * temp);
void inorderSearchNInsertCountry(Node * node,ListNode ** head);
void inorderSearchNInsert(Node * node,ListNode ** head);

void inorderSearchNInsertDate(Node * node,ListNode ** head, Date * date1, Date * date2);
void inorderSearchNInsertCountryDate(Node * node,ListNode ** head, Date * date1, Date * date2);

void getPatientsInThatPeriod(Node * node, Date * date1, Date * date2);
void getPatientsInThatPeriod_SpecifiCountry(Node * node, Date * date1, Date * exitDate, char * date2);
void getCurrentPatients(Node * node);
#endif
