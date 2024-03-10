/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

// #include <main.h>
#include <unity.h>


void setUp(void) {
}
void tearDown(void) {
}

void test_1equal1(void) {
    TEST_ASSERT_EQUAL(1, 1);
}
void test_1equal2(void) {
    TEST_ASSERT_EQUAL(1, 2);
}

int main() {

    
    UNITY_BEGIN();
    RUN_TEST(test_1equal1);
    RUN_TEST(test_1equal2);
 

    UNITY_END(); // stop unit testing

}

