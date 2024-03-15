#include "collectors.h"

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