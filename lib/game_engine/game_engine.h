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

typedef struct {
  uint16_t pos_X;
  uint16_t pos_Y;
} T_point;

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

typedef struct {
  uint8_t team;
  uint8_t ship_id;
  uint16_t abscisse;
  uint16_t ordinate;
  uint8_t status;
} T_ship_test;

typedef struct {
  uint8_t planet_ID;
  uint16_t pos_X;
  uint16_t pos_Y;
  int8_t ship_ID;
  bool saved;
} T_planet;

typedef struct {
  uint16_t pos_X;
  uint16_t pos_Y;
} T_planet_test;

extern T_planet *planets;
extern uint8_t nb_planets;
extern T_ship_test *ship;
extern uint8_t nb_ship;

void ship_manager(uint8_t id);
char *explore(uint8_t ship_id, char *command_buffer);
char *move(uint8_t ship_id, uint16_t angle, uint16_t speed,
           char *command_buffer);

void set_ship_type(T_ship *ship);
char *generate_command(T_command_type command_type, int ship_id, int angle,
                       int speed, char *command_buffer);

T_planet_test parse_planet(const char *chaine);
T_ship_test parse_ship(const char *chaine);
uint16_t get_distance_between_two_points(T_point starting_point,
                                         T_point ending_point);
uint16_t get_angle_between_two_points(T_point starting_point,
                                      T_point ending_point);

char *create_buffer(int buffer_size);
int free_buffer(char *buffer_ptr);

#endif // GAME_ENGINE_H