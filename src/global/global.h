#ifndef GLOBAL_H
#define GLOBAL_H

#include "cmsis_os.h"
#include "../include/hardware.h"
osMutexId_t putsMutex_M;

extern const osMutexAttr_t putsMutex_attributes;

void putsMutex(char *text);
char* osStatusToString(osStatus_t status);
char* longlong_to_string(long long num);

#endif