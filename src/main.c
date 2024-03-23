#include <math.h>
#include <stdbool.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "cmsis_os.h"
#include "hardware.h"

#include <OS_engine.h>

#include "attackers/attackers.h"
#include "collectors/collectors.h"
#include "explorators/explorators.h"

osThreadId_t mainTaskHandle;
void StartMainTask(void *argument);

int main(void) {
  hardware_init();
  osKernelInitialize();

  os_engine_init();

  const osThreadAttr_t mainTask_attributes = {
      .name = "mainTask",
      .priority = (osPriority_t)osPriorityNormal1,
      .stack_size = 2048,
  };
  mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

  attackerTaskHandles_1 =
      osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
  attackerTaskHandles_2 =
      osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
  attackerTaskHandles_3 =
      osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
  attackerTaskHandles_4 =
      osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
  attackerTaskHandles_5 =
      osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

  exploratorTaskHandles_1 =
      osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
  exploratorTaskHandles_2 =
      osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);

  collectorTaskHandles_1 =
      osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
  collectorTaskHandles_2 =
      osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);

  osKernelStart();
}

void StartMainTask(void *argument) {
  while (1) {
    osDelay(1);
  }
}