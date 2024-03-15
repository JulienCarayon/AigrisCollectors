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
    puts("BOOTED");


typedef enum {
  UNKNOWN_SHIP,
  ATTACKERS_SHIP,
  EXPLORER_SHIP,
  COLLECTOR_SHIP
} T_ship_type;

typedef enum { MOVE_CMD, FIRE_CMD, RADAR_CMD } T_command_type;

typedef struct {
  int id;
  int abscisse;
  int ordinate;
  int angle;
  int speed;
  bool status;
  T_ship_type ship_type;

} T_ship;

char command_buffer[100];
char start_command_server[50];
bool is_comptetion_started = false;

void set_ship_type(T_ship *ship);
void generate_command(T_command_type command_type, int ship_id, int angle,
                      int speed, char *command_buffer);

osMutexId_t osMutexTest;

int main(void) {
  hardware_init();

  osKernelInitialize();

  const osThreadAttr_t defaultTask_attributes = {
      .name = "defaultTask",
      .priority = (osPriority_t)osPriorityNormal,
      .stack_size = MINIMAL_STACK_SIZE,
  };

  defaultTaskHandle =
      osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  if (strstr(gets(start_command_server), "START") != NULL) {
    if (osMutexRelease(osMutexTest) != osOK) {
      return 0;
    }

    is_comptetion_started = true;
    osKernelStart();
  } else {
    is_comptetion_started = false;
  }

  while (1) {
  }
}

void set_ship_type(T_ship *ship) {
  if (ship->id >= 1 && ship->id <= 5) {
    ship->ship_type = ATTACKERS_SHIP;
  } else if (ship->id > 5 && ship->id <= 7) {
    ship->ship_type = EXPLORER_SHIP;
  } else if (ship->id >= 8 && ship->id <= 9) {
    ship->ship_type = COLLECTOR_SHIP;
  } else {
    ship->ship_type = UNKNOWN_SHIP;
  }
}

void StartMainTask(void *argument)
{
    putsMutex("Main Thread Task started\n");
    while (1)
    {   
        putsMutex("Main Thread Task :\n");
        char buffer[256]; // Utiliser un tableau pour stocker les données lues
        if (uart_data_available()){
            getsMutex(buffer);
            putsMutex(buffer);
            if(strstr(buffer,"START")!=NULL){
                putsMutex("GAME STARTED");
                is_comptetion_started = true
            }
            
            int _angle = 90;
            int _speed = 0;

 
            if (is_comptetion_started == true) {
              if (_angle >= 359) {
                _angle = 0;
              }

              if (_speed >= 2999) {
                _speed = 0;
              }

              _angle += 10;
              _speed += 10;

              generate_command(MOVE_CMD, 4, _angle, _speed, command_buffer);
              // generate_command(FIRE_CMD, 1, _angle, _speed, command_buffer);

              puts(command_buffer);

              osDelay(1);
             } 
             else {
              /* do nothing */
             }
        }
        osDelay(1);
    }
void generate_command(T_command_type command_type, int ship_id, int angle,
                      int speed, char *command_buffer) {
  switch (command_type) {
  case MOVE_CMD:
    snprintf(command_buffer, 100, "MOVE %d %d %d\n", ship_id, angle, speed);
    break;
  case FIRE_CMD:
    snprintf(command_buffer, 100, "FIRE %d %d\n", ship_id, angle);
    break;
  case RADAR_CMD:
    snprintf(command_buffer, 100, "RADAR %d\n", ship_id);
    break;
  }
}