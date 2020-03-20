#ifndef _REQUESTS_H_
#define _REQUESTS_H_
#include <stdio.h>

#include "hashDC.h"
bool Request_5(Hash * patientHash, Hash_DC * diseaseHash, Hash_DC * countryHash, char * tok);
bool Request_6(Hash * patientHash, char * tok);
bool Request_7(Hash_DC * diseaseHash, char * tok);
void Read_Requests(Hash_DC * diseaseHash, Hash_DC * countryHash, Hash * patientHash);

#endif
