#include "OS_engine.h"
#include <constants.h>
#include <string.h>

bool is_comptetion_started = false;
bool rx_command_received = false;
char rx_command_buffer[RX_COMMAND_BUFFER_SIZE] = {""};

const osMutexAttr_t uartMutex_attributes = {
    .name = "uartMutex", osMutexPrioInherit, NULL, 0U};

bool putsMutex(char *text) {
  if (uartMutex_M != NULL) {
    osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
    if (aquire_status != osOK)
      return false;
    puts(text);
    osStatus_t release_status = osMutexRelease(uartMutex_M);
    if (release_status != osOK) {
      return false;
    }
    return true;
  } else {
    return false;
  }
}

char *getsMutex(char *text) {
  char *original_str = text;
  if (uartMutex_M != NULL) {
    osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
    if (aquire_status != osOK)
      return NULL;

    gets(text);

    osStatus_t release_status = osMutexRelease(uartMutex_M);
    if (release_status != osOK) {
      return NULL;
    }
  }
  return original_str;
}

void wait_start(void) {
  while (!is_comptetion_started) {
    osDelay(OS_DELAY);
  }
}

// TO DO :
/*
 */
bool send_command(char *command, char *response_buffer) {
  if (uartMutex_M != NULL) // TODO Acquire mutex function (while)
  {
    putsMutex(command);
    osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
    if (aquire_status != osOK)
      return false;

    while (rx_command_received == false) {
      osDelay(1); // Let some time
    }

    osStatus_t release_status = false;
    if (strstr(rx_command_buffer, "OK") != NULL) {
      rx_command_received = false;
      memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
      release_status = osMutexRelease(uartMutex_M);
      return true;
    } else if (strstr(rx_command_buffer, "KO") != NULL) {
      rx_command_received = false;
      memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
      release_status = osMutexRelease(uartMutex_M);
      return false;
    } else {
      rx_command_received = false;
      memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
      return false;
    }
    release_status = osMutexRelease(uartMutex_M);

    if (release_status != osOK) {
      return false;
    }
  } else {
    return false;
  }
}

void os_release_mutex() {}