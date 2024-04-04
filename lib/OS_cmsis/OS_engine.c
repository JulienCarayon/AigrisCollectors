#include "OS_engine.h"
#include "../include/hardware.h"
#include "OS_types.h"
#include <constants.h>
#include <string.h>

bool is_comptetion_started = false;
bool rx_command_received = false;
char rx_command_buffer[RX_COMMAND_BUFFER_SIZE] = {""};

static os_mutex_id uartMutex_M;

void os_engine_init(void)
{
  const os_mutex_attr uartMutex_attributes = {
      .name = "uartMutex", osMutexPrioInherit, NULL, 0U};

  uartMutex_M = os_create_mutex(uartMutex_attributes);
}

void wait_start(void)
{
  while (!is_comptetion_started)
  {
    osDelay(OS_DELAY);
  }
}

os_mutex_id os_create_mutex(const os_mutex_attr mutex_attribute)
{
  os_mutex_id uart_mutex = osMutexNew(&mutex_attribute);

  if (uart_mutex == NULL)
    while (1)
      ;

  return uart_mutex;
}

void os_acquire_mutex(os_mutex_id mutex_id, uint32_t timeout)
{
  osStatus_t aquire_status = osMutexAcquire(mutex_id, timeout);

  if (aquire_status != osOK)
    while (1)
    {
      puts("ERRORS ACQUIRE\n");
    }
}

void os_release_mutex(os_mutex_id mutex_id)
{
  osStatus_t release_status = osMutexRelease(uartMutex_M);

  if (release_status != osOK)
    while (1)
    {
      puts("ERRORS RELEASE\n");
    }
}

void send_command(char *command, char *response_buffer)
{
  os_acquire_mutex(uartMutex_M, osWaitForever);
  puts(command);

  while (rx_command_received == false)
  {
    osDelay(OS_DELAY); // Let some time
  }

  if (strstr(rx_command_buffer, "OK") != NULL)
  {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uartMutex_M);
  }
  else if (strstr(rx_command_buffer, "KO") != NULL)
  {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uartMutex_M);
  }
  else
  {
    rx_command_received = false;
    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uartMutex_M);
  }
  osDelay(OS_DELAY); // TODO Why ?
}

osMemoryPoolId_t init_memory_pool(void)
{
  osMemoryPoolId_t new_memory_pool_id =
      osMemoryPoolNew(MEMORY_POOL_OBJECTS, sizeof(os_T_Memory_block), NULL);
  putsMutex("init_memory_pool : new_memory_pool_id : ");
  putsMutex(new_memory_pool_id);

  if (new_memory_pool_id == NULL)
  {
    while (1)
      puts("new_memory_pool_id == NULL");
  }
  return new_memory_pool_id;
}

void putsMutex(char *text)
{
  os_acquire_mutex(uartMutex_M, osWaitForever);
  puts(text);
  os_release_mutex(uartMutex_M);
}

char *getsMutex(char *text)
{
  char *original_str = text;
  os_acquire_mutex(uartMutex_M, osWaitForever);
  gets(text);
  os_release_mutex(uartMutex_M);
  return original_str;
}