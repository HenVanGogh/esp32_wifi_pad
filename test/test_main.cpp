#include <unity.h>
#include <Arduino.h>
#include "test_input_manager.h"
#include "test_web_server.h"
// Forward declarations of test functions
// void test_input_manager_initial_state(void);
// void test_input_manager_button_states(void);
// void test_encoder_position(void);
// void test_web_server_initialization(void);
// void test_web_server_update(void);
// void test_json_format(void);

void setUp(void) {
    // Setup code before each test
}

void tearDown(void) {
    // Cleanup code after each test
}

void setup() {
    delay(2000);  // Service delay to allow board to stabilize
    UNITY_BEGIN();
    
    // Input Manager tests
    RUN_TEST(test_input_manager_initial_state);
    RUN_TEST(test_input_manager_button_states);
    RUN_TEST(test_encoder_position);
    
    // WebServer tests
    RUN_TEST(test_web_server_initialization);
    RUN_TEST(test_web_server_update);
    RUN_TEST(test_json_format);
    
    UNITY_END();
}

void loop() {
} 