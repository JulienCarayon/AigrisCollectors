#include <constants.h>
#include <game_engine.h>
#include <unity.h>

void setUp(void) {}
void tearDown(void) {}

void test_get_angle_between_two_points(void) {
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 10000;
  point_B.pos_Y = 10000;

  TEST_ASSERT_EQUAL_INT(get_angle_between_two_points(point_A, point_B), 349);
}

void test_get_distance_between_two_points(void) {
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 17000;
  point_B.pos_Y = 1000;

  TEST_ASSERT_EQUAL_INT(get_distance_between_two_points(point_A, point_B),
                        15620);
}

void test_explore(void) {
  char *buffer = create_buffer(BUFFER_SIZE);
  TEST_ASSERT_EQUAL_STRING(explore(7, buffer), "RADAR 7\n");
}

void test_planet_parsing(void) {
  const char *input = "P 495 10000 20000 -1 0,P 25 3040 40 -1 1,P 1445 340 1 1 "
                      "1,S 0 4 13000 0 0,B 10000 10000";

  T_planet expected_planets[] = {
      {495, 10000, 20000, -1, 0}, {25, 3040, 40, -1, 1}, {1445, 340, 1, 1, 1}};

  T_game_data game_data[NUMBER_OF_GAME_DATA];
  uint8_t number_of_planets;

  parse_planets_gpt(input, game_data, &number_of_planets);

  TEST_ASSERT_EQUAL_INT_MESSAGE(
      sizeof(expected_planets) / sizeof(expected_planets[0]), number_of_planets,
      "Number of expected_planets invalid !");

  TEST_ASSERT_EQUAL_INT(3, number_of_planets);

  for (int i = 0; i < number_of_planets; i++) {
    TEST_ASSERT_EQUAL_INT(expected_planets[i].planet_ID,
                          game_data->planets[i].planet_ID);
    TEST_ASSERT_EQUAL_INT(expected_planets[i].pos_X,
                          game_data->planets[i].pos_X);
    TEST_ASSERT_EQUAL_INT(expected_planets[i].pos_Y,
                          game_data->planets[i].pos_Y);
    TEST_ASSERT_EQUAL_INT(expected_planets[i].ship_ID,
                          game_data->planets[i].ship_ID);
    TEST_ASSERT_EQUAL_INT(expected_planets[i].planet_saved,
                          game_data->planets[i].planet_saved);
  }
}

void test_test(void) { TEST_ASSERT_EQUAL_UINT8(6, 6); }

void test_ship_parsing(void) {
  const char *input = "P 495 10000 20000 -1 0,P 95 1000 200 -1 0,S 0 1 10000 "
                      "253 1,S 0 2 12000 53 "
                      "0,S 0 3 10 13 0,S 4 4 4 4 4,B 11111 11111";

  T_ship expected_ships[] = {{0, 1, 10000, 253, 1},
                             {0, 2, 12000, 53, 0},
                             {0, 3, 10, 13, 0},
                             {4, 4, 4, 4, 4}};
  T_game_data game_data[NUMBER_OF_GAME_DATA];
  uint8_t number_of_ships = 0;

  parse_ships_gpt(input, game_data, &number_of_ships);

  TEST_ASSERT_EQUAL_INT(4, number_of_ships);

  for (int i = 0; i < number_of_ships; i++) {
    TEST_ASSERT_EQUAL_INT(expected_ships[i].team_ID,
                          game_data->ships[i].team_ID);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].ship_ID,
                          game_data->ships[i].ship_ID);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].pos_X, game_data->ships[i].pos_X);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].pos_Y, game_data->ships[i].pos_Y);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].broken, game_data->ships[i].broken);
  }
}

void test_get_ship_position(void) {
  T_ship ship = {0, 1, 1520, 11325, 0};
  T_point ship_pos = get_ship_position(ship);
  T_point exepected_ship_pos = {1520, 11325};

  TEST_ASSERT_EQUAL_INT(exepected_ship_pos.pos_X, ship_pos.pos_X);
  TEST_ASSERT_EQUAL_INT(exepected_ship_pos.pos_Y, ship_pos.pos_Y);
}

void test_get_planet_position(void) {
  T_planet planet = {495, 10000, 20000, -1, 0};
  T_point planet_pos = get_planet_position(planet);
  T_point exepected_planet_pos = {10000, 20000};

  TEST_ASSERT_EQUAL_INT(exepected_planet_pos.pos_X, planet_pos.pos_X);
  TEST_ASSERT_EQUAL_INT(exepected_planet_pos.pos_Y, planet_pos.pos_Y);
}

void test_get_base_position(void) {
  T_base base = {10000, 0};
  T_point base_pos = get_base_position(base);
  T_point exepected_base_pos = {10000, 0};

  TEST_ASSERT_EQUAL_INT(exepected_base_pos.pos_X, base_pos.pos_X);
  TEST_ASSERT_EQUAL_INT(exepected_base_pos.pos_Y, base_pos.pos_Y);
}

