#ifndef ATTACKERS_H
#define ATTACKERS_H
#include "cmsis_os.h"
#include "../global/global.h"

void StartAttackerTask_1(void *argument);
void StartAttackerTask_2(void *argument);
void StartAttackerTask_3(void *argument);
void StartAttackerTask_4(void *argument);
void StartAttackerTask_5(void *argument);

osThreadId_t attackerTaskHandles_1;
osThreadId_t attackerTaskHandles_2;
osThreadId_t attackerTaskHandles_3;
osThreadId_t attackerTaskHandles_4;
osThreadId_t attackerTaskHandles_5;


#endif