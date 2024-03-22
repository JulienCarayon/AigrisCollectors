#include "explorators.h"

const osThreadAttr_t exploratorsTask_attributes = {
    .name = "exploratorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = TASKS_SIZES,
};

void StartExploratorTask_1(void *argument) {
  // putsMutex("Explorer Task 1 started\n");
  while (1) {
    if (is_comptetion_started == true) {
      test_ship(6);
    }
    osDelay(OS_DELAY);
  }
}

void StartExploratorTask_2(void *argument) {
  // putsMutex("Explorer Task 2 started\n");
  while (1) {
    if (is_comptetion_started == true) {
      test_ship(7);
    }
    osDelay(OS_DELAY);
  }
}