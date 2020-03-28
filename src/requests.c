
#include "../include/requests.h"

bool Request_1( Hash_DC * diseaseHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    tok = strtok(NULL,delimiters);
    if(tok == NULL)
    {
        Hash_DC_AllPatients(diseaseHash);
        return true;
    }
    else
    {
        Date * date1 = NULL;
        Date * date2 = NULL;
        date1 = malloc(sizeof(*date1));
        date2 = malloc(sizeof(*date2));

        // date1
        date1 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> year = (long)atoi(tok);

        // date2
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(date1);
            free(date2);
            printf("error\n");
            return true;
        }

        date2 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> year = (long)atoi(tok);
        Hash_DC_AllPatientsInThatPeriod(diseaseHash, date1, date2);
        free(date1);
        free(date2);
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
    if(tok == NULL)
    {
        printf("error\n");
        return true;
    }
    diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
    strcpy(diseaseID,(const  char *)tok);


    Date * date1 = NULL;
    Date * date2 = NULL;
    date1 = malloc(sizeof(*date1));
    date2 = malloc(sizeof(*date2));

    // // date1
    tok = strtok(NULL, delimiters);

    date1 -> day = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    date1 -> month = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    date1 -> year = (long)atoi(tok);

    // date2
    tok = strtok(NULL,delimiters);

    if(tok == NULL)
    {
        free(date1);
        free(date2);
        printf("error\n");
        return true;
    }
    // date2
    date2 -> day = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    date2 -> month = (long)atoi(tok);

    tok = strtok(NULL,delimiters);
    date2 -> year = (long)atoi(tok);
// diseaseFrequency H1N1 10-10-2010 20-20-2020 Greece

    tok = strtok(NULL,delimiters);
    // without country
    if(tok == NULL)
    {
        tResult = 0;
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID),diseaseID);
        getPatientsInThatPeriod(bst -> root, date1, date2);
        printf("%s %ld\n",diseaseID,tResult);
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
        getPatientsInThatPeriod_SpecifiCountry(bst -> root, date1, date2, country);
        printf("%s %ld\n",diseaseID, tResult);
        free(country);
    }
    free(date1);
    free(date2);
    return true;

}
///////////////////////////////////////////////////////////////////////////////////////////////
bool Request_3( Hash_DC * countryHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$;";
    // get k
    tok = strtok(NULL,delimiters);
    size_t k = atoi(tok);

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
        DeleteList(&head);
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);
        for (size_t i = 0; i < maxK; i++)
        {
            free(nodes[i] -> dc_name);
            free(nodes[i]);
        }
        free(head);
        free(nodes);
        // PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        // inorderMaxHeap(maxHeap -> root);
        if(k == 0)
        {
            printf("error\n");
            return false;
        }
        if(k > maxK)
        {
            k = maxK;
        }
        GetKMaxValues(maxHeap -> root, k);
        DeallocateMaxHeap(maxHeap -> root);
        free(maxHeap);

        // topk-Diseases 3 Greece
        return true;
    }
    else
    {
        Date * date1 = NULL;
        Date * date2 = NULL;
        date1 = malloc(sizeof(*date1));
        date2 = malloc(sizeof(*date2));

        // date1
        date1 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> year = (long)atoi(tok);

        // date2
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(date1);
            free(date2);
            printf("You have to add date2! Please try again!\n");
            return true;
        }
        // date2
        date2 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> year = (long)atoi(tok);

        BST * bst = Hash_DC_Get_BSTroot(countryHash,Hash_Function_DJB2((unsigned char *)country), country);
        ListNode * head = NULL;
        inorderSearchNInsertDate(bst -> root,&head, date1, date2);
        size_t maxK = LenOfList(head);
        BinaryTreeNode ** nodes = (BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)* maxK);
        ListNode * current = head;
        for (size_t i = 0; i < maxK; i++)
        {
            nodes[i] = CreateBinaryTreeNode(current -> dc_name,current -> total_patientes);
            current = current -> next;
        }
        DeleteList(&head);
        BinaryMaxHeap * maxHeap = CreateBinaryMaxHeap();
        maxHeap -> root = BuildMaxHeap(nodes,maxHeap -> root, 0 ,maxK);
        for (size_t i = 0; i < maxK; i++)
        {
            free(nodes[i]);
        }
        free(head);
        free(nodes);
        // PrintList(&head);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        // inorderMaxHeap(maxHeap -> root);
        if(k == 0)
        {
            printf("error\n");
            return false;
        }
        if(k > maxK)
        {
            k = maxK;
        }
        GetKMaxValues(maxHeap -> root, k);
        DeallocateMaxHeap(maxHeap -> root);
        free(maxHeap);
        return true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Request_4( Hash_DC * diseaseHash, char * tok)
{
    char delimiters[] = " \n\t\r\v\f\n:,/.-><[]{}|=+*@#$;";
    // get k
    tok = strtok(NULL,delimiters);
    size_t k = atoi(tok);

    // get disease
    tok = strtok(NULL, " \n");
    char * diseaseID;
    diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
    strcpy(diseaseID,(const  char *)tok);

    tok = strtok(NULL,delimiters);
    if(tok == NULL)
    {
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID);
        // inorder(bst -> root);
        ListNode * head = NULL;
        inorderSearchNInsertCountry(bst -> root,&head);
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
        for (size_t i = 0; i < maxK; i++)
        {
            free(nodes[i] -> dc_name);
            free(nodes[i]);
        }
        free(head);
        free(nodes);

        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        // inorderMaxHeap(maxHeap -> root);
        if(k == 0)
        {
            printf("error\n");
            return false;
        }
        if(k > maxK)
        {
            k = maxK;
        }
        GetKMaxValues(maxHeap -> root, k);
        DeallocateMaxHeap(maxHeap -> root);
        free(maxHeap);

        return true;
    }
    else
    {
        Date * date1 = NULL;
        Date * date2 = NULL;
        date1 = malloc(sizeof(*date1));
        date2 = malloc(sizeof(*date2));

        // date1
        date1 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date1 -> year = (long)atoi(tok);

        // date2
        tok = strtok(NULL,delimiters);

        if(tok == NULL)
        {
            free(date1);
            free(date2);
            printf("error\n");
            return true;
        }
        // date2
        date2 -> day = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> month = (long)atoi(tok);

        tok = strtok(NULL,delimiters);
        date2 -> year = (long)atoi(tok);

        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)diseaseID), diseaseID);
        // inorder(bst -> root);
        ListNode * head = NULL;
        inorderSearchNInsertCountryDate(bst -> root,&head, date1, date2);
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

        for (size_t i = 0; i < maxK; i++)
        {
            free(nodes[i] -> dc_name);
            free(nodes[i]);
        }
        free(head);
        free(nodes);


        setParent(maxHeap -> root,maxHeap -> root);
        preorderMaxHeapify(maxHeap -> root);
        // inorderMaxHeap(maxHeap -> root);
        if(k == 0)
        {
            printf("error\n");
            return false;
        }
        if(k > maxK)
        {
            k = maxK;
        }
        GetKMaxValues(maxHeap -> root, k);
        DeallocateMaxHeap(maxHeap -> root);
        free(maxHeap);


        return true;
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
        free(entryDate);
        free(exitDate);
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
    free(entryDate);
    free(exitDate);
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
        printf("Not found\n");
        return false;
    }
    else
    {
        tok = strtok(NULL,delimiters);
        info -> exitDate -> day = (long)atoi(tok);
        tok = strtok(NULL,delimiters);
        info -> exitDate -> month = (long)atoi(tok);
        tok = strtok(NULL,delimiters);
        info -> exitDate -> year = (long)atoi(tok);
        // PatientInfo_Print(info);
        return true;
    }
}

