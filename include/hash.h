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
    char * recordID;
    char * patientFirstName;
    char * patientLastName;
    char * diseaseID;
    char * country;

    Date * entryDate;
    Date * exitDate;
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




PatientInfo * PatientInfo_Init(const char * recordID, const char * patientFirstName ,const char * patientLastName,const char * diseaseID, const char * country, Date * entryDate, Date * exitDate);
void PatientInfo_Print(const PatientInfo * info);
void PatientInfo_Deallocate(PatientInfo ** info);
Date * PatientInfo_EntryDate(const PatientInfo * info);
Date * PatientInfo_ExitDate(const PatientInfo * info);


long long Hash_Function_DJB2(unsigned char *str); // This function IS NOT mine, source: djb2 by Dan Bernstein
Hash * Hash_Init(size_t hashSize, size_t bucketSize);
void Hash_Insert(Hash * ht, long long number, PatientInfo * info);
void Hash_Print(const Hash * ht);
void Hash_Deallocate(Hash ** ht,bool remove);
// void Hash_Bye(Hash * ht,bool remove);
// long Hash_Compare_Dates_Times(const Hash * ht,long long number, Date * date1,Date * date2, Time * time1, Time *time2,long flag);

#endif
