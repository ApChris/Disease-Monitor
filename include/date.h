#ifndef _DATE_H_
#define _DATE_H_

#include <stdio.h>

typedef struct date
{
    long day;
    long month;
    long year;
}Date;


long Compare_Date(Date * date,Date * dateArg);


#endif
