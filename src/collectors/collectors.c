#include "collectors.h"
#include <OS_engine.h>

const osThreadAttr_t collectorsTask_attributes = {
    .name = "collectorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = TASKS_SIZES,
};

void StartCollectorTask_1(void *argument) {
  wait_start();
  collector_manager(8);
}

void StartCollectorTask_2(void *argument) {
  wait_start();
  collector_manager(9);
}