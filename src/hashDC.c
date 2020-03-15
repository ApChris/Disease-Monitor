#include "../include/hashDC.h"

// ----------------------------- BUCKET NODE -----------------------------
static BucketNode_DC * BucketNode_Init(long long number, size_t size, const char * dc_name)
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
    bucketnode -> bst = NULL;

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
