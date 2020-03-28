/*
	File Name 	: diseaseMonitor .c
	Author 		: Christoforos Apostolopoulos
	Project 	: Number -> 1 , System Programming 2019-2020
*/
#include <stdio.h>

#include "../include/hash.h"
#include "../include/input.h"
#include "../include/bst.h"
#include "../include/hashDC.h"
#include "../include/requests.h"

#include "../include/binaryMaxHeap.h"

int main(int argc, char const *argv[])
{
    // long error;                             // A variable that works as error flag


    long diseaseHashtableNumOfEntries;      // Size of disease Hash Table
    long countryHashtableNumOfEntries;      // Size of country Hash Table
    long bucketSize;                        // Bytes number of hashTable's bucket
    char * patientRecordsFile = NULL;              // patientRecordFile


    Hash * patientHash;


    if (argc != 9)                          // Check if we have !=9 arguments
    {
      printf("ERROR INPUT!!\nGive for example : ./diseaseMonitor -p small.txt -h1 10 -h2 10 -b 3\n");
      return -1;
    }

    for(int i = 1; i < argc; i++)           // Get arguments
    {
      if(strcmp(argv[i],"-p") == 0)         // patient FILE
      {
          patientRecordsFile = (char *)malloc(sizeof(char)*strlen(argv[i+1]) + 8);
          strcpy(patientRecordsFile,"../etc/");
          strcat(patientRecordsFile,argv[i+1]);

      }
      else if(strcmp(argv[i],"-h1") == 0)  // diseaseHashtableNumOfEntries
      {
         diseaseHashtableNumOfEntries = atoi(argv[i+1]);

      }
      else if(strcmp(argv[i],"-h2") == 0)  // countryHashtableNumOfEntries
      {
          countryHashtableNumOfEntries = atoi(argv[i+1]);
      }
      else if(strcmp(argv[i],"-b") == 0)  // Size of bucket
      {
          bucketSize = atoi(argv[i+1]);
      }
    }

    // Print just for feedback
    // Print_Input(patientRecordsFile,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);

    patientHash = Hash_Init(diseaseHashtableNumOfEntries, bucketSize);

    Hash_DC * diseaseHash = Hash_DC_Init(diseaseHashtableNumOfEntries, bucketSize);
    Hash_DC * countryHash = Hash_DC_Init(countryHashtableNumOfEntries, bucketSize);

    ReadFile(patientRecordsFile, patientHash, diseaseHash, countryHash);

    Read_Requests(diseaseHash, countryHash, patientHash);

    Hash_DC_Deallocate(&countryHash);
    Hash_DC_Deallocate(&diseaseHash);
    Hash_Deallocate(&patientHash,true);


    free(patientRecordsFile);
    return 0;
}
