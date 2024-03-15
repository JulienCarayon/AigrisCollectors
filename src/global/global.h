#ifndef GLOBAL_H
#define GLOBAL_H

#include "cmsis_os.h"
#include "../include/hardware.h"
#include <stdbool.h>

osMutexId_t uartMutex_M;

extern const osMutexAttr_t uartMutex_attributes;
bool send_command(const char *command, char *response_buffer);
char *getsMutex(char *text);
void putsMutex(char *text);
char* osStatusToString(osStatus_t status);
char* longlong_to_string(long long num);
bool uart_data_available();

#endif