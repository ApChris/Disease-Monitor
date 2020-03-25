#ifndef _HASHDC_H_
#define _HASHDC_H_
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


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


Hash_DC * Hash_DC_Init(size_t hashSize, size_t bucketSize);
void Hash_DC_Insert(Hash_DC * ht, long long number, const char * dc_name, Date * entryDate, PatientInfo * info);
void Hash_DC_Print(const Hash_DC * ht);
void Hash_DC_CurrentActivePatients(const Hash_DC * ht);
void Hash_DC_AllPatients(const Hash_DC * ht);
BST * Hash_DC_Get_BSTroot(const Hash_DC * ht,long long number, const char * dc_name);
void Hash_DC_AllPatientsInThatPeriod(const Hash_DC * ht,Date * entryDate, Date * exitDate);
void Hash_DC_Deallocate(Hash_DC ** ht);
#endif
