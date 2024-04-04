#include "attackers/attackers.h"
#include "collectors/collectors.h"
#include "explorators/explorators.h"
#include "hardware.h"
#include <OS_engine.h>
#include <math.h>
#include <stdbool.h>

#include "cmsis_os.h"
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

osThreadId_t mainTaskHandle;
void StartMainTask(void *argument);

osMemoryPoolId_t memory_pool_id = NULL;

int main(void)
{
    hardware_init();
    osKernelInitialize();

    os_engine_init();

    const osThreadAttr_t mainTask_attributes = {
        .name = "mainTask",
        .priority = (osPriority_t)osPriorityNormal1,
        .stack_size = 2048,
    };
    mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

    attackerTaskHandles_1 =
        osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    // attackerTaskHandles_2 =
    //     osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    // attackerTaskHandles_3 =
    //     osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    // attackerTaskHandles_4 =
    //     osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    // attackerTaskHandles_5 =
    //     osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    // exploratorTaskHandles_1 =
    //     osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    // exploratorTaskHandles_2 =
    //     osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);

    // collectorTaskHandles_1 =
    //     osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    // collectorTaskHandles_2 =
    //     osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);

    osKernelStart();
}

void StartMainTask(void *argument)
{

    putsMutex("AM I STUCK HERE ? \n");
    osStatus_t status;
    memory_pool_id = init_memory_pool();
    putsMutex("NO\n");
    putsMutex("MAIN : memory_pool_id : \n");
    putsMutex(memory_pool_id);
    putsMutex("\n");
    os_T_Memory_block *memory_block = NULL;
    memory_block = (os_T_Memory_block *)osMemoryPoolAlloc(memory_pool_id,
                                                          0U); // get Mem Block
    if (memory_block != NULL)
    {                                    // Mem Block was available
        memory_block->uint16_data_1 = 1; // do some work...
        memory_block->uint16_data_2 = 2;
        memory_block->uint16_data_3 = 3;
        memory_block->uint8_data_1 = 4;
        memory_block->uint8_data_2 = 5;
        putsMutex("memory_block->uint16_data_1=");
        char buffer[20];
        sprintf(buffer, "%lu", memory_block->uint16_data_1);
        putsMutex(buffer);
        putsMutex("\n");
        // status = osMemoryPoolFree(memory_pool_id, memory_block); // free mem block

        // if (status == osErrorNoMemory || status == osErrorParameter)
        // {
        //     while (1)
        //         ;
        // }
    }

    else
    {
        while (1)
        {
            puts("MEM POOL WRITE : memory_block is NULL\n");
        }
    }
    putsMutex("MAIN : osMemoryPoolGetCapacity : ");
    char buffer[20];
    sprintf(buffer, "%u", osMemoryPoolGetCapacity(memory_pool_id));
    putsMutex(buffer);
    putsMutex("\n ");
    while (1)
    {
        osDelay(1);
    }
}