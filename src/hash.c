#include "../include/hash.h"


long long Hash_Function_DJB2(unsigned char *str) // This function IS NOT mine, source: djb2 by Dan Bernstein
{
    unsigned long hash = 5381;
    int c;

    while( (c = *str++) != '\0')
    {
        hash = ((hash << 5) + hash) + c;

    }
    return hash;
}



// ----------------------------- PATIENTINFO -----------------------------

PatientInfo * Patient_PatientInfo_Init(const char * recordID, const char * patientFirstName ,const char * patientLastName,const char * diseaseID, const char * country, Date * entryDate, Date * exitDate)
{
    PatientInfo * info;
    int char_counter = 0;

    if( (info = malloc(sizeof(*info))) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }

    // recordID
    char_counter = strlen(recordID) + 1;
    if( (info -> recordID = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> recordID,recordID);
    info -> recordID[char_counter] = '\0';


    // patientFirstName
    char_counter = strlen(patientFirstName) + 1;
    if( (info -> patientFirstName = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> patientFirstName,patientFirstName);
    info -> patientFirstName[char_counter] = '\0';


    // patientLastName
    char_counter = strlen(patientLastName) + 1;
    if( (info -> patientLastName = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> patientLastName,patientLastName);
    info -> patientLastName[char_counter] = '\0';


    // diseaseID
    char_counter = strlen(diseaseID) + 1;
    if( (info -> diseaseID = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> diseaseID,diseaseID);
    info -> diseaseID[char_counter] = '\0';

    // country
    char_counter = strlen(country) + 1;
    if( (info -> country = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> country,country);
    info -> country[char_counter] = '\0';


    // entryDate
    if( (info -> entryDate = malloc(sizeof(* entryDate))) == NULL)
    {
        perror("Error(PatientInfo): ");
        exit(EXIT_FAILURE);
    }
    info -> entryDate -> day = entryDate -> day;
    info -> entryDate -> month = entryDate -> month;
    info -> entryDate -> year = entryDate -> year;


    // Date
    if((info -> exitDate = malloc(sizeof(* exitDate))) == NULL)
    {
        perror("Error(PatientInfo): ");
        exit(EXIT_FAILURE);
    }
    info -> exitDate -> day = exitDate -> day;
    info -> exitDate -> month = exitDate -> month;
    info -> exitDate -> year = exitDate -> year;

    return info;
}


void Patient_PatientInfo_Print(const PatientInfo * info)
{
    printf("%s %s %s %s %s %ld-%ld-%ld %ld-%ld-%ld\n",info -> recordID, info -> patientFirstName, info -> patientLastName,
     info -> diseaseID, info -> country, info -> entryDate -> day, info -> entryDate -> month, info -> entryDate -> year, info -> exitDate -> day, info -> exitDate -> month, info -> exitDate -> year);
}

void Patient_PatientInfo_Deallocate(PatientInfo ** info)
{
    free((*info) -> recordID);
    free((*info) -> patientFirstName);
    free((*info) -> patientLastName);
    free((*info) -> diseaseID);
    free((*info) -> country);
    free((*info) -> entryDate);
    free((*info) -> exitDate);

    free(*info);
    *info = NULL;
}

Date * Patient_PatientInfo_EntryDate(const PatientInfo * info)
{
    return info -> entryDate;
}

Date * Patient_PatientInfo_ExitDate(const PatientInfo * info)
{
    return info -> exitDate;
}

// ----------------------------- PATIENT -----------------------------
static Patient * Patient_Patient_Init(size_t size)
{
    size_t i = 0;
    Patient * patient = malloc(sizeof(*patient));

    if(patient == NULL)
    {
        perror("Error(Patient): ");
        exit(EXIT_FAILURE);
    }
    patient -> length = 0;
    patient -> size = size;
    patient -> next = NULL;
    patient -> info = malloc(sizeof(*patient -> info) * size);

    if(patient -> info == NULL)
    {
        perror("Error(Patient): ");
        exit(EXIT_FAILURE);
    }
    while(i < size)
    {
        patient -> info[i] = NULL;
        i++;
    }
    return patient;
}

static void Patient_Patient_Insert(Patient * patient, PatientInfo * info)
{
    if( (patient -> length) < (patient -> size) )
    {
        patient -> info[patient -> length] = info;
        ++patient->length;
    }
    else if(patient -> next != NULL)
    {
        Patient_Patient_Insert(patient->next, info);
    }
    else
    {
        patient -> next = Patient_Patient_Init(patient -> size);
        Patient_Patient_Insert(patient -> next, info);
    }
}

// ----------------------------- BUCKET NODE -----------------------------
static BucketNode * Patient_BucketNode_Init(long long number, size_t size)
{
    BucketNode * bucketnode = malloc(sizeof(*bucketnode));

    if(bucketnode == NULL)
    {
        perror("Error(Patient_BucketNode_Init): ");
        exit(EXIT_FAILURE);
    }

    bucketnode -> number = number;
    bucketnode -> size = size;
    bucketnode -> head = NULL;

    return bucketnode;
}

static void Patient_BucketNode_Insert(BucketNode * bucketnode, PatientInfo * info)
{
    if(bucketnode -> head == NULL)
    {
        bucketnode -> head = Patient_Patient_Init(bucketnode -> size);
    }
    Patient_Patient_Insert(bucketnode -> head, info);

}


// ----------------------------- BUCKET -----------------------------
static Bucket * Patient_Bucket_Init(size_t bucketSize)
{
    size_t i = 0;
    Bucket * bucket;
    bucket = malloc(sizeof(*bucket));
    if(bucket == NULL)
    {
        perror("Error(Bucket_Init): ");
        exit(EXIT_FAILURE);
    }

    bucket -> length  = 0;
    bucket -> size = bucketSize;
    bucket -> nodes = malloc(sizeof(*bucket -> nodes) * bucketSize);
    bucket -> next = NULL;

    if(bucket -> nodes == NULL)
    {
        perror("Error(Bucket_Init): ");
        exit(EXIT_FAILURE);
    }

    while(i < bucketSize)    // Init every pointer to null
    {
        bucket -> nodes[i] = NULL;
        i++;
    }

    return bucket;
}

static void Patient_Bucket_Insert(Bucket * bucket, long long number, PatientInfo * info)
{
    size_t i = 0;
    while(i < bucket -> length)
    {
        if(bucket -> nodes[i] -> number == number) // If already exists
        {
            Patient_BucketNode_Insert(bucket -> nodes[i], info);
            return;
        }
        i++;
    }
    if(bucket -> next != NULL) // Go to last bucket
    {
        Patient_Bucket_Insert(bucket -> next, number , info);
    }
    else if(bucket -> length < bucket -> size)  // If the number that can hold this bucket is < of the total number of nodes that can hold then
    {
        bucket -> nodes[bucket->length] = Patient_BucketNode_Init(number, bucket -> size);
        Patient_BucketNode_Insert(bucket -> nodes[bucket -> length], info);
        ++bucket->length;

    }
    else // That means that we are at the end of buckets and we are going to create a new bucket because the last entry can't be put in previous last bucket
    {

        bucket -> next = Patient_Bucket_Init(bucket -> size);
        Patient_Bucket_Insert(bucket -> next, number, info);
    }

}


// ----------------------------- HASH -----------------------------------------

Hash * Patient_Hash_Init(size_t hashSize, size_t bucketSize)
{
    size_t i = 0;                                        // init a counter for buckettable

    size_t tempBucketSize;                               // That variable holds the number of BucketNodes
    tempBucketSize = bucketSize / sizeof(BucketNode);    // The bytes that I took from user div sizeof Bucket

    Hash * ht;                                           // A pointer to Hash struct
    ht = (Hash *)malloc(sizeof(*ht));

    if(ht == NULL)                                       // Check for error
    {
        perror("Error(Hash_Init): ");
        exit(EXIT_FAILURE);
    }

    ht -> hashSize = hashSize;                                          // Init Hash size
    ht -> bucketSize = tempBucketSize;                                  // Init Bucket size
    ht -> bucketTable = malloc(sizeof(*ht -> bucketTable) * hashSize);  // Create space for hashSize pointers to BucketNodes

    if(ht -> bucketTable == NULL)                       // Check for error
    {
        perror("Error(Hash_Init): ");
        exit(EXIT_FAILURE);
    }

    while(i < hashSize)                                 // Init every pointer to null
    {
        ht -> bucketTable[i] = NULL;
        i++;
    }
    printf("\nHash_Init has been completed successfully!\n\n");        // Feedback

    return ht;                                          // Return pointer
}



void Patient_Hash_Insert(Hash * ht, long long number, PatientInfo * info)
{

    size_t position = number % ht -> hashSize;

    if(ht -> bucketTable[position] == NULL)
    {
        ht -> bucketTable[position] = Patient_Bucket_Init(ht -> bucketSize);
    }
    Patient_Bucket_Insert(ht -> bucketTable[position], number, info);
}
