

long ReadFile_(const char * patientRecordsFile, Hash * patientHash)
{

    char line[255];
    PatientInfo * info;
    char * recordID
    char * patientFirstName;
    char * patientLastName;
    char * diseaseID;
    char * country;
    long value;

    long day,month,year;

    Date * date;
    Time * time;
    date = malloc(sizeof(*date));
    time = malloc(sizeof(*time));

    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$";
    char * tok;

    FILE * file;
    file = fopen(fileName, "r");
    printf("%s has been opened successfully!!\n\n", fileName); // Feedback


    long result;
    tID = 0;
    while(fgets(line,sizeof(line), file))
    {

        // Read next token
        tok = strtok(line, delimiters);

        // Get transactionID
        recordID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(recordID,(const char *)tok);
        recordID[1 + sizeof(char) * strlen(tok)] = '\0';

        // Read next token
        tok = strtok(NULL,delimiters);

        // Get senderWalletID
        patientFirstName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(patientFirstName,(const  char *)tok);
        patientFirstName[1 + sizeof(char) * strlen(tok)] = '\0';

        // Read next token
        tok = strtok(NULL,delimiters);

        // Get receivWalletID
        patientLastName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(patientLastName,(const  char *)tok);
        patientLastName[1 + sizeof(char) * strlen(tok)] = '\0';

        // Read next token
        tok = strtok(NULL,delimiters);

        // Get receivWalletID
        diseaseID = ( char *)malloc(1 + sizeof(char) * strlen(tok));
        strcpy(diseaseID,(const  char *)tok);
        diseaseID[1 + sizeof(char) * strlen(tok)] = '\0';


        // Read next token
        tok = strtok(NULL,delimiters);


        value = (long)atoi(tok);                     // Get value
        tok = strtok(NULL,delimiters);

        day = (long)atoi(tok);                       // Get day
        tok = strtok(NULL,delimiters);

        month = (long)atoi(tok);                     // Get month
        tok = strtok(NULL,delimiters);

        year = (long)atoi(tok);                      // Get year
        tok = strtok(NULL,delimiters);

        hours = (long)atoi(tok);                     // Get hours
        tok = strtok(NULL,delimiters);

        minutes = (long)atoi(tok);                  // Get minutes
        tok = strtok(NULL,delimiters);

        // Date & Time
        date -> day = day;
        date -> month = month;
        date -> year = year;

        time -> hours = hours;
        time -> minutes = minutes;


    fclose(file);
    printf("\n\n%s has been closed successfully!!\n", fileName); // Feedback
}
