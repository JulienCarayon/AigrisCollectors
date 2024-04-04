#ifndef EXPLORATORS_H
#define EXPLORATORS_H
#include "OS_types.h"
#include <game_engine.h>

extern const osThreadAttr_t exploratorsTask_attributes;

os_thread_id exploratorTaskHandles_1;
os_thread_id exploratorTaskHandles_2;

void StartExploratorTask_1(void *argument);
void StartExploratorTask_2(void *argument);

#endif