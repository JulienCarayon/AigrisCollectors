#include "OS_types.h"
#include <stdio.h>

void send_command(char *command) { printf("%s", command); }

void send_command_radar(char *command, char *response_buffer) {
  printf("%s", command);
}

void os_delay(uint32_t os_delay) {}

void aquire_game_data_mutex(void) {}

void release_game_data_mutex(void) {}

void os_puts_mutex(void) {}

void os_firing_timer_start(os_timer_id timer_id, uint32_t ticks) {}
