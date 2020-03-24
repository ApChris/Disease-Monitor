
#include "../include/requests.h"

bool Request_1( Hash_DC * diseaseHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    tok = strtok(NULL,delimiters);
    if(tok == NULL)
    {
        printf("Arguments missing!!\n");
        Hash_DC_AllPatients(diseaseHash);
        return true;
    }
    else
    {
        Date * entryDate = NULL;
        Date * exitDate = NULL;
        entryDate = malloc(sizeof(*entryDate));
        exitDate = malloc(sizeof(*exitDate));

        // entryDate
        entryDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> year = (long)atoi(tok);

        // exitDate
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(entryDate);
            free(exitDate);
            printf("You have to add exitDate! Please try again!\n");
            return true;
        }

        exitDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> year = (long)atoi(tok);
        printf("%ld-%ld-%ld\n",entryDate -> day,entryDate -> month,entryDate -> year);
        Hash_DC_AllPatientsInThatPeriod(diseaseHash, entryDate, exitDate);
        free(entryDate);
        free(exitDate);
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////
bool Request_2(Hash_DC * diseaseHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";

    char * diseaseID;

    tok = strtok(NULL," ");
    diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
    strcpy(diseaseID,(const  char *)tok);


    Date * entryDate = NULL;
    Date * exitDate = NULL;
    entryDate = malloc(sizeof(*entryDate));
    exitDate = malloc(sizeof(*exitDate));

    // // entryDate
    tok = strtok(NULL, delimiters);
    entryDate -> day = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    entryDate -> month = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    entryDate -> year = (long)atoi(tok);

    // exitDate
    tok = strtok(NULL,delimiters);

    if(tok == NULL)
    {
        free(entryDate);
        free(exitDate);
        printf("You have to add exitDate! Please try again!\n");
        return true;
    }
    // exitDate
    exitDate -> day = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    exitDate -> month = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    exitDate -> year = (long)atoi(tok);
// diseaseFrequency H1N1 10-10-2010 20-20-2020 Greece

    tok = strtok(NULL,delimiters);
    // without country
    if(tok == NULL)
    {
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID),diseaseID);
        getPatientsInThatPeriod(bst -> root, entryDate, exitDate);
    }
    // user gave a country
    else
    {
        tResult = 0;
        // store country
        char * country;
        country = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(country,(const  char *)tok);

        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID),diseaseID);
        getPatientsInThatPeriod_SpecifiCountry(bst -> root, entryDate, exitDate, country);
        printf("Result = %ld\n", tResult);
        free(country);
    }
    free(entryDate);
    free(exitDate);
    return true;

}
///////////////////////////////////////////////////////////////////////////////////////////////
bool Request_3( Hash_DC * countryHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    printf("edw\n");
    // get k
    tok = strtok(NULL,delimiters);
    long k = atoi(tok);

    // get country
    tok = strtok(NULL,delimiters);
    char * country;
    country = ( char *)malloc(1 + sizeof(char) * strlen(tok));
    strcpy(country,(const  char *)tok);

    tok = strtok(NULL,delimiters);
    if(tok == NULL)
    {
        BST * bst = Hash_DC_Get_BSTroot(countryHash,Hash_Function_DJB2((unsigned char *)country), country);
        ListNode * head = NULL;
        inorderSearchNInsert(bst -> root,&head);
        size_t maxK = LenOfList(head);
        BinaryTreeNode ** nodes = (BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)* maxK);
        ListNode * current = head;
        for (size_t i = 0; i < maxK; i++)
        {
            nodes[i] = CreateBinaryTreeNode(current -> dc_name,current -> total_patientes);
            current = current -> next;
        }
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);

        PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        inorderMaxHeap(maxHeap -> root);
        if(k > maxK || k == 0)
        {
            printf("Error Input: Total Diseases are:%ld\nPlease Give a number between 1 - %ld\n",maxK,maxK);
            return false;
        }
        GetKMaxValues(maxHeap -> root, k);
        // topk-Diseases 3 Greece
        return true;
    }
    else
    {
        Date * entryDate = NULL;
        Date * exitDate = NULL;
        entryDate = malloc(sizeof(*entryDate));
        exitDate = malloc(sizeof(*exitDate));

        // entryDate
        entryDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> year = (long)atoi(tok);

        // exitDate
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(entryDate);
            free(exitDate);
            printf("You have to add exitDate! Please try again!\n");
            return true;
        }
        // exitDate
        exitDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> year = (long)atoi(tok);

        BST * bst = Hash_DC_Get_BSTroot(countryHash,Hash_Function_DJB2((unsigned char *)country), country);
        inorder(bst -> root);
        ListNode * head = NULL;
        inorderSearchNInsertDate(bst -> root,&head, entryDate, exitDate);
        size_t maxK = LenOfList(head);
        BinaryTreeNode ** nodes = (BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)* maxK);
        ListNode * current = head;
        for (size_t i = 0; i < maxK; i++)
        {
            nodes[i] = CreateBinaryTreeNode(current -> dc_name,current -> total_patientes);
            current = current -> next;
        }
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);

        PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        inorderMaxHeap(maxHeap -> root);
        if(k > maxK || k == 0)
        {
            printf("Error Input: Total Diseases are:%ld\nPlease Give a number between 1 - %ld\n",maxK,maxK);
            return false;
        }
        GetKMaxValues(maxHeap -> root, k);
    }


}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Request_4( Hash_DC * diseaseHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n:,/.-><[]{}|=+*@#$;";
    printf("edw\n");
    // get k
    tok = strtok(NULL,delimiters);
    long k = atoi(tok);

    // get disease
    tok = strtok(NULL, " ");
    char * diseaseID;
    diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
    strcpy(diseaseID,(const  char *)tok);

    tok = strtok(NULL,delimiters);
    if(tok == NULL)
    {
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID);
        inorder(bst -> root);
        ListNode * head = NULL;
        inorderSearchNInsertCountry(bst -> root,&head);
        size_t maxK = LenOfList(head);
        printf("maxK = %ld\n",maxK);
        BinaryTreeNode ** nodes = (BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)* maxK);
        ListNode * current = head;
        for (size_t i = 0; i < maxK; i++)
        {
            nodes[i] = CreateBinaryTreeNode(current -> dc_name,current -> total_patientes);
            current = current -> next;
        }
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);

        PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        inorderMaxHeap(maxHeap -> root);
        if(k > maxK || k == 0)
        {
            printf("Error Input: Total Diseases are:%ld\nPlease Give a number between 1 - %ld\n",maxK,maxK);
            return false;
        }
        GetKMaxValues(maxHeap -> root, k);
        // topk-Diseases 3 Greece
        return true;
    }
    else
    {
        Date * entryDate = NULL;
        Date * exitDate = NULL;
        entryDate = malloc(sizeof(*entryDate));
        exitDate = malloc(sizeof(*exitDate));

        // entryDate
        entryDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        entryDate -> year = (long)atoi(tok);

        // exitDate
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(entryDate);
            free(exitDate);
            printf("You have to add exitDate! Please try again!\n");
            return true;
        }
        // exitDate
        exitDate -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        exitDate -> year = (long)atoi(tok);

        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID);
        inorder(bst -> root);
        ListNode * head = NULL;
        inorderSearchNInsertCountryDate(bst -> root,&head, entryDate, exitDate);
        size_t maxK = LenOfList(head);
        BinaryTreeNode ** nodes = (BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)* maxK);
        ListNode * current = head;
        for (size_t i = 0; i < maxK; i++)
        {
            nodes[i] = CreateBinaryTreeNode(current -> dc_name,current -> total_patientes);
            current = current -> next;
        }
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);

        PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        inorderMaxHeap(maxHeap -> root);
        if(k > maxK || k == 0)
        {
            printf("Error Input: Total Diseases are:%ld\nPlease Give a number between 1 - %ld\n",maxK,maxK);
            return false;
        }
        GetKMaxValues(maxHeap -> root, k);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////////////
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
        printf("Arguments missing!!\n");
        Hash_DC_CurrentActivePatients(diseaseHash);
        return true;
    }
    else
    {
        // global variable
        tResult = 0;

        // Get root of current disease
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)tok), tok);

        // get Patients
        getCurrentPatients(bst -> root);
        printf("Current patients = %ld\n",tResult);

        return true;
    }
}


