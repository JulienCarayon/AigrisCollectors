#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#include <constants.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  uint16_t pos_X;
  uint16_t pos_Y;
} T_point;

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

// TODO add T_ship_type (modify set_ship_type)?
typedef struct
{
  int8_t team_ID;
  int8_t ship_ID;
  uint16_t pos_X;
  uint16_t pos_Y;
  uint8_t broken; // same size as an boolean
} T_ship;

typedef struct
{
  uint16_t planet_ID;
  uint16_t pos_X;
  uint16_t pos_Y;
  int8_t ship_ID;
  uint8_t planet_saved; // same size as an boolean
} T_planet;

typedef struct
{
  uint16_t pos_X;
  uint16_t pos_Y;
  uint16_t uint16_data;
  uint8_t uint8_data;
  uint8_t uint8_data_2; // same size as an boolean
} T_base;

/*
    TODO use extern variable ?
    TODO add planet_saved variable
*/
extern uint8_t nb_planets;
extern uint8_t nb_ship;

void ship_manager(uint8_t id);
char *explore(uint8_t ship_id, char *command_buffer);
char *move(uint8_t ship_id, uint16_t angle, uint16_t speed,
           char *command_buffer);

void set_ship_type(T_ship *ship);
char *generate_command(T_command_type command_type, int ship_id, int angle,
                       int speed, char *command_buffer);

void parse_planets(const char *server_response, T_planet *planets,
                   uint8_t *num_planets);
void parse_ships(const char *server_response, T_ship *ships);
void parse_base(const char *server_response, T_base *base);

uint16_t get_distance_between_two_points(T_point starting_point,
                                         T_point ending_point);
uint16_t get_angle_between_two_points(T_point starting_point,
                                      T_point ending_point);
T_point coordinate_to_point(uint16_t x, uint16_t y);
char *create_buffer(int buffer_size);
void free_buffer(char *buffer_ptr);

void show_planet(T_planet *planet);

#endif // GAME_ENGINE_H