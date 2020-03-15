#ifndef _HASHDC_H_
#define _HASHDC_H_
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"
#include "bst.h"

#define TRUE 1
#define FALSE 0
#define TAG 1400322


typedef struct BucketNode_DC
{
    size_t size;
    long long number;
    char * dc_name;
    BST * bst;
}BucketNode_DC;

typedef struct Bucket_DC
{
    size_t length;
    size_t size;
    BucketNode_DC ** nodes;
    struct Bucket_DC * next;
}Bucket_DC;


typedef struct Hash_DC
{
    size_t hashSize;
    size_t bucketSize;
    Bucket_DC ** bucketTable;
}Hash_DC;

#endif