void test_direction(void) {

  // arguments :
  //    - mode : 1 planet / 2 ship / 3 base
  //    - who  : id ship
  //    - item id

  // TODO add base coo for other teams

  // T_ship ships = {{0, 1, 1000, 0, 0}, {0, 6, 2000, 0, 0}, {0, 9, 30000, 0,
  // 0}}; T_planet planets = {{45106, 10000, 20000, -1, 0}, {785, 2000, 2000,
  // -1, 0}}; T_base base = {10000, 0};

  // 1er test  : ship id (8) vers planet (0) -> mode 1

  // 2eme test : ship id (8) vers base       -> mode 3
}

void test_ship_parsing_numberf_of_ships(void) {

  const char *input_1_ship = "S 0 1 10000 540 0,";

  const char *input_4_ships =
      "P 495 10000 20000 -1 0,P 95 1000 200 -1 0,S 0 1 10000 "
      "253 1,S 0 2 12000 53 "
      "0,S 0 3 10 13 0,S 4 4 4 4 4,B 11111 11111";

  const char *input_10_ships =
      "P 495 10000 20000 -1 0,P 95 1000 200 -1 0,S 0 1 10000 "
      "253 1,S 0 2 12000 53 "
      "0,S 0 3 10 13 0,S 0 3 10 13 0,S 0 3 10 13 0,S 0 3 10 13 0,S 0 3 10 13 "
      "0,S 0 3 10 13 0,S 0 3 10 13 0,S 4 4 4 4 4,B 11111 11111";

  T_game_data game_data[NUMBER_OF_GAME_DATA];

  uint8_t number_of_ships_1 = 0;
  uint8_t number_of_ships_4 = 0;
  uint8_t number_of_ships_10 = 0;

  parse_ships_gpt(input_1_ship, game_data, &number_of_ships_1);
  parse_ships_gpt(input_4_ships, game_data, &number_of_ships_4);
  parse_ships_gpt(input_10_ships, game_data, &number_of_ships_10);

  TEST_ASSERT_EQUAL_INT(1, number_of_ships_1);
  TEST_ASSERT_EQUAL_INT(4, number_of_ships_4);
  TEST_ASSERT_EQUAL_INT(10, number_of_ships_10);
}

void test_ship_parsing_error(void) {
  const char *input = "S 0 2 11500 0 0,";

  T_ship expected_ships[] = {{1, 9, 1100, 2513, false}};
  T_game_data game_data[NUMBER_OF_GAME_DATA];
  uint8_t number_of_ships = 0;
  parse_ships_gpt(input, game_data, &number_of_ships);

  for (int i = 0; i < number_of_ships; i++) {
    TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].team_ID,
                              game_data->ships[i].team_ID);
    TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].ship_ID,
                              game_data->ships[i].ship_ID);
    TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].pos_X,
                              game_data->ships[i].pos_X);
    TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].pos_Y,
                              game_data->ships[i].pos_Y);
    TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].broken,
                              game_data->ships[i].broken);
  }
}

void test_base_parsing(void) {
  // const char *input =
  //     "P 495 10000 20000 -1 0,P 25 3040 40 -1 1,P 11113 15410 6100 7 0,S 0 1
  //     " "10000 253 1,S 0 2 11500 0 0,S 0 3 8500 1546 0,S 0 4 13000 0 0,S 0 5
  //     " "7000 19999 1,S 0 6 14500 0 0,S 0 7 5500 21 0,S 0 8 16000 0 0,S 0 9
  //     4000 " "0 1,B 10000 0";

  // T_base expected_base[] = {
  //     {10000, 0, 0, 0, 0},
  // };
  // T_base parsed_base[BASE_NUMBER];

  // parse_base(input, parsed_base);

  // TEST_ASSERT_EQUAL_INT(expected_base[0].pos_X, parsed_base[0].pos_X);
  // TEST_ASSERT_EQUAL_INT(expected_base[0].pos_Y, parsed_base[0].pos_Y);
  // TEST_ASSERT_EQUAL_INT(expected_base[0].uint16_data,
  //                       parsed_base[0].uint16_data);
  // TEST_ASSERT_EQUAL_INT(expected_base[0].uint8_data,
  // parsed_base[0].uint8_data);
  // TEST_ASSERT_EQUAL_INT(expected_base[0].uint8_data_2,
  //                       parsed_base[0].uint8_data_2);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_test);
  RUN_TEST(test_get_angle_between_two_points);
  RUN_TEST(test_get_distance_between_two_points);
  RUN_TEST(test_explore);
  RUN_TEST(test_planet_parsing);
  RUN_TEST(test_ship_parsing);
  // RUN_TEST(test_direction);
  RUN_TEST(test_get_ship_position);
  RUN_TEST(test_get_planet_position);
  RUN_TEST(test_get_base_position);
  RUN_TEST(test_ship_parsing_numberf_of_ships);
  RUN_TEST(test_ship_parsing_error);
  // RUN_TEST(test_base_parsing);
  UNITY_END(); // stop unit testing
}