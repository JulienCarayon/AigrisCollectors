#include "attackers.h"

void StartAttackerTask_1(void *argument)
{   
    putsMutex("Attacker Task 1 started\n");
    while (1)
    {
        putsMutex("Attacker Task 1\n");
        osDelay(100);
    }
}

void StartAttackerTask_2(void *argument)
{

    putsMutex("Attacker Task 2 started\n");
    while (1)
    {
        putsMutex("Attacker Task 2\n");
        osDelay(100);
    }
}

void StartAttackerTask_3(void *argument)
{
    putsMutex("Attacker Task 3 started\n");
    while (1)
    {
        putsMutex("Attacker Task 3\n");
        osDelay(100);
    }
}

void StartAttackerTask_4(void *argument)
{
    putsMutex("Attacker Task 4 started\n");
    while (1)
    {
        putsMutex("Attacker Task 4\n");
        osDelay(100);
    }
}

void StartAttackerTask_5(void *argument)
{
    putsMutex("Attacker Task 5 started\n");
    while (1)
    {
        putsMutex("Attacker Task 5\n");
        osDelay(100);
    }
}