#include "OS_engine.h"
#include "../include/hardware.h"
#include "OS_types.h"
#include <constants.h>
#include <stdio.h>
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

    strncpy(response_buffer, rx_command_buffer, sizeof(rx_command_buffer) - 1);
    response_buffer[sizeof(rx_command_buffer) - 1] = '\0';

    memset(rx_command_buffer, 0, sizeof(rx_command_buffer));
    os_release_mutex(uartMutex_M);
  }
  osDelay(OS_DELAY); // TODO Why ?
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

uint32_t getFreeStackSpace(os_thread_id thread_id)
{

  // TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();
  // uint32_t freeStackSpace = uxTaskGetStackHighWaterMark(thread_id);
  // return freeStackSpace * sizeof(StackType_t); // Convertir les mots de pile en octets
  return osThreadGetStackSpace(thread_id);
}

uint32_t getStackSize(os_thread_id thread_id)
{
  const char *thread_name = osThreadGetName(thread_id); // Get the thread name pointer
  uint32_t task_size = TASKS_SIZES;
  if (strstr(thread_name, "exploratorsTask") != NULL)
  {
    task_size = TASKS_SIZES_EXPLORER;
  }
  return task_size;
}

uint32_t getUsedStackSpace(os_thread_id thread_id)
{
  // uint32_t used_stack_size =
  //     (getStackSize(thread_id) - getFreeStackSpace(thread_id));

  // char buff_size[40] = {0};
  // sprintf(buff_size, "Used stack space : %ld\n", used_stack_size);
  // putsMutex(buff_size);

  return (getStackSize(thread_id) - getFreeStackSpace(thread_id));
}

void printTaskInformation(os_thread_id thread_id)
{

  const char *thread_name = osThreadGetName(thread_id); // Get the thread name pointer

  char buff_information[50] = {0};
  sprintf(buff_information,
          // "%s : free stack space : %ld/%ld \n"
          "%s : used stack space : %ld/%ld \n",
          // thread_name, getFreeStackSpace(thread_id), getStackSize(thread_id),
          thread_name, getUsedStackSpace(thread_id), getStackSize(thread_id));
  putsMutex(buff_information);
  osDelay(10);
}

void getTotalRAMUsage(void)
{
  char buff_information[200] = {0};
  sprintf(buff_information, "TOTAL RAM USAGE : %d \n",
          (configTOTAL_HEAP_SIZE - xPortGetFreeHeapSize()));
  putsMutex(buff_information);
}
