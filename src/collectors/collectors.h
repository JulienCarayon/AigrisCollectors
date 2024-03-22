#ifndef COLLECTORS_H
#define COLLECTORS_H
#include "cmsis_os.h"
#include <game_engine.h>

extern const osThreadAttr_t collectorsTask_attributes;

osThreadId_t collectorTaskHandles_1;
osThreadId_t collectorTaskHandles_2;

void StartCollectorTask_1(void *argument);
void StartCollectorTask_2(void *argument);

#endif