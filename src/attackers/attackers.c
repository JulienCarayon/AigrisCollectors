#include "attackers.h"

const osThreadAttr_t attackersTask_attributes = {
        .name = "attackersTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = TASKS_SIZES,
};

void StartAttackerTask_1(void *argument)
{   
    // putsMutex("Attacker Task 1 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(1);
        }
        osDelay(OS_DELAY);
    }
}

void StartAttackerTask_2(void *argument)
{

    // putsMutex("Attacker Task 2 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(2);
        }
        osDelay(OS_DELAY);
    }
}

void StartAttackerTask_3(void *argument)
{
    // putsMutex("Attacker Task 3 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(3);
        }
        osDelay(OS_DELAY);
    }
}

void StartAttackerTask_4(void *argument)
{
    // putsMutex("Attacker Task 4 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(4);
        }
        osDelay(OS_DELAY);
    }
}

void StartAttackerTask_5(void *argument)
{
    // putsMutex("Attacker Task 5 started\n");
    while (1)
    {
        if(is_comptetion_started == true){
            testShip(5);
        }
        osDelay(OS_DELAY);
    }
}