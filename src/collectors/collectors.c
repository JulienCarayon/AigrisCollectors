#include "collectors.h"

const osThreadAttr_t collectorsTask_attributes = {
    .name = "collectorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = TASKS_SIZES,
};

void StartCollectorTask_1(void *argument) {
  while (1) {
    if (is_comptetion_started == true) {
      test_ship(8);
    }
    osDelay(OS_DELAY);
  }
}

void StartCollectorTask_2(void *argument) {
  while (1) {
    if (is_comptetion_started == true) {
      test_ship(9);
    }
    osDelay(OS_DELAY);
  }
}