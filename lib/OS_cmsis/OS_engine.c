#include "OS_engine.h"
#include "../include/hardware.h"
#include "OS_types.h"
#include <constants.h>
#include <stdio.h>
#include <string.h>

bool is_comptetion_started = false;
bool rx_command_received = false;
char rx_command_buffer[RX_COMMAND_BUFFER_SIZE] = {0};

static os_mutex_id uart_mutex_id;
static os_mutex_id game_data_mutex_id;

void os_engine_init(void) {
  const os_mutex_attr uart_mutex_attributes = {
      .name = "uartMutex", osMutexPrioInherit, NULL, 0U};

  uart_mutex_id = os_create_mutex(uart_mutex_attributes);

  const os_mutex_attr game_data_mutex_attributes = {
      .name = "dataMutex", osMutexPrioInherit, NULL, 0U};

  game_data_mutex_id = os_create_mutex(game_data_mutex_attributes);
}

os_timer_id os_timer_new(uint8_t ship_id, void *os_firing_timer_callback,
                         uint8_t attacker_id, void *game_data) {
  os_timer_id timer_id = osTimerNew(os_firing_timer_callback, osTimerOnce,
                                    &attacker_id, game_data);

  if (!timer_id) {
    while (1) {
      os_puts_mutex("ERROR os_timer_new\n");
    }
  }
  return timer_id;
}

void os_timer_start(os_timer_id timer_id, uint32_t timer_delay) {
  if (osTimerStart(timer_id, timer_delay) != osOK) {
    while (1) {
      os_puts_mutex("Timer could not be started\n");
    }
  }
}

void wait_start(void) {
  while (!is_comptetion_started) {
    osDelay(OS_DELAY);
  }
}

os_mutex_id os_create_mutex(const os_mutex_attr mutex_attribute) {
  os_mutex_id uart_mutex = osMutexNew(&mutex_attribute);

  if (uart_mutex == NULL)
    while (1)
      ;

  return uart_mutex;
}

void os_acquire_mutex(os_mutex_id mutex_id, uint32_t timeout) {
  osStatus_t aquire_status = osMutexAcquire(mutex_id, timeout);
  // puts("AQUIRED MUTEX\n");

  if (aquire_status != osOK)
    while (1) {
      puts("ERRORS ACQUIRE\n");
    }
}

void os_release_mutex(os_mutex_id mutex_id) {
  if (osMutexGetOwner(mutex_id) != NULL) {
    osStatus_t release_status = osMutexRelease(mutex_id);

    if (release_status != osOK)
      while (1) {
        puts("ERRORS RELEASE\n");
      }
  }
}

void os_delay(uint32_t os_delay) { osDelay(OS_DELAY); }

void aquire_game_data_mutex(void) {
  os_acquire_mutex(game_data_mutex_id, osWaitForever);
}

void release_game_data_mutex(void) { os_release_mutex(game_data_mutex_id); }

void send_command(char *command) {
  os_acquire_mutex(uart_mutex_id, osWaitForever);
  puts(command);

  gets(rx_command_buffer);

  if (strstr(rx_command_buffer, "OK") != NULL) {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  } else if (strstr(rx_command_buffer, "KO") != NULL) {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  } else {
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  }

  osDelay(OS_DELAY);
}

void send_command_radar(char *command, char *response_buffer) {
  os_acquire_mutex(uart_mutex_id, osWaitForever);
  puts(command);

  gets(rx_command_buffer);

  rx_command_received = false;
  strncpy(response_buffer, rx_command_buffer, sizeof(rx_command_buffer) - 1);
  response_buffer[sizeof(rx_command_buffer) - 1] = '\0';
  memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
  os_release_mutex(uart_mutex_id);

  osDelay(OS_DELAY);
}

void os_puts_mutex(char *text) {
  os_acquire_mutex(uart_mutex_id, osWaitForever);
  puts(text);
  os_release_mutex(uart_mutex_id);
}

char *getsMutex(char *text) {
  char *original_str = text;
  os_acquire_mutex(uart_mutex_id, osWaitForever);
  gets(text);
  os_release_mutex(uart_mutex_id);
  return original_str;
}

uint32_t getFreeStackSpace(os_thread_id thread_id) {
  uint32_t stack_space = osThreadGetStackSpace(thread_id);
  char space[40] = {0};
  sprintf(space, "Free stack space : %ld\n", stack_space);
  os_puts_mutex(space);

  return stack_space;
}

uint32_t getStackSize(os_thread_id thread_id) {
  uint32_t stack_size = osThreadGetStackSize(thread_id);
  char buff_size[40] = {0};
  sprintf(buff_size, "Stack size : %ld\n", stack_size);
  os_puts_mutex(buff_size);

  return stack_size;
}

void getUsedStackSpace(os_thread_id thread_id) {
  uint32_t used_stack_size =
      getStackSize(thread_id) - getFreeStackSpace(thread_id);

  char buff_size[40] = {0};
  sprintf(buff_size, "Used stack space : %ld\n", used_stack_size);
  os_puts_mutex(buff_size);
}

void os_firing_timer_start(os_timer_id timer_id, uint32_t ticks) {
  if (osTimerStart(timer_id, ticks) != osOK) {
    while (1) {
      os_puts_mutex("ERROR os_firing_timer_start");
    }
  }
}