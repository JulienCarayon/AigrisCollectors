#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"

osThreadId_t mainTaskHandle;

osThreadId_t attackerTaskHandles_1;
osThreadId_t attackerTaskHandles_2;
osThreadId_t attackerTaskHandles_3;
osThreadId_t attackerTaskHandles_4;
osThreadId_t attackerTaskHandles_5;

osThreadId_t exploratorTaskHandles_1;
osThreadId_t exploratorTaskHandles_2;

osThreadId_t collectorTaskHandles_1;
osThreadId_t collectorTaskHandles_2;

void StartMainTask(void *argument);

void StartAttackerTask_1(void *argument);
void StartAttackerTask_2(void *argument);
void StartAttackerTask_3(void *argument);
void StartAttackerTask_4(void *argument);
void StartAttackerTask_5(void *argument);

void StartExploratorTask_1(void *argument);
void StartExploratorTask_2(void *argument);

void StartCollectorTask_1(void *argument);
void StartCollectorTask_2(void *argument);

int main(void)
{
    hardware_init();

    osKernelInitialize();

    const osThreadAttr_t mainTask_attributes = {
        .name = "mainTask",
        .priority = (osPriority_t)osPriorityNormal1,
        .stack_size = 128,
    };
    mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

    const osThreadAttr_t attackersTask_attributes = {
        .name = "attackersTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 128,
    };

    attackerTaskHandles_1 = osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    attackerTaskHandles_2 = osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    attackerTaskHandles_3 = osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    attackerTaskHandles_4 = osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    attackerTaskHandles_5 = osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    const osThreadAttr_t exploratorsTask_attributes = {
        .name = "exploratorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 128,
    };
    exploratorTaskHandles_1 = osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    exploratorTaskHandles_2 = osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);    

    const osThreadAttr_t collectorsTask_attributes = {
        .name = "collectorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 128,
    };
    collectorTaskHandles_1 = osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    collectorTaskHandles_2 = osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);






    osKernelStart();

    while (1)
    {
    }
}

void StartMainTask(void *argument)
{
    puts("Main Thread Task started\n");
    while (1)
    {
        puts("Main Thread Task\n");
        osDelay(1);
    }
}

void StartAttackerTask_1(void *argument)
{
    puts("Attacker Task 1 started\n");
    while (1)
    {
        puts("Attacker Task 1\n");
        osDelay(1);
    }
}

void StartAttackerTask_2(void *argument)
{
    puts("Attacker Task 2 started\n");
    while (1)
    {
        puts("Attacker Task 2\n");
        osDelay(1);
    }
}

void StartAttackerTask_3(void *argument)
{
    puts("Attacker Task 3 started\n");
    while (1)
    {
        puts("Attacker Task 3\n");
        osDelay(1);
    }
}

void StartAttackerTask_4(void *argument)
{
    puts("Attacker Task 4 started\n");
    while (1)
    {
        puts("Attacker Task 4\n");
        osDelay(1);
    }
}

void StartAttackerTask_5(void *argument)
{
    puts("Attacker Task 5 started\n");
    while (1)
    {
        puts("Attacker Task 5\n");
        osDelay(1);
    }
}

void StartExploratorTask_1(void *argument)
{
    puts("Explorer Task 1 started\n");
    while (1)
    {
        puts("Explorer Task 1\n");
        osDelay(1);
    }
}

void StartExploratorTask_2(void *argument)
{
    puts("Explorer Task 2 started\n");
    while (1)
    {
        puts("Explorer Task 2\n");
        osDelay(1);
    }
}

void StartCollectorTask_1(void *argument)
{
    puts("Explorer Task 1 started\n");
    while (1)
    {
        puts("Explorer Task 1\n");
        osDelay(1);
    }
}

void StartCollectorTask_2(void *argument)
{
    puts("Collector Task 2 started\n");
    while (1)
    {
        puts("Collector Task 2\n");
        osDelay(1);
    }
}