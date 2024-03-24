#include <constants.h>
#include <game_engine.h>
#include <unity.h>

void setUp(void) {}
void tearDown(void) {}

void test_1equal1(void) { TEST_ASSERT_EQUAL(1, 1); }

void test_get_angle_between_two_points(void) {
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 10000;
  point_B.pos_Y = 10000;

  TEST_ASSERT_EQUAL(get_angle_between_two_points(point_A, point_B), 349);
}

void test_get_distance_between_two_points(void) {
  T_point point_A;
  point_A.pos_X = 5000;
  point_A.pos_Y = 11000;

  T_point point_B;
  point_B.pos_X = 17000;
  point_B.pos_Y = 1000;

  TEST_ASSERT_EQUAL(get_distance_between_two_points(point_A, point_B), 15620);
}

void test_explore(void) {
  char *buffer = create_buffer(BUFFER_SIZE);
  TEST_ASSERT_EQUAL_STRING(explore(7, buffer), "RADAR 7\n");
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_1equal1);
  RUN_TEST(test_get_angle_between_two_points);
  RUN_TEST(test_get_distance_between_two_points);
  RUN_TEST(test_explore);
  UNITY_END(); // stop unit testing
}