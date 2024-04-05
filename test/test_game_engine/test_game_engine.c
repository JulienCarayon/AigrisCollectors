#include <constants.h>
#include <game_engine.h>
#include <unity.h>

void setUp(void) {}
void tearDown(void) {}

void test_get_angle_between_two_points(void)
{
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 10000;
  point_B.pos_Y = 10000;

  TEST_ASSERT_EQUAL_INT(get_angle_between_two_points(point_A, point_B), 349);
}

void test_get_distance_between_two_points(void)
{
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 17000;
  point_B.pos_Y = 1000;

  TEST_ASSERT_EQUAL_INT(get_distance_between_two_points(point_A, point_B),
                        15620);
}

void test_coordinate_to_point(void)
{
  T_point test_1 = coordinate_to_point(5000, 11000);

  TEST_ASSERT_EQUAL_INT(test_1.pos_X, 5000);
  TEST_ASSERT_EQUAL_INT(test_1.pos_Y, 11000);
}

void test_explore(void)
{
  char *buffer = create_buffer(BUFFER_SIZE);
  TEST_ASSERT_EQUAL_STRING(explore(7, buffer), "RADAR 7\n");
}

void test_planet_parsing(void)
{
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

  for (int i = 0; i < number_of_planets; i++)
  {
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

void test_ship_parsing(void)
{
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

  for (int i = 0; i < number_of_ships; i++)
  {
    TEST_ASSERT_EQUAL_INT(expected_ships[i].team_ID,
                          game_data->ships[i].team_ID);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].ship_ID,
                          game_data->ships[i].ship_ID);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].pos_X, game_data->ships[i].pos_X);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].pos_Y, game_data->ships[i].pos_Y);
    TEST_ASSERT_EQUAL_INT(expected_ships[i].broken, game_data->ships[i].broken);
  }
}

void test_ship_parsing_error(void)
{
  // const char *input =
  //     "P 495 10000 20000 -1 0,P 25 3040 40 -1 1,P 11113 15410 6100 7 0,S 0 1
  //     " "10000 253 1,S 0 2 11500 0 0,S 0 3 8500 1546 0,S 0 4 13000 0 0,S 0 5
  //     " "7000 19999 1,S 0 6 14500 0 0,S 0 7 5500 21 0,S 0 8 16000 0 0,S 0 9
  //     4000 " "0 1,B 10000 0";

  // T_ship expected_ships[] = {
  //     {1, 9, 1000, 2513, false}, {1, 8, 1100, 10, true},
  //     {1, 7, 850, 15146, true},  {1, 6, 1300, 10, true},
  //     {1, 10, 700, 1999, false}, {1, 4, 1450, 10, true},
  //     {1, 3, 500, 211, true},    {1, 2, 1600, 10, true},
  //     {1, 1, 400, 10, false},
  // };

  // T_ship parsed_ships[SHIPS_NUMBER];

  // parse_ships(input, parsed_ships);

  // for (int i = 0; i < SHIPS_NUMBER; i++) {
  //   TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].team_ID,
  //                             parsed_ships[i].team_ID);
  //   TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].ship_ID,
  //                             parsed_ships[i].ship_ID);
  //   TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].pos_X,
  //   parsed_ships[i].pos_X);
  //   TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].pos_Y,
  //   parsed_ships[i].pos_Y);
  //   TEST_ASSERT_NOT_EQUAL_INT(expected_ships[i].broken,
  //   parsed_ships[i].broken);
  // }
}

void test_base_parsing(void)
{
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

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_test);
  RUN_TEST(test_get_angle_between_two_points);
  RUN_TEST(test_get_distance_between_two_points);
  RUN_TEST(test_explore);
  RUN_TEST(test_planet_parsing);
  RUN_TEST(test_ship_parsing);
  // RUN_TEST(test_ship_parsing_error);
  // RUN_TEST(test_base_parsing);
  UNITY_END(); // stop unit testing
}