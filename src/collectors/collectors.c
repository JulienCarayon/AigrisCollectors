#include "collectors.h"

const osThreadAttr_t collectorsTask_attributes = {
    .name = "collectorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 2048,
};

void StartCollectorTask_1(void *argument)
{
    putsMutex("Explorer Task 1 started\n");
    while (1)
    {
        putsMutex("Explorer Task 1\n");
        osDelay(100);
    }
}

void StartCollectorTask_2(void *argument)
{
    putsMutex("Collector Task 2 started\n");
    while (1)
    {
        putsMutex("Collector Task 2\n");
        osDelay(100);
        osThreadYield();
    }
}