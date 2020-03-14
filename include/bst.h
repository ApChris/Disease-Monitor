#ifndef __BST_H_
#define __BST_H_

typedef struct Node
{
    Date * entryDate;
    struct Node * left;
    struct Node * right;
}Node;

typedef struct BST
{
    Node * root;
}BST;

Node * CreateNode(Date * entryDate);
BST * CreateBST();
Node * PushBST(Node * node, Date * entryDate);
void inorder(Node * node);
Node * DeleteNode(Node * node, Date * entryDate);
long SearchBST(BST * root,Date * entryDate);
void DeallocateBST(BST * temp)
#endif
