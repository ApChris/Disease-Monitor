#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <stdio.h> 
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"

#define TRUE 1
#define FALSE 0


typedef struct PatientInfo
{
    char * fullName;
    char * lastName;
    char * disease;
    char * country;

    Date * dateEntry;
    Date * dateExit;
}PatientInfo;

typedef struct Patient
{
    size_t length;
    size_t size;
    PatientInfo ** info;
    struct Patient * next;
}Patient;


typedef struct BucketNode
{
        size_t size;
        long long number;
        Patient * head;
}BucketNode;



typedef struct Bucket
{
    size_t length;
    size_t size;
    BucketNode ** nodes;
    struct Bucket * next;
}Bucket;


typedef struct Hash
{
    size_t hashSize;
    size_t bucketSize;
    Bucket ** bucketTable;
}Hash;





// TransactionInfo * TransactionInfo_Init(const char * transactionID,const char * senderWalletID,const char * receiverWalletID,long value,Date * date,Time * time);
// void TransactionInfo_Deallocate(TransactionInfo ** info);
// void TransactionInfo_Print(const TransactionInfo * info);
// Date * TransactionInfo_Date(const TransactionInfo * info);
// Time * TransactionInfo_Time(const TransactionInfo * info);


// long long Hash_Function_DJB2(unsigned char *str); // This function IS NOT mine, source: djb2 by Dan Bernstein
Hash * Hash_Init(size_t hashSize, size_t bucketSize);
// void Hash_Insert(Hash * ht, long long number, TransactionInfo * info);
// void Hash_Print(const Hash * ht);
// void Hash_Deallocate(Hash ** ht,bool remove);
// void Hash_Bye(Hash * ht,bool remove);
// long Hash_Compare_Dates_Times(const Hash * ht,long long number, Date * date1,Date * date2, Time * time1, Time *time2,long flag);

#endif
