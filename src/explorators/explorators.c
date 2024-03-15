#include "explorators.h"

const osThreadAttr_t exploratorsTask_attributes = {
    .name = "exploratorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 2048,
};

void StartExploratorTask_1(void *argument)
{
    putsMutex("Explorer Task 1 started\n");
    while (1)
    {
        putsMutex("Explorer Task 1\n");
        osDelay(100);
    }
}

void StartExploratorTask_2(void *argument)
{
    putsMutex("Explorer Task 2 started\n");
    while (1)
    {
        putsMutex("Explorer Task 2\n");
        osDelay(100);
    }
}