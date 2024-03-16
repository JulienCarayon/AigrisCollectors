#include "collectors.h"

const osThreadAttr_t collectorsTask_attributes = {
    .name = "collectorsTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = TASKS_SIZES,
};

void StartCollectorTask_1(void *argument)
{
    // putsMutex("Collector Task 1 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(8);
        }
        osDelay(OS_DELAY);
    }
}

void StartCollectorTask_2(void *argument)
{
    // putsMutex("Collector Task 2 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(9);
        }
        osDelay(OS_DELAY);
    }
}