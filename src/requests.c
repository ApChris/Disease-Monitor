
#include "../include/requests.h"


bool Request_5(Hash * patientHash, Hash_DC * diseaseHash, Hash_DC * countryHash, char * tok)
{

    char * recordID = NULL;
    char * patientFirstName = NULL;
    char * patientLastName = NULL;
    char * diseaseID = NULL;
    char * country = NULL;
    Date * entryDate = NULL;
    Date * exitDate = NULL;

    entryDate = malloc(sizeof(*entryDate));
    exitDate = malloc(sizeof(*exitDate));

    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    PatientInfo * info = NULL;

    // Get recordID
    tok = strtok(NULL, " ");
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

        return true;
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
    return true;
}


bool Request_6(Hash * patientHash, char * tok)
{

    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    tok = strtok(NULL,delimiters);
    PatientInfo * info = Hash_Find_Patient(patientHash,Hash_Function_DJB2((unsigned char *)tok), tok);
    if(info == NULL)
    {
        printf("This recordID doesn't exist. Please try again!!\n");
        return false;
    }
    else
    {
        // Date * exitDate = (Date *)malloc(sizeof(Date));
        printf("------> Before Update <------\n");
        PatientInfo_Print(info);
        printf("------> After Update <-------\n");
        tok = strtok(NULL,delimiters);
        info -> exitDate -> day = (long)atoi(tok);
        tok = strtok(NULL,delimiters);
        info -> exitDate -> month = (long)atoi(tok);
        tok = strtok(NULL,delimiters);
        info -> exitDate -> year = (long)atoi(tok);
        PatientInfo_Print(info);
        return true;
    }
}

bool Request_7(Hash_DC * diseaseHash, char * tok)
{

    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|=+*@#$;";
    tok = strtok(NULL," \n");
    if(tok == NULL)
    {
        printf("This recordID doesn't exist. Please try again!!\n");
        return true;
    }
    else
    {
        printf("%s\n",tok);
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)tok), tok);
        inorder(bst -> root);
        return true;
    }
}


static long Read_Requests_Parse(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash, char * request)
{

    bool result;
    char * tok;
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$";
    tok = strtok(request,delimiters);

    if(tok != NULL)
    {
        if(strcmp(tok,"globalDiseaseStats") == 0)
        {
            // result = Request_1(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            // printf("%s\n",tok);
            printf("1\n");

        }
        else if(strcmp(tok,"diseaseFrequency") == 0)
        {
            printf("2\n");
            // tok = Request_2(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            // tok = Request_2(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            // printf("%s\n",tok);

        }
        else if(strcmp(tok,"topk-Diseases") == 0)
        {
            tok = strtok(NULL," ");
            //tok = strtok(NULL,delimiters);

            // char * fileName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
            // strcpy(fileName,(const char *)tok);
            // fileName[1 + sizeof(char) * strlen(tok)] = '\0';
            // printf("%s\n",fileName);
            // result = Request_3(fileName,hashSender,hashReceiver,wh,dateArg,timeArg,root);
            printf("3\n");
        }
        else if(strcmp(tok,"topk-Countries") == 0)
        {
            printf("4\n");

        }
        else if(!strcmp(tok,"insertPatientRecord"))
        {
            printf("edwww\n");
            if(Request_5(patientHash, diseaseHash, countryHash, tok))
            {
                printf("\nPatient has been inserted successfully\n");
            }
            printf("bghka\n");
            return false;

        }
        else if(strcmp(tok,"recordPatientExit") == 0)
        {
            if(Request_6(patientHash,tok))
            {
                printf("\nExitDate has been added successfully!\n");
            }
            printf("6\n");
            return false;

        }
        else if(strcmp(tok,"numCurrentPatients") == 0)
        {
            Request_7(diseaseHash,tok);

            printf("7\n");

        }
        else if(strcmp(tok,"exit") == 0)
        {
            printf("Promt has been closed!!!\n");
            return true;

        }
        return false;

    }

}



void Read_Requests(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash)
{
    char * request = NULL;
    size_t length;
    long read;
    printf("---------> Promt <---------\n");
    while((read = getline(&request,&length, stdin)) != -1)
    {
        if(Read_Requests_Parse(diseaseHash, countryHash, patientHash, request))
        {
            break;
        }
    }
}
