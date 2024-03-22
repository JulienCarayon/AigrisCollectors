#include <math.h>
#include <stdbool.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "cmsis_os.h"
#include "hardware.h"

#include "global/global.h"

#include "attackers/attackers.h"
#include "explorators/explorators.h"
#include "collectors/collectors.h"
#include <stdio.h>
#include <string.h>


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

    // La variable suivante enfreint la règle 5.1
    char thisIsAVeryLongIdentifierThatExceedsThe31CharacterLimitthisIsAVeryLongIdentifierThatExceedsThe31CharacterLimit;

    // Les variables suivantes enfreignent la règle 7.1
    int octalConstant = 0123;
    char octalEscapeSequence = '\012';

    // La ligne suivante enfreint la règle 14.4
    goto illegalLabel;

illegalLabel:
    attackerTaskHandles_1 = osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    attackerTaskHandles_2 = osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    attackerTaskHandles_3 = osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    attackerTaskHandles_4 = osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    attackerTaskHandles_5 = osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    exploratorTaskHandles_1 = osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    exploratorTaskHandles_2 = osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);

    collectorTaskHandles_1 = osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    collectorTaskHandles_2 = osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);

    uartMutex_M = osMutexNew(&uartMutex_attributes);
    // puts("BOOTED");

    osKernelStart();
}

void StartMainTask(void *argument)
{
    // putsMutex("Main Thread Task started\n");
    while (1)
    {
        // putsMutex("Main Thread Task :\n");
        char buffer[256]; // Utiliser un tableau pour stocker les données lues
        if (uart_data_available() && is_comptetion_started == false)
        {
            getsMutex(buffer);
            // putsMutex(buffer);
            if (strstr(buffer, "START") != NULL)
            {
                // putsMutex("GAME STARTED");
                is_comptetion_started = true;
            }
        }
        osDelay(1);
    }
}