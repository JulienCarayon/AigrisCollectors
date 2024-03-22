#ifndef OS_ENGINE_H
#define OS_ENGINE_H

#include <os_types.h>
#include <stdbool.h>

#define RX_COMMAND_BUFFER_SIZE 256

extern bool is_comptetion_started;
extern bool rx_command_received;
extern char rx_command_buffer[RX_COMMAND_BUFFER_SIZE];

char *getsMutex(char *text);
bool putsMutex(char *text);
bool send_command(char *command, char *response_buffer);
void wait_start(void);

void os_engine_init(void);
void os_create_mutex();
void os_acquire_mutex();
void os_release_mutex(os_mutex_id mutex_id);

#endif
