
#include "../include/binaryMaxHeap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/bst.h"

void swap(void ** node1, void ** node2)
{
    void * temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

BinaryTreeNode * CreateBinaryTreeNode(char * dc_name, size_t total_patientes)
{
    BinaryTreeNode * node;
    if( (node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode))) == NULL)
    {
        perror("Error(CreateBinaryTreeNode): ");
        exit(EXIT_FAILURE);
    }

    node -> dc_name = ( char *)malloc(1 + sizeof(char) * strlen(dc_name));
    strcpy(node -> dc_name,(const  char *)dc_name);

    node -> total_patientes = total_patientes;
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = NULL;

    return node;
}

BinaryMaxHeap * CreateBinaryMaxHeap()
{
    BinaryMaxHeap * bst;
    if(((bst = (BinaryMaxHeap *)malloc(sizeof(BinaryMaxHeap))) == NULL))
    {
        perror("Error(CreateBinaryMaxHeap): ");
        exit(EXIT_FAILURE);
    }
    bst -> root = NULL;
    bst -> totalNodes = 0;
    return bst;
}

void inorderMaxHeap(BinaryTreeNode * node)
{
    if(node != NULL)
    {
        inorderMaxHeap(node -> left);
        if(node -> parent == NULL)
        {
            printf("Parent = NULL\t\t----->");
        }
        else
        {
            printf("Parent = (%s , %ld)\t----->",node -> parent -> dc_name, node -> parent -> total_patientes);
        }
        printf("\tChild = (%s , %ld)\n", node -> dc_name, node -> total_patientes);
        inorderMaxHeap(node -> right);
    }
}

void setParent(BinaryTreeNode * node,BinaryTreeNode * parent)
{
    if(node != NULL)
    {
        setParent(node -> left, node);
        if(node == parent)
        {
            node -> parent = NULL;
        }
        else
        {
            node -> parent = parent;

        }
        setParent(node -> right, node);
    }
}

BinaryTreeNode * BuildMaxHeap(BinaryTreeNode ** arr, BinaryTreeNode * node, size_t i, size_t n)
{

    if(i < n)
    {

        BinaryTreeNode * newBinaryTreeNode =  CreateBinaryTreeNode(arr[i] -> dc_name, arr[i] -> total_patientes);
        node = newBinaryTreeNode;

        node -> left = BuildMaxHeap(arr, node -> left, 2*i+1 ,n);;


        node -> right = BuildMaxHeap(arr, node -> right, 2*i+2 ,n);

        return node;

    }

    return node;
}

void MaxHeapify(BinaryTreeNode * root, BinaryTreeNode * node)
{
    if(root == NULL)
    {
        return;
    }
    MaxHeapify(root -> left, root);
    MaxHeapify(root -> right, root);
    if(node != NULL && (root -> total_patientes > node -> total_patientes))
    {
        swap((void **)&(root -> dc_name), (void **)&(node -> dc_name));
        swap((void **)&(root -> total_patientes), (void **)&(node -> total_patientes));
    }
}

void preorderMaxHeapify(BinaryTreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    MaxHeapify(root,NULL);
    preorderMaxHeapify(root -> left);
    preorderMaxHeapify(root -> right);
}

void GetKMaxValues(BinaryTreeNode * root, size_t k)
{
    for (size_t i = 0; i < k; i++)
    {
        if(root == NULL)
        {
            return;
        }
        printf("-> %s -> %ld\n",root -> dc_name, root -> total_patientes);
        root -> total_patientes = 0;
        preorderMaxHeapify(root);
    }

}


void DeallocateMaxHeap(BinaryTreeNode * temp)
{
    if(temp == NULL)
    {
        return;
    }
    DeallocateMaxHeap(temp -> left);
    DeallocateMaxHeap(temp -> right);
    free(temp);

}
