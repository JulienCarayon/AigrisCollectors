#include "game_engine.h"
#include "OS_engine.h"

uint8_t nb_planets = 0;
T_game_data game_data[NUMBER_OF_GAME_DATA];
T_planet planets[MAX_PLANETS_NUMBER] = {
    {1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4},
    {5, 5, 5, 5, 5}, {6, 6, 6, 6, 6}, {7, 7, 7, 7, 7}, {8, 8, 8, 8, 8}};

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
  uint32_t size_of_game_data = 0;
  initialize_game_data(game_data);

  while (1) {
    size_of_game_data = sizeof(game_data);
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
      generate_command(RADAR_CMD, id, _angle, _speed, command_buffer);
      send_command(command_buffer, answer_buffer);
      parse_planets_gpt(answer_buffer, game_data, &nb_planets);
      parse_ships(answer_buffer, game_data);
      parse_base(answer_buffer, game_data);
    }
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

void write_game_data(const char *server_response) {}

void parse_planets(const char *server_response, T_game_data *game_data,
                   uint8_t *num_planets) {
  *num_planets = 0;
  const char *str_token;
  char *save_ptr;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);

  while (str_token != NULL) {
    if (str_token[0] == SERVER_RESPONSE_PLANET_DELIMITER) {
      if (*num_planets >= MAX_PLANETS_NUMBER) {
        // TODO while(1) tu pleures ?
      }

      sscanf(str_token, "P %hu %hu %hu %hhd %hhu",
             &game_data->planets[*num_planets].planet_ID,
             &game_data->planets[*num_planets].pos_X,
             &game_data->planets[*num_planets].pos_Y,
             &game_data->planets[*num_planets].ship_ID,
             &game_data->planets[*num_planets].planet_saved);
      (*num_planets)++;
    }
    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}

void parse_planets_gpt(const char *server_response, T_game_data *game_data,
                       uint8_t *num_planets) {
  *num_planets = 0;
  const char *str = server_response;
  const char *delimiter = strchr(
      str, SERVER_RESPONSE_DELIMITER[0]); // Recherche du premier délimiteur

  while (delimiter != NULL) {
    if (*str == SERVER_RESPONSE_PLANET_DELIMITER) {
      if (*num_planets >= MAX_PLANETS_NUMBER) {
        // Gérer le dépassement du nombre maximal de planètes
        break;
      }

      sscanf(str, "P %hu %hu %hu %hhd %hhu",
             &game_data->planets[*num_planets].planet_ID,
             &game_data->planets[*num_planets].pos_X,
             &game_data->planets[*num_planets].pos_Y,
             &game_data->planets[*num_planets].ship_ID,
             &game_data->planets[*num_planets].planet_saved);
      (*num_planets)++;
    }

    str = delimiter + 1; // Passer au prochain caractère après le délimiteur
    delimiter = strchr(
        str, SERVER_RESPONSE_DELIMITER[0]); // Recherche du prochain délimiteur
  }

  // Traiter le dernier élément de la chaîne s'il n'y a pas de délimiteur après
  if (*str == SERVER_RESPONSE_PLANET_DELIMITER) {
    if (*num_planets < MAX_PLANETS_NUMBER) {
      sscanf(str, "P %hu %hu %hu %hhd %hhu",
             &game_data->planets[*num_planets].planet_ID,
             &game_data->planets[*num_planets].pos_X,
             &game_data->planets[*num_planets].pos_Y,
             &game_data->planets[*num_planets].ship_ID,
             &game_data->planets[*num_planets].planet_saved);
      (*num_planets)++;
    }
  }
}

void parse_ships(const char *server_response, T_game_data *game_data) {
  const char *str_token;
  char *save_ptr;
  uint8_t ship_id = 0;
  uint8_t *num_ship;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  uint8_t debug_team_ID = 0;
  uint8_t debug_ship_ID = 0;
  uint16_t debug_pos_X = 0;
  uint16_t debug_pos_Y = 0;
  uint8_t debug_broken = 0;

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);
  while (str_token != NULL) {
    if (str_token[0] == SERVER_RESPONSE_SHIP_DELIMITER) {
      if (ship_id >= 36) {
        // TODO while(1) tu pleures ?
      }

      sscanf(str_token, "S %hhu %hhu %hu %hu %hhu",
             &game_data->ships[*num_ship].team_ID,
             &game_data->ships[*num_ship].ship_ID,
             &game_data->ships[*num_ship].pos_X,
             &game_data->ships[*num_ship].pos_Y,
             &game_data->ships[*num_ship].broken);

      (*num_ship)++;
    }

    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}

void parse_base(const char *server_response, T_game_data *game_data) {
  const char *str_token;
  char *save_ptr;
  char server_response_copy[strlen(server_response) + 1];
  strcpy(server_response_copy, server_response);

  str_token =
      strtok_r(server_response_copy, SERVER_RESPONSE_DELIMITER, &save_ptr);
  while (str_token != NULL) {
    if (str_token[0] == 'B') {
      sscanf(str_token, "B %hu %hu", &game_data->base[0].pos_X,
             &game_data->base[0].pos_Y);
    }

    str_token = strtok_r(NULL, SERVER_RESPONSE_DELIMITER, &save_ptr);
  }
}

void show_planet(T_planet *planet) {
  char buffer[RX_COMMAND_BUFFER_SIZE];

  for (uint8_t id = 0; id < nb_planets; id++) {
    sprintf(
        buffer,
        "planet_ID: %u, pos_X: %u, pos_Y: %u, ship_ID: %d, planet_saved: %u",
        planet[id].planet_ID, planet[id].pos_X, planet[id].pos_Y,
        planet[id].ship_ID, planet[id].planet_saved);

    puts(buffer);
  }
}

void initialize_game_data(T_game_data *game_data) {
  for (int i = 0; i < 8; i++) {
    game_data->planets[i].planet_ID = 0;
    game_data->planets[i].pos_X = 0;
    game_data->planets[i].pos_Y = 0;
    game_data->planets[i].ship_ID = 0;
    game_data->planets[i].planet_saved = 0;
  }

  for (int i = 0; i < 9 * 4; i++) {
    game_data->ships[i].team_ID = 1;
    game_data->ships[i].ship_ID = 1;
    game_data->ships[i].pos_X = 1;
    game_data->ships[i].pos_Y = 1;
    game_data->ships[i].broken = 1;
  }

  game_data->base->pos_X = 0;
  game_data->base->pos_Y = 0;
}