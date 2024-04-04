#include "OS_engine.h"
#include "../include/hardware.h"
#include "OS_types.h"
#include <constants.h>
#include <stdio.h>
#include <string.h>

bool is_comptetion_started = false;
bool rx_command_received = false;
char rx_command_buffer[RX_COMMAND_BUFFER_SIZE] = {""};

static os_mutex_id uart_mutex_id;
static os_mutex_id data_mutex_id;

void os_engine_init(void) {
  const os_mutex_attr uart_mutex_attributes = {
      .name = "uartMutex", osMutexPrioInherit, NULL, 0U};

  uart_mutex_id = os_create_mutex(uart_mutex_attributes);

  const os_mutex_attr data_mutex_attributes = {
      .name = "dataMutex", osMutexPrioInherit, NULL, 0U};

  data_mutex_id = os_create_mutex(data_mutex_attributes);
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

  if (aquire_status != osOK)
    while (1) {
      puts("ERRORS ACQUIRE\n");
    }
}

void os_release_mutex(os_mutex_id mutex_id) {
  osStatus_t release_status = osMutexRelease(uart_mutex_id);

  if (release_status != osOK)
    while (1) {
      puts("ERRORS RELEASE\n");
    }
}

void send_command(char *command, char *response_buffer) {
  os_acquire_mutex(uart_mutex_id, osWaitForever);
  puts(command);

  while (rx_command_received == false) {
    osDelay(OS_DELAY); // Let some time
  }

  if (strstr(rx_command_buffer, "OK") != NULL) {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  } else if (strstr(rx_command_buffer, "KO") != NULL) {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  } else {
    rx_command_received = false;

    strncpy(response_buffer, rx_command_buffer, sizeof(rx_command_buffer) - 1);
    response_buffer[sizeof(rx_command_buffer) - 1] = '\0';

    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uart_mutex_id);
  }
  osDelay(OS_DELAY); // TODO Why ?
}

void putsMutex(os_mutex_id mutex_id, char *text) {
  os_acquire_mutex(mutex_id, osWaitForever);
  puts(text);
  os_release_mutex(mutex_id);
}

char *getsMutex(os_mutex_id mutex_id, char *text) {
  char *original_str = text;
  os_acquire_mutex(mutex_id, osWaitForever);
  gets(text);
  os_release_mutex(mutex_id);
  return original_str;
}

uint32_t getFreeStackSpace(os_thread_id thread_id) {
  uint32_t stack_space = osThreadGetStackSpace(thread_id);
  char space[40] = {0};
  sprintf(space, "Free stack space : %ld\n", stack_space);
  putsMutex(uart_mutex_id, space);

  return stack_space;
}

uint32_t getStackSize(os_thread_id thread_id) {
  uint32_t stack_size = osThreadGetStackSize(thread_id);
  char buff_size[40] = {0};
  sprintf(buff_size, "Stack size : %ld\n", stack_size);
  putsMutex(uart_mutex_id, buff_size);

  return stack_size;
}

void getUsedStackSpace(os_thread_id thread_id) {
  uint32_t used_stack_size =
      getStackSize(thread_id) - getFreeStackSpace(thread_id);

  char buff_size[40] = {0};
  sprintf(buff_size, "Used stack space : %ld\n", used_stack_size);
  putsMutex(uart_mutex_id, buff_size);
}
