#ifndef COLLECTORS_H
#define COLLECTORS_H
#include "cmsis_os.h"
#include "../global/global.h"

void StartCollectorTask_1(void *argument);
void StartCollectorTask_2(void *argument);


osThreadId_t collectorTaskHandles_1;
osThreadId_t collectorTaskHandles_2;



#endif