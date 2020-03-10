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

PatientInfo * PatientInfo_Init(const char * fullName,const char * lastName,const char * disease, const char * country, Date * dateEntry, Date * dateExit)
{
    PatientInfo * info;
    int char_counter = 0;

    if( (info = malloc(sizeof(*info))) == NULL)
    {
        perror("Error(PatientInfo_Init): ");
        exit(EXIT_FAILURE);
    }

    // TransactionID
    char_counter = strlen(fullName) + 1;
    if( (info -> fullName = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(TransactionInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> fullName,fullName);
    info -> fullName[char_counter] = '\0';


    // lastName
    char_counter = strlen(lastName) + 1;
    if( (info -> lastName = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(TransactionInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> lastName,lastName);
    info -> lastName[char_counter] = '\0';


    // disease
    char_counter = strlen(disease) + 1;
    if( (info -> disease = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(TransactionInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> disease,disease);
    info -> disease[char_counter] = '\0';

    // country
    char_counter = strlen(country) + 1;
    if( (info -> country = malloc(1 + sizeof(char) * char_counter)) == NULL)
    {
        perror("Error(TransactionInfo_Init): ");
        exit(EXIT_FAILURE);
    }
    strcpy(info -> country,country);
    info -> country[char_counter] = '\0';


    // Date
    if( (info -> dateEntry = malloc(sizeof(* dateEntry))) == NULL)
    {
        perror("Error(PatientInfo): ");
        exit(EXIT_FAILURE);
    }
    info -> dateEntry -> day = dateEntry -> day;
    info -> dateEntry -> month = dateEntry -> month;
    info -> dateEntry -> year = dateEntry -> year;


    // Date
    if((info -> dateExit = malloc(sizeof(* dateExit))) == NULL)
    {
        perror("Error(PatientInfo): ");
        exit(EXIT_FAILURE);
    }
    info -> dateExit -> day = dateExit -> day;
    info -> dateExit -> month = dateExit -> month;
    info -> dateExit -> year = dateExit -> year;

    return info;
}


void PatientInfo_Print(const PatientInfo * info)
{
    printf("%s %s %s %s %ld-%ld-%ld %ld-%ld-%ld\n",info -> fullName, info -> lastName,
     info -> disease, info -> country, info -> dateEntry -> day, info -> dateEntry -> month, info -> dateEntry -> year, info -> dateExit -> day, info -> dateExit -> month, info -> dateExit -> year);
}

void PatientInfo_Deallocate(PatientInfo ** info)
{
    free((*info) -> fullName);
    free((*info) -> lastName);
    free((*info) -> disease);
    free((*info) -> country);
    free((*info) -> dateEntry);
    free((*info) -> dateExit);

    free(*info);
    *info = NULL;
}

Date * PatientInfo_DateEntry(const PatientInfo * info)
{
    return info -> dateEntry;
}


// ----------------------------- PATIENT -----------------------------
static Patient * Patient_Init(size_t size)
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

static void Patient_Insert(Patient * patient, PatientInfo * info)
{
    if( (patient -> length) < (patient -> size) )
    {
        patient -> info[patient -> length] = info;
        ++patient->length;
    }
    else if(patient -> next != NULL)
    {
        Patient_Insert(patient->next, info);
    }
    else
    {
        patient -> next = Patient_Init(patient -> size);
        Patient_Insert(patient -> next, info);
    }
}

// ----------------------------- BUCKET NODE -----------------------------
static BucketNode * BucketNode_Init(long long number, size_t size)
{
    BucketNode * bucketnode = malloc(sizeof(*bucketnode));

    if(bucketnode == NULL)
    {
        perror("Error(Wallet_Init): ");
        exit(EXIT_FAILURE);
    }

    bucketnode -> number = number;
    bucketnode -> size = size;
    bucketnode -> head = NULL;

    return bucketnode;
}

static void BucketNode_Insert(BucketNode * bucketnode, PatientInfo * info)
{
    if(bucketnode -> head == NULL)
    {
        bucketnode -> head = Patient_Init(bucketnode -> size);
    }
    Patient_Insert(bucketnode -> head, info);

}


// ----------------------------- BUCKET -----------------------------
static Bucket * Bucket_Init(size_t bucketSize)
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

static void Bucket_Insert(Bucket * bucket, long long number, PatientInfo * info)
{
    size_t i = 0;
    while(i < bucket -> length)
    {
        if(bucket -> nodes[i] -> number == number) // If already exists
        {
            BucketNode_Insert(bucket -> nodes[i], info);
            return;
        }
        i++;
    }
    if(bucket -> next != NULL) // Go to last bucket
    {
        Bucket_Insert(bucket -> next, number , info);
    }
    else if(bucket -> length < bucket -> size)  // If the number that can hold this bucket is < of the total number of nodes that can hold then
    {
        bucket -> nodes[bucket->length] = BucketNode_Init(number, bucket -> size);
        BucketNode_Insert(bucket -> nodes[bucket -> length], info);
        ++bucket->length;

    }
    else // That means that we are at the end of buckets and we are going to create a new bucket because the last entry can't be put in previous last bucket
    {

        bucket -> next = Bucket_Init(bucket -> size);
        Bucket_Insert(bucket -> next, number, info);
    }

}


// ----------------------------- HASH -----------------------------------------

Hash * Hash_Init(size_t hashSize, size_t bucketSize)
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



void Hash_Insert(Hash * ht, long long number, PatientInfo * info)
{

    size_t position = number % ht -> hashSize;

    if(ht -> bucketTable[position] == NULL)
    {
        ht -> bucketTable[position] = Bucket_Init(ht -> bucketSize);
    }
    Bucket_Insert(ht -> bucketTable[position], number, info);
}
