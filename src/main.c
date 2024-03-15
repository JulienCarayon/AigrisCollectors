#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"

#include "global/global.h"

#include "attackers/attackers.h"
#include "explorators/explorators.h"
#include "collectors/collectors.h"

osThreadId_t mainTaskHandle;

void StartMainTask(void *argument);

int main(void)
{
    hardware_init();

    osKernelInitialize();
    

    const osThreadAttr_t mainTask_attributes = {
        .name = "mainTask",
        .priority = (osPriority_t)osPriorityNormal1,
        .stack_size = 2048,
    };
    mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

    const osThreadAttr_t attackersTask_attributes = {
        .name = "attackersTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };

    attackerTaskHandles_1 = osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    attackerTaskHandles_2 = osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    attackerTaskHandles_3 = osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    attackerTaskHandles_4 = osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    attackerTaskHandles_5 = osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    const osThreadAttr_t exploratorsTask_attributes = {
        .name = "exploratorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };
    exploratorTaskHandles_1 = osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    exploratorTaskHandles_2 = osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);    

    const osThreadAttr_t collectorsTask_attributes = {
        .name = "collectorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };
    collectorTaskHandles_1 = osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    collectorTaskHandles_2 = osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);
    
    const osMutexAttr_t mutex_attributes = {
        .name = "putsMutex",
        osMutexPrioInherit,  // attr_bits
        NULL,                // memory for control block   
        0U                   // size for control block
    };
    putsMutex_M = osMutexNew(&mutex_attributes);
    puts("BOOTED");
    // putsMutex_M = xSemaphoreCreateMutex();
    osKernelStart();

    while (1)
    {
    }
}





void StartMainTask(void *argument)
{
    putsMutex("Main Thread Task started\n");
    while (1)
    {   
        putsMutex("Main Thread Task :");
        osDelay(100);
    }
}