static long Read_Requests_Parse(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash, char * request)
{

    bool result;
    char * tok;
    char delimiters[] = " \n\t\r\v\f\n:,/.><[]{}|=+*@#$";
    tok = strtok(request,delimiters);

    if(tok != NULL)
    {
        if(strcmp(tok,"globalDiseaseStats") == 0)
        {
            if(Request_1(diseaseHash,tok))
            {
                printf("\nglobalDiseaseStats request has been done successfully!\n");
            }
            printf("6\n");
            return false;

        }
        else if(strcmp(tok,"diseaseFrequency") == 0)
        {
            printf("2\n");
            if(Request_2(diseaseHash,tok))
            {
                printf("\ndiseaseFrequency request has been done successfully!\n");
            }

        }
        else if(strcmp(tok,"topk-Diseases") == 0)
        {

            if(Request_3(countryHash,tok))
            {
                printf("\ntopk-Diseases request has been done successfully!\n");
            }
        }
        else if(strcmp(tok,"topk-Countries") == 0)
        {
            if(Request_4(diseaseHash,tok))
            {
                printf("\ntopk-Diseases request has been done successfully!\n");
            }

        }
        else if(!strcmp(tok,"insertPatientRecord"))
        {
            if(Request_5(patientHash, diseaseHash, countryHash, tok))
            {
                printf("\nPatient has been inserted successfully\n");
            }
            return false;

        }
        else if(strcmp(tok,"recordPatientExit") == 0)
        {
            if(Request_6(patientHash,tok))
            {
                printf("\nExitDate has been added successfully!\n");
            }
            return false;

        }
        else if(strcmp(tok,"numCurrentPatients") == 0)
        {
            Request_7(diseaseHash,tok);

            printf("--------------------------------------------\n");
            return false;
        }
        else if(strcmp(tok,"exit") == 0)
        {
            printf("Promt has been closed!!!\n");
            return true;

        }
        return false;

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////


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
///////////////////////////////////////////////////////////////////////////////////////////////