bool Request_7(Hash_DC * diseaseHash, char * tok)
{
    tok = strtok(NULL," \n");
    if(tok == NULL)
    {
        tResult = 0;
        Hash_DC_CurrentActivePatients(diseaseHash);
        return true;
    }
    else
    {
        // global variable
        tResult = 0;

        // Get root of current disease
        BST * bst = Hash_DC_Get_BSTroot(diseaseHash,Hash_Function_DJB2((unsigned char *)tok), tok);

        // if bst != NULL means that disease exists in hash
        if(bst != NULL)
        {
            getCurrentPatients(bst -> root);
        }
        printf("%s %ld\n",tok, tResult);
        return true;
    }
}


static long Read_Requests_Parse(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash, char * request)
{

    char * tok;
    char delimiters[] = " \n\t\r\v\f\n:,.><[]{}|=+*@#$";
    tok = strtok(request,delimiters);

    if(tok != NULL)
    {
        if(strcmp(tok,"/globalDiseaseStats") == 0)
        {
            Request_1(diseaseHash,tok);

            return false;

        }
        else if(strcmp(tok,"/diseaseFrequency") == 0)
        {
            Request_2(diseaseHash,tok);

            return false;

        }
        else if(strcmp(tok,"/topk-Diseases") == 0)
        {

            Request_3(countryHash,tok);

        }
        else if(strcmp(tok,"/topk-Countries") == 0)
        {
            Request_4(diseaseHash,tok);

            return false;

        }
        else if(strcmp(tok,"/insertPatientRecord") == 0)
        {
            if(Request_5(patientHash, diseaseHash, countryHash, tok))
            {
                printf("\nRecord added\n");
            }
            return false;

        }
        else if(strcmp(tok,"/recordPatientExit") == 0)
        {
            if(Request_6(patientHash,tok))
            {
                printf("\nRecord updated\n");
            }
            return false;

        }
        else if(strcmp(tok,"/numCurrentPatients") == 0)
        {
            Request_7(diseaseHash,tok);

            return false;
        }
        else if(strcmp(tok,"/exit") == 0)
        {
            printf("exiting\n");
            return true;

        }
        return false;

    }
    return true;

}
///////////////////////////////////////////////////////////////////////////////////////////////


void Read_Requests(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash)
{
    char * request = NULL;
    size_t length;
    long read;
    while((read = getline(&request,&length, stdin)) != -1)
    {
        if(Read_Requests_Parse(diseaseHash, countryHash, patientHash, request))
        {
            free(request);
            break;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
