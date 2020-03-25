#ifndef __INPUT_H_
#define __INPUT_H_

#include "hash.h"
#include "hashDC.h"
void ReadFile(const char * patientRecordsFile, Hash * patientHash, Hash_DC * diseaseHash, Hash_DC * countryHash);
void Print_Input(char * patientRecordsFile, long diseaseHashtableNumOfEntries, long countryHashtableNumOfEntries, long bucketSize);

#endif
