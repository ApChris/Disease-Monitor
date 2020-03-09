/*
	File Name 	: date .c
	Author 		: Christoforos Apostolopoulos
	Project 	: Number -> 1 , System Programming 2019-2020
*/

#include "../include/date.h"


long Compare_Date_Time(Date * date,Date * dateArg)
{
    if(dateArg -> year > date -> year) // if last transaction year is > than new transaction year then ERROR
    {
        printf("\n1Wrong date/time input!!!\n");
        return -1;
    }
    else if(dateArg -> year < date -> year)
    {
        printf("\nThe date & time from stdin is fine!\n");
        return 0;
    }
    else // dateArg -> year is == YEAR
    {
        if(dateArg -> month > date -> month)
        {
            printf("\n2Wrong date/time input!!!\n");
            return -1;
        }
        else if(dateArg -> month < date -> month)
        {
            printf("\nThe date & time from stdin is fine!\n");
            return 0;
        }
        else // year & month is the same
        {
            if(dateArg -> day > date -> day)
            {
                printf("\n3Wrong date/time input!!!\n");
                return -1;
            }
            else if(dateArg -> day < date -> day)
            {
                printf("\nThe date & time from stdin is fine!\n");
                return 0;
            }
            else // year/month/day is the same
            {
                printf("\nThe date & time is exactly the same!!\nTherefore I will add 1 minute to new transaction time and ill continue!\n");
            }
        }
    }
}
