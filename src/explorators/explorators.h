#ifndef EXPLORATORS_H
#define EXPLORATORS_H
#include "cmsis_os.h"
#include "../global/global.h"

void StartExploratorTask_1(void *argument);
void StartExploratorTask_2(void *argument);


osThreadId_t exploratorTaskHandles_1;
osThreadId_t exploratorTaskHandles_2;



#endif