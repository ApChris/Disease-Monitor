#include "../include/hashDC.h"

// ----------------------------- BUCKET NODE -----------------------------
static BucketNode_DC * BucketNode_DC_Init(long long number, size_t size, const char * dc_name, Date * entryDate, PatientInfo * info)
{
    long counter;
    BucketNode_DC * bucketnode = malloc(sizeof(*bucketnode));

    if(bucketnode == NULL)
    {
        perror("Error(Patient_BucketNode_Init): ");
        exit(EXIT_FAILURE);
    }

    bucketnode -> number = number;
    bucketnode -> size = size;
    bucketnode -> bst = CreateBST();;
    bucketnode -> bst -> root = PushBST(bucketnode -> bst -> root, entryDate, info);

    counter = strlen(dc_name) + 1;
    bucketnode -> dc_name = malloc(1 + sizeof(char) * counter);
    strcpy(bucketnode -> dc_name,dc_name);


    return bucketnode;
}


// ----------------------------- BUCKET -----------------------------
static Bucket_DC * Bucket_DC_Init(size_t bucketSize)
{
    size_t i = 0;
    Bucket_DC * bucket;
    bucket = malloc(sizeof(*bucket));
    if(bucket == NULL)
    {
        perror("Error(Bucket_DC_Init): ");
        exit(EXIT_FAILURE);
    }

    bucket -> length  = 0;
    bucket -> size = bucketSize;
    bucket -> nodes = malloc(sizeof(*bucket -> nodes) * bucketSize);
    bucket -> next = NULL;

    if(bucket -> nodes == NULL)
    {
        perror("Error(Bucket_DC_Init): ");
        exit(EXIT_FAILURE);
    }

    while(i < bucketSize)    // Init every pointer to null
    {
        bucket -> nodes[i] = NULL;
        i++;
    }

    return bucket;
}



static void Bucket_DC_Insert(Bucket_DC * bucket, long long number,const char * dc_name, Date * entryDate, PatientInfo * info)
{
    size_t i = 0;
    while(i < bucket -> length)
    {
        if(bucket -> nodes[i] -> number == number) // If already exists
        {
            // BucketNode_DC_Insert(bucket -> nodes[i], info);
            bucket -> nodes[i] -> bst -> root = PushBST(bucket -> nodes[i] -> bst -> root, entryDate, info);
            // bucket -> nodes[i] -> info = info;
            return;
        }
        i++;
    }
    if(bucket -> next != NULL) // Go to last bucket
    {
        Bucket_DC_Insert(bucket -> next, number ,dc_name, entryDate, info);
    }
    else if(bucket -> length < bucket -> size)  // If the number that can hold this bucket is < of the total number of nodes that can hold then
    {
        bucket -> nodes[bucket->length] = BucketNode_DC_Init(number, bucket -> size, dc_name, entryDate, info);
        // BucketNode_DC_Insert(bucket -> nodes[bucket -> length], dc_name, entryDate, info);
        ++bucket->length;

    }
    else // That means that we are at the end of buckets and we are going to create a new bucket because the last entry can't be put in previous last bucket
    {

        bucket -> next = Bucket_DC_Init(bucket -> size);
        Bucket_DC_Insert(bucket -> next, number, dc_name, entryDate, info);
    }

}

static void Bucket_DC_Print(const Bucket_DC * bucket)
{
    size_t i = 0;
    if(bucket == NULL)
    {
        return;
    }
    while(i < bucket -> length)
    {
        printf("%s\n", bucket -> nodes[i] -> dc_name);
        // PatientInfo_Print(bucket -> nodes[i] -> info);
        // printf("%ld-%ld-%ld\n", bucket -> nodes[i] -> bst -> root -> entryDate -> day, bucket -> nodes[i] -> bst -> root -> entryDate -> month, bucket -> nodes[i] -> bst -> root -> entryDate -> year);
        i++;
    }
    Bucket_DC_Print(bucket -> next);
}


static BST * Bucket_DC_Get_BSTroot(const Bucket_DC * bucket, long long number, const char * dc_name)
{
    size_t i = 0;

    if(bucket == NULL)
    {
        return 0;
    }
    while(i < bucket -> length)
    {

        if((bucket -> nodes[i] -> number == number) && (!strcmp(bucket -> nodes[i] -> dc_name, dc_name)))
        {
            return bucket -> nodes[i] -> bst;
        }
        i++;
    }
    if(bucket -> next != NULL)
    {
        Bucket_DC_Get_BSTroot(bucket -> next, number, dc_name);
    }
    return NULL;

}
// ----------------------------- HASH_DC -----------------------------------------

Hash_DC * Hash_DC_Init(size_t hashSize, size_t bucketSize)
{
    size_t i = 0;                                        // init a counter for buckettable

    size_t tempBucketSize;                               // That variable holds the number of BucketNodes
    tempBucketSize = bucketSize / sizeof(BucketNode_DC);    // The bytes that I took from user div sizeof Bucket

    Hash_DC * ht;                                           // A pointer to Hash_DC struct
    ht = (Hash_DC *)malloc(sizeof(*ht));

    if(ht == NULL)                                       // Check for error
    {
        perror("Error(Hash_DC_Init): ");
        exit(EXIT_FAILURE);
    }

    ht -> hashSize = hashSize;                                          // Init Hash_DC size
    ht -> bucketSize = tempBucketSize;                                  // Init Bucket size
    ht -> bucketTable = malloc(sizeof(*ht -> bucketTable) * hashSize);  // Create space for hashSize pointers to BucketNodes

    if(ht -> bucketTable == NULL)                       // Check for error
    {
        perror("Error(Hash_DC_Init): ");
        exit(EXIT_FAILURE);
    }

    while(i < hashSize)                                 // Init every pointer to null
    {
        ht -> bucketTable[i] = NULL;
        i++;
    }
    printf("\nHash_DC_Init has been completed successfully!\n\n");        // Feedback

    return ht;                                          // Return pointer
}


void Hash_DC_Insert(Hash_DC * ht, long long number, const char * dc_name, Date * entryDate, PatientInfo * info)
{

    size_t position = number % ht -> hashSize;

    if(ht -> bucketTable[position] == NULL)
    {
        ht -> bucketTable[position] = Bucket_DC_Init(ht -> bucketSize);
    }
    Bucket_DC_Insert(ht -> bucketTable[position], number,dc_name, entryDate, info);
}

void Hash_DC_Print(const Hash_DC * ht)
{
    size_t i = 0;
    while(i < ht -> hashSize)
    {
        printf("Position %zu:\n", i);
        Bucket_DC_Print(ht -> bucketTable[i]);
        printf("\n");
        i++;
    }
}


BST * Hash_DC_Get_BSTroot(const Hash_DC * ht,long long number, const char * dc_name)
{
    size_t position = number % ht -> hashSize;
    return Bucket_DC_Get_BSTroot(ht -> bucketTable[position],number,dc_name);
}
