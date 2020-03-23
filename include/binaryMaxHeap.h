#ifndef _BINARYMAXHEAP_H_
#define _BINARYMAXHEAP_H_

#include "stdio.h"

typedef struct BinaryTreeNode
{
    char * dc_name;
    size_t total_patientes;
    struct BinaryTreeNode * left;
    struct BinaryTreeNode * right;
    struct BinaryTreeNode * parent;
}BinaryTreeNode;

typedef struct BinaryMaxHeap
{
    BinaryTreeNode * root;
    size_t totalNodes;
}BinaryMaxHeap;


void swap(void ** node1, void ** node2);

BinaryTreeNode * CreateBinaryTreeNode(char * dc_name, size_t total_patientes);

BinaryMaxHeap * CreateBinaryMaxHeap();

void inorderMaxHeap(BinaryTreeNode * node);

BinaryTreeNode * PushMaxHeap(BinaryTreeNode * node, char * dc_name, size_t total_patientes);


BinaryTreeNode * BuildMaxHeap(BinaryTreeNode ** arr, BinaryTreeNode * root, size_t i, size_t n);
void setParent(BinaryTreeNode * node,BinaryTreeNode * parent);
void MaxHeapify(BinaryTreeNode * root, BinaryTreeNode * node);
void preorderMaxHeapify(BinaryTreeNode * root);

#endif
