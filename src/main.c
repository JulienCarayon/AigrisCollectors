#include <math.h>
#include <stdbool.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "cmsis_os.h"
#include "main.h"

#define MINIMAL_STACK_SIZE ((uint16_t)2048)
#define SHIP_MAX_NUMBER 9

osThreadId_t defaultTaskHandle;
osThreadId_t defaultTaskHandle_2;

void StartDefaultTask(void *argument);
void StartAdditionalTask(void *argument);

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

void StartDefaultTask(void *argument) {
  if (osMutexAcquire(osMutexTest, osWaitForever) != osOK) {
  }

  int _angle = 90;
  int _speed = 0;

  while (1) {
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
    } else {
      /* do nothing */
    }
  }
}
