
#include "../include/"

static long Read_Requests_Parse(Hash * hashSender,Hash * hashReceiver,WalletHash * wh,char * line,Date * dateArg,Time * timeArg,BST * root)
{

    long result = 0;
    char * tok;
    char delimiters[] = " \n\t\r\v\f\n-:,/.><[]{}|-=+*@#$";
    tok = strtok(line,delimiters);

    if(tok != NULL)
    {
        if(strcmp(tok,"requestTransaction") == 0)
        {
            result = Request_1(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            printf("%s\n",tok);

        }
        else if(strcmp(tok,"requestTransactions") == 0)
        {
            printf("2\n");
            tok = Request_2(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            tok = Request_2(hashSender,hashReceiver,wh,tok,dateArg,timeArg,root);
            printf("%s\n",tok);

        }
        else if(strcmp(tok,"requestTransactions2") == 0)
        {
            tok = strtok(NULL," ");
            //tok = strtok(NULL,delimiters);

            char * fileName = ( char *)malloc(1 + sizeof(char) * strlen(tok));
            strcpy(fileName,(const char *)tok);
            fileName[1 + sizeof(char) * strlen(tok)] = '\0';
            printf("%s\n",fileName);
            result = Request_3(fileName,hashSender,hashReceiver,wh,dateArg,timeArg,root);
            printf("3\n");
        }
        else if(strcmp(tok,"findEarnings") == 0)
        {
            printf("4\n");

        }
        else if(strcmp(tok,"findPayments") == 0)
        {
            result = Request_5(hashSender,tok);

        }
        else if(strcmp(tok,"walletStatus") == 0)
        {
            result = Request_6(wh,tok);
            if(result != -1)
            {
                printf("\nBalance = %ld\n\n",result);
                printf("Give another:\n");
            }
            result = 0;


        }
        else if(strcmp(tok,"bitCoinStatus") == 0)
        {
            result = Request_7(wh,tok);

            printf("7\n");

        }
        else if(strcmp(tok,"traceCoin") == 0)
        {
            printf("8\n");

        }
        else if(strcmp(tok,"exit") == 0)
        {
            printf("Promt has been closed!!!\n");
            result = -1;
            return result;
        }
        return result;

    }

}



void Read_Requests(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash)
{
    char * line = NULL;
    printf("---------> Promt <---------\n");
    while((read = getline(&line,&length, file)) != -1)
    {
        if(Read_Requests_Parse(patientHash,countryHash) < 0)
        {
            break;
        }
    }
}
