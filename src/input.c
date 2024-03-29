#include "../include/input.h"

void ReadFile(const char * patientRecordsFile, Hash * patientHash, Hash_DC * diseaseHash, Hash_DC * countryHash)
{
    // for getline
    char * line = NULL;
    size_t length = 0;
    long read;
    FILE * file;


    // variables that I read from file
    char * recordID = NULL;
    char * patientFirstName = NULL;
    char * patientLastName = NULL;
    char * diseaseID = NULL;
    char * country = NULL;
    Date * entryDate = NULL;
    Date * exitDate = NULL;

    // for strtok
    char delimiters[] = " \n\t\r\v\f\n:,/.><[]{}|=+*@#$-";
    char * tok = NULL;

    // The struct that we are going to fill

    entryDate = malloc(sizeof(*entryDate));
    exitDate = malloc(sizeof(*exitDate));

    file = fopen(patientRecordsFile, "r");
    // printf("%s has been opened successfully!!\n\n", patientRecordsFile); // Feedback

    while((read = getline(&line,&length, file)) != -1)
    {
        PatientInfo * info = NULL;

        // Get recordID
        tok = strtok(line, " ");
        recordID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(recordID,(const char *)tok);

        // Read patientFirstName
        tok = strtok(NULL," ");
        patientFirstName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(patientFirstName,(const  char *)tok);

        // Read patientLastName
        tok = strtok(NULL," ");
        patientLastName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(patientLastName,(const  char *)tok);

        // Read diseaseID
        tok = strtok(NULL," ");
        diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(diseaseID,(const  char *)tok);

        // Read country
        tok = strtok(NULL," ");
        country = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(country,(const  char *)tok);


        // read entryDate
        tok = strtok(NULL,delimiters);
        entryDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> year = (long)atoi(tok);

        // read ExitDate
        tok = strtok(NULL,delimiters);

        // if current patient doessn't
        if(tok == NULL)
        {
            // Flag to fix the print function
            exitDate -> day = TAG;
            info = PatientInfo_Init(recordID,patientFirstName,patientLastName,diseaseID,country, entryDate, exitDate);      // create the
            Hash_Insert(patientHash,Hash_Function_DJB2((unsigned char *)recordID),info);
            Hash_DC_Insert(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID, entryDate, info);
            Hash_DC_Insert(countryHash,Hash_Function_DJB2((unsigned char *)country), country, entryDate, info);
            free(recordID);
            free(patientFirstName);
            free(patientLastName);
            free(diseaseID);
            free(country);

            continue;
        }

        exitDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> year = (long)atoi(tok);

        info = PatientInfo_Init(recordID,patientFirstName,patientLastName,diseaseID,country, entryDate, exitDate);      // create the
        Hash_Insert(patientHash,Hash_Function_DJB2((unsigned char *)recordID),info);
        Hash_DC_Insert(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID, entryDate, info);
        Hash_DC_Insert(countryHash,Hash_Function_DJB2((unsigned char *)country), country, entryDate, info);
        free(recordID);
        free(patientFirstName);
        free(patientLastName);
        free(diseaseID);
        free(country);


    }
    free(entryDate);
    free(exitDate);
    free(line);
    fclose(file);
    // printf("\n\n%s has been closed successfully!!\n", patientRecordsFile); // Feedback
}

void Print_Input(char * patientRecordsFile, long diseaseHashtableNumOfEntries, long countryHashtableNumOfEntries, long bucketSize)
{
    printf("\nYour input was:\n\n-> patientRecordsFile = %s\n-> diseaseHashtableNumOfEntries = %ld\n"
    "-> countryHashtableNumOfEntries = %ld\n-> bucketSize = %ld\n",patientRecordsFile,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);

}
