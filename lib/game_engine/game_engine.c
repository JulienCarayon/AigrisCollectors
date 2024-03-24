#include "game_engine.h"
#include "OS_engine.h"

T_planet *planets = NULL;
T_ship_test *ship = NULL;

char *explore(uint8_t ship_id, char *command_buffer) {
  command_buffer = generate_command(RADAR_CMD, ship_id, 0, 0, command_buffer);
  return command_buffer;
}

char *move(uint8_t ship_id, uint16_t angle, uint16_t speed,
           char *command_buffer) {
  command_buffer =
      generate_command(MOVE_CMD, ship_id, angle, speed, command_buffer);
  return command_buffer;
}

char *generate_command(T_command_type command_type, int ship_id, int angle,
                       int speed, char *command_buffer) {
  switch (command_type) {
  case MOVE_CMD:
    snprintf(command_buffer, BUFFER_SIZE, "MOVE %d %d %d\n", ship_id, angle,
             speed);
    break;
  case FIRE_CMD:
    snprintf(command_buffer, BUFFER_SIZE, "FIRE %d %d\n", ship_id, angle);
    break;
  case RADAR_CMD:
    snprintf(command_buffer, BUFFER_SIZE, "RADAR %d\n", ship_id);
    break;
  }

  return command_buffer;
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

void ship_manager(uint8_t id) {
  while (1) {
    static int _angle = 90;
    static int _speed = 0;
    char command_buffer[100] = {""};
    char answer_buffer[100] = {""};

    if (_angle >= 359) {
      _angle = 0;
    }

    if (_speed >= 999) {
      _speed = 0;
    }

    _angle += 10;
    _speed += 10;

    generate_command(MOVE_CMD, id, _angle, _speed, command_buffer);
    send_command(command_buffer, answer_buffer);
  }
}

uint16_t get_distance_between_two_points(T_point starting_point,
                                         T_point ending_point) {
  return sqrt(pow(ending_point.pos_X - starting_point.pos_X, 2) +
              pow(ending_point.pos_Y - starting_point.pos_Y, 2));
}

uint16_t get_angle_between_two_points(T_point starting_point,
                                      T_point ending_point) {
  double angle_radian = atan2(ending_point.pos_Y - starting_point.pos_Y,
                              ending_point.pos_X - starting_point.pos_X);
  int16_t angle_degree = (int16_t)(angle_radian * (180.0 / M_PI));

  if (angle_degree < 0)
    angle_degree += 360;

  return (uint16_t)angle_degree;
}

T_planet_test parse_planet(const char *chaine) {
  T_planet_test planet;
  char type;
  sscanf(chaine, "%c %hd %hd", &type, &planet.pos_X, &planet.pos_Y);
  return planet;
}

T_ship_test parse_ship(const char *chaine) {
  T_ship_test ship;
  char type;
  sscanf(chaine, "%c %hhd %hhd %hd %hd %hhd", &type, &ship.team, &ship.ship_id,
         &ship.abscisse, &ship.ordinate, &ship.status);
  return ship;
}

char *create_buffer(int buffer_size) {
  static int counter = 0;
  counter++;
  char *buffer = (char *)malloc(buffer_size * sizeof(char));

  if (buffer == NULL) {
    while (1) {
    }
  }

  return buffer;
}

int free_buffer(char *buffer_ptr) {
  if (buffer_ptr != NULL) {
    free(buffer_ptr);

    return 0;
  }
  return -1;
}