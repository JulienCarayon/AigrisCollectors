#include "game_engine.h"
#include "OS_engine.h"

T_planet planets[MAX_PLANETS_NUMBER] = {
    {1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4},
    {1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4}};

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
  if (ship->ship_ID >= 1 && ship->ship_ID <= 5) {
    // ship->ship_type = ATTACKERS_SHIP;
  } else if (ship->ship_ID > 5 && ship->ship_ID <= 7) {
    // ship->ship_type = EXPLORER_SHIP;
  } else if (ship->ship_ID >= 8 && ship->ship_ID <= 9) {
    // ship->ship_type = COLLECTOR_SHIP;
  } else {
    // ship->ship_type = UNKNOWN_SHIP;
  }
}

void ship_manager(uint8_t id) {
  char command_buffer[BUFFER_SIZE] = {0};
  char answer_buffer[RX_COMMAND_BUFFER_SIZE] = {0};

#ifdef DEBUG
  putsMutex("THREADS -> memory_pool_id :");
  char adresse_str[20];
  sprintf(adresse_str, "%p", memory_pool_id);
  putsMutex(adresse_str);
  putsMutex("\n");
#endif

  while (1) {
#ifdef DEBUG
    osStatus_t status;
    os_T_Memory_block *memory_block = NULL;
    memory_block = (os_T_Memory_block *)osMemoryPoolAlloc(memory_pool_id, 0U);

    if (memory_block != NULL) {
      uint16_t data1 = memory_block->uint16_data_1;
      uint16_t data2 = memory_block->uint16_data_2;
      uint16_t data3 = memory_block->uint16_data_3;
      uint8_t data4 = memory_block->uint8_data_1;
      uint8_t data5 = memory_block->uint8_data_2;
      putsMutex("data1=");
      char buffer[20];
      sprintf(buffer, "%u", data1);
      putsMutex(buffer);
      putsMutex("\n");
    } else {
      while (1) {
        puts("MEM POOL READ : memory_block is NULL\n");
      }
    }
#endif

    memset(command_buffer, 0, sizeof(command_buffer));
    memset(answer_buffer, 0, sizeof(answer_buffer));

    static int _angle = 90;
    static int _speed = 0;

    if (_angle >= 359) {
      _angle = 0;
    }

    if (_speed >= 999) {
      _speed = 0;
    }

    _angle += 10;
    _speed += 10;

    if (id == 6) {
      int num_planets;

      generate_command(RADAR_CMD, id, _angle, _speed, command_buffer);
      send_command(command_buffer, answer_buffer);
      parse_planets(answer_buffer, planets, &num_planets);
      afficher_planet(planets);
    }
  }
}

void afficher_planet(T_planet *planet) {
  char buffer[RX_COMMAND_BUFFER_SIZE];

  //"P %hu %hu %hu %hhd %hhu",
  sprintf(buffer,
          "planet_ID: %u, pos_X: %u, pos_Y: %u, ship_ID: %d, planet_saved: %u",
          planet[0].planet_ID, planet[0].pos_X, planet[0].pos_Y,
          planet[0].ship_ID, planet[0].planet_saved);

  putsMutex(buffer);
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

char *create_buffer(int buffer_size) {
  char *buffer = (char *)malloc(buffer_size * sizeof(char));

  if (buffer == NULL) {
    while (1) {
    }
  }

  return buffer;
}

void free_buffer(char *buffer_ptr) {
  if (buffer_ptr != NULL) {
    free(buffer_ptr);
  } else {
    while (1)
      ;
  }
}

void parse_planets(const char *server_response, T_planet *planets,
                   int *num_planets) {
  *num_planets = 0;
  const char *str_token;
  char *save_ptr;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);

  while (str_token != NULL) {
    if (str_token[0] == SERVER_RESPONSE_PLANET_DELIMITER) {
      if (*num_planets > MAX_PLANETS_NUMBER) { // TODO test with >=
        putsMutex("num_planets > MAX_PLANETS_NUMBER");
        exit(1);
      }

      sscanf(str_token, "P %hu %hu %hu %hhd %hhu",
             &planets[*num_planets].planet_ID, &planets[*num_planets].pos_X,
             &planets[*num_planets].pos_Y, &planets[*num_planets].ship_ID,
             &planets[*num_planets].planet_saved);
      (*num_planets)++;
    }
    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}

void parse_ships(const char *server_response, T_ship *ships) {
  const char *str_token;
  char *save_ptr;
  uint8_t ship_id = 0;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);
  while (str_token != NULL) {
    if (str_token[0] == 'S') {
      sscanf(str_token, "S %hhd %hhd %hu %hu %hhu", &ships[ship_id].team_ID,
             &ships[ship_id].ship_ID, &ships[ship_id].pos_X,
             &ships[ship_id].pos_Y, &ships[ship_id].broken);

      ship_id++;
    }

    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}

void parse_base(const char *server_response, T_base *base) {
  const char *str_token;
  char *save_ptr;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);
  while (str_token != NULL) {
    if (str_token[0] == 'B') {
      sscanf(str_token, "B %hu %hu %hu %hhu %hhu", &base[0].pos_X,
             &base[0].pos_Y, &base[0].uint16_data, &base[0].uint8_data,
             &base[0].uint8_data_2);
    }

    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}