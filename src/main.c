#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"
#include "hardware.h"

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

    attackerTaskHandles_1 = osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    attackerTaskHandles_2 = osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    attackerTaskHandles_3 = osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    attackerTaskHandles_4 = osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    attackerTaskHandles_5 = osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    exploratorTaskHandles_1 = osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    exploratorTaskHandles_2 = osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);    

    collectorTaskHandles_1 = osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    collectorTaskHandles_2 = osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);
    
    putsMutex_M = osMutexNew(&putsMutex_attributes);
    puts("BOOTED");

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