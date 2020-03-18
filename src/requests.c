
#include "../include/requests.h"

long Request_6(Hash * patientHash, char * tok)
{

    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    tok = strtok(NULL,delimiters);
    PatientInfo * info = Hash_Find_Patient(patientHash,Hash_Function_DJB2((unsigned char *)tok), tok);
    if(info == NULL)
    {
        printf("This recordID doesn't exist. Please try again!!\n");
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

    }
}


static long Read_Requests_Parse(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash, char * request)
{

    long result = 0;
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
        else if(strcmp(tok,"insertPatientRecord") == 0)
        {
            // result = Request_5(hashSender,tok);
            printf("5\n");

        }
        else if(strcmp(tok,"recordPatientExit") == 0)
        {
            result = Request_6(patientHash,tok);
            if(result != -1)
            {
                printf("\nBalance = %ld\n\n",result);
                printf("Give another:\n");
            }
            result = 0;
            printf("6\n");

        }
        else if(strcmp(tok,"numCurrentPatients") == 0)
        {
            // result = Request_7(wh,tok);

            printf("7\n");

        }
        else if(strcmp(tok,"exit") == 0)
        {
            printf("Promt has been closed!!!\n");
            result = -1;
            return result;;

        }
        return result;

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
        printf("%s\n",request);
        if(Read_Requests_Parse(diseaseHash, countryHash, patientHash, request) < 0)
        {
            break;
        }
    }
}
