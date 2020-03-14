/*
	File Name 	: diseaseMonitor .c
	Author 		: Christoforos Apostolopoulos
	Project 	: Number -> 1 , System Programming 2019-2020
*/
#include <stdio.h>

#include "../include/hash.h"
#include "../include/input.h"

int main(int argc, char const *argv[])
{
    long result;                            // A variable to hold values from functions returns
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
          patientRecordsFile = (char *)malloc(sizeof(char)*strlen(argv[i+1]) + 5);
          strcpy(patientRecordsFile,"etc/");
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
    Print_Input(patientRecordsFile,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);

    patientHash = Hash_Init(diseaseHashtableNumOfEntries, bucketSize);



    // PatientInfo * info;
    // info = PatientInfo_Init("123","Jodi","Carey","COVID-2019","China", dateArg, dateArg1);      // create the
    // Hash_Insert(patientHash,Hash_Function_DJB2((unsigned char *)"COVID-2019"),info);            // Insert in  Hash

    // info = PatientInfo_Init("53","Michael","Crawford","MERS-COV","USA", dateArg, dateArg1);      // create the
    // Hash_Insert(patientHash,Hash_Function_DJB2((unsigned char *)"MERS-COV"),info);            // Insert in  Hash

    // Hash_Print(patientHash);

    result = ReadFile(patientRecordsFile, patientHash);
    Hash_Print(patientHash);

    Hash_Deallocate(&patientHash,true);
    // Patient_PatientInfo_Deallocate(&info);
    free(patientRecordsFile);
    return 0;
}
