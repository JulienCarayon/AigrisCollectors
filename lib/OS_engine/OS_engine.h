#ifndef OS_ENGINE_H
#define OS_ENGINE_H

#include "../include/hardware.h"
#include "cmsis_os.h"
#include <stdbool.h>

#define RX_COMMAND_BUFFER_SIZE 256

extern bool is_comptetion_started;
extern bool rx_command_received;
extern char rx_command_buffer[RX_COMMAND_BUFFER_SIZE];

osMutexId_t uartMutex_M;
extern const osMutexAttr_t uartMutex_attributes;

char *getsMutex(char *text);
bool putsMutex(char *text);
bool send_command(char *command, char *response_buffer);
void wait_start(void);
void os_release_mutex();
#endif
