#ifndef __INPUT_H_
#define __INPUT_H_

#include "hash.h"

long ReadFile(const char * patientRecordsFile, Hash * patientHash);
void Print_Input(char * patientRecordsFile, long diseaseHashtableNumOfEntries, long countryHashtableNumOfEntries, long bucketSize);

#endif
