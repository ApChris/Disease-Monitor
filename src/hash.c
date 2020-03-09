#include "../include/hash.h"


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
