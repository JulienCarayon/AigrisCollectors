#include "attackers.h"

const osThreadAttr_t attackersTask_attributes = {
    .name = "attackersTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = TASKS_SIZES,
};

void StartAttackerTask_1(void *argument) {
  wait_start();
  test_ship(1);
}

void StartAttackerTask_2(void *argument) {
  wait_start();
  test_ship(2);
}

void StartAttackerTask_3(void *argument) {
  wait_start();
  test_ship(3);
}

void StartAttackerTask_4(void *argument) {
  wait_start();
  test_ship(4);
}

void StartAttackerTask_5(void *argument) {
  wait_start();
  test_ship(5);
}
