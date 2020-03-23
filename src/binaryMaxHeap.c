
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
    // BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();

    if(i < n)
    {
        // if(node == NULL)
        // {
        //     BinaryTreeNode * newBinaryTreeNode = CreateBinaryTreeNode(arr[i] -> dc_name, arr[i] -> total_patientes);
        //     node = newBinaryTreeNode;
        //     return node;
        // }


        BinaryTreeNode * newBinaryTreeNode =  CreateBinaryTreeNode(arr[i] -> dc_name, arr[i] -> total_patientes);
        node = newBinaryTreeNode;
        printf("%ld\n", arr[i] -> total_patientes);
            //


        node -> left = BuildMaxHeap(arr, node -> left, 2*i+1 ,n);;

        printf("12->%ld\n", arr[i] -> total_patientes);

        node -> right = BuildMaxHeap(arr, node -> right, 2*i+2 ,n);

        // right -> parent = node;
        printf("r->%ld\n", arr[i] -> total_patientes);
        return node;

    }

    return node;
}


BinaryTreeNode * BuildMaxHeap2(BinaryTreeNode ** heap, BinaryTreeNode * node, size_t i, size_t n)
{
    if(i < n)
    {

        BinaryTreeNode * newBinaryTreeNode =  CreateBinaryTreeNode(head -> dc_name, arr[i] -> total_patientes);
        node = newBinaryTreeNode;

        printf("%ld\n", head -> total_patientes);
        node -> left = BuildMaxHeap2(heap, node -> left, 2*i+1 ,n);;

        printf("12->%ld\n", head -> total_patientes);

        node -> right = BuildMaxHeap2(heap, node -> right, 2*i+2 ,n);

        // right -> parent = node;
        printf("r->%ld\n", arr[i] -> total_patientes);
        return node;

    }

    return node;
}
void swap2(BinaryTreeNode * node1, BinaryTreeNode * node2)
{
    BinaryTreeNode * temp = node1 -> left;
    node1 -> left = node2 -> left;
    node2 -> left = temp;

    temp = node1 -> right;
    node1 -> right = node2-> right;
    node2 -> right = temp;

    temp = node1 -> parent;
    node1 -> parent = node2-> parent;
    node2 -> parent = temp;
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
        swap(&(root -> dc_name), &(node -> dc_name));
        swap(&(root -> total_patientes), &(node -> total_patientes));
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

// BinaryTreeNode *right = PushMaxHeap(node -> right, dc_name, total_patientes);
//             node -> right = right;
//             right -> parent = node;

//
// void getCurrentPatients(BinaryTreeNode * node)
// {
//     if(node != NULL)
//     {
//         getCurrentPatients(node -> left);
//         if(node -> info -> exitDate -> day == TAG)
//         {
//             tResult++;
//             PatientInfo_Print(node -> info);
//         }
//         getCurrentPatients(node -> right);
//     }
// }
//
// void getPatientsInThatPeriod(BinaryTreeNode * node, Date * entryDate, Date * exitDate)
// {
//     if(node != NULL)
//     {
//         getPatientsInThatPeriod(node -> left, entryDate, exitDate);
//         if( (Compare_Date(node -> info -> entryDate, entryDate) != -1) && (Compare_Date(node -> info -> exitDate, exitDate) != 1) )
//         {
//             tResult++;
//             PatientInfo_Print(node -> info);
//         }
//         getPatientsInThatPeriod(node -> right, entryDate, exitDate);
//     }
// }
//
// // A function which finds the patients from specific country in spesific period
// void getPatientsInThatPeriod_SpecifiCountry(BinaryTreeNode * node, Date * entryDate, Date * exitDate, char * country)
// {
//     if(node != NULL)
//     {
//         getPatientsInThatPeriod_SpecifiCountry(node -> left, entryDate, exitDate, country);
//         if(!strcmp(node -> info -> country, country))
//         {
//             // check date
//             if( (Compare_Date(node -> info -> entryDate, entryDate) != -1) && (Compare_Date(node -> info -> exitDate, exitDate) != 1) )
//             {
//                 tResult++;
//                 PatientInfo_Print(node -> info);
//             }
//         }
//
//         getPatientsInThatPeriod_SpecifiCountry(node -> right, entryDate, exitDate, country);
//     }
// }
//
// BinaryTreeNode * PushMaxHeap(BinaryTreeNode * node, char * dc_name, size_t total_patientes)
// {
//     if(node == NULL)
//     {
//         BinaryTreeNode * newBinaryTreeNode = CreateBinaryTreeNode(dc_name, total_patientes);
//         node = newBinaryTreeNode;
//         return node;
//     }
//
//     if(total_patientes <= node -> total_patientes)
//     {
//         if(node -> right == NULL && node -> left != NULL)
//         {
//             BinaryTreeNode *right = PushMaxHeap(node -> right, dc_name, total_patientes);
//             node -> right = right;
//             right -> parent = node;
//
//             if(right -> parent -> total_patientes < node -> right -> total_patientes)
//             {
//                 printf("mphka edw1\n");
//                 swap(&(right -> parent -> dc_name), &(node -> right -> dc_name));
//                 swap(&(right -> parent -> total_patientes), &(node -> right -> total_patientes));
//
//                 // printf("Pasdasd = %s , %ld\n",right -> parent -> dc_name, right -> parent -> total_patientes);
//                 // printf("123123 = %s , %ld\n",node -> right -> dc_name, node -> right -> total_patientes);
//             }
//         }
//         else
//         {
//             BinaryTreeNode *left = PushMaxHeap(node -> left, dc_name, total_patientes);
//             node -> left = left;
//             left -> parent = node;
//
//             if(left -> parent -> total_patientes < node -> left -> total_patientes)
//             {
//                 printf("mphka edw2\n");
//
//                 swap(&(left -> parent -> dc_name), &(node -> left -> dc_name));
//                 swap(&(left -> parent -> total_patientes), &(node -> left -> total_patientes));
//             }
//         }
//
//     }
//     else
//     {
//         if(node -> left == NULL && node -> right != NULL)
//         {
//             BinaryTreeNode *left = PushMaxHeap(node -> left, dc_name, total_patientes);
//             node -> left = left;
//             left -> parent = node;
//
//             if(left -> parent -> total_patientes < node -> left -> total_patientes)
//             {
//                 printf("mphka edw3\n");
//
//                 swap(&(left -> parent -> dc_name), &(node -> left -> dc_name));
//                 swap(&(left -> parent -> total_patientes), &(node -> left -> total_patientes));
//             }
//         }
//         else
//         {
//             BinaryTreeNode *right = PushMaxHeap(node -> right, dc_name, total_patientes);
//             node -> right = right;
//             right -> parent = node;
//
//
//                 if(right -> parent -> total_patientes < node -> right -> total_patientes)
//                 {
//                     printf("mphka edw4\n");
//                     swap(&(right -> parent -> dc_name), &(node -> right -> dc_name));
//                     swap(&(right -> parent -> total_patientes), &(node -> right -> total_patientes));
//
//                     // printf("Pasdasd = %s , %ld\n",right -> parent -> dc_name, right -> parent -> total_patientes);
//                     // printf("123123 = %s , %ld\n",node -> right -> dc_name, node -> right -> total_patientes);
//                 }
//         }
//
//
//
//     }
//     return node;
// }



//////////////////////////////////////////////////////////////////////////////////////////
