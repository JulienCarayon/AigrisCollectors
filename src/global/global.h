#ifndef GLOBAL_H
#define GLOBAL_H

#include "cmsis_os.h"
#include "../include/hardware.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define OS_DELAY 100
#define TASKS_SIZES 1024

osMutexId_t uartMutex_M;

extern const osMutexAttr_t uartMutex_attributes;
bool send_command(const char *command, char *response_buffer);
char *getsMutex(char *text);
void putsMutex(char *text);
char *osStatusToString(osStatus_t status);
char *longlong_to_string(long long num);
bool uart_data_available();

typedef enum
{
    UNKNOWN_SHIP,
    ATTACKERS_SHIP,
    EXPLORER_SHIP,
    COLLECTOR_SHIP
} T_ship_type;

typedef enum
{
    MOVE_CMD,
    FIRE_CMD,
    RADAR_CMD
} T_command_type;

typedef struct
{
    int id;
    int abscisse;
    int ordinate;
    int angle;
    int speed;
    bool status;
    T_ship_type ship_type;

} T_ship;
void testShip(uint8_t id);

char start_command_server[50];
extern bool is_comptetion_started;
void set_ship_type(T_ship *ship);
void generate_command(T_command_type command_type, int ship_id, int angle,
                      int speed, char *command_buffer);
char *boolToCString(bool value);
#endif