#include <unity.h>
#include "InputManager.h"

void test_input_manager_initial_state() {
    // Get instance of InputManager
    InputManager& input_manager = InputManager::getInstance();
    
    // Test initial state
    const InputManager::InputStates& states = input_manager.getStates();
    
    TEST_ASSERT_FALSE(states.button);
    TEST_ASSERT_FALSE(states.button1);
    TEST_ASSERT_FALSE(states.button2);
    TEST_ASSERT_FALSE(states.button3);
    TEST_ASSERT_FALSE(states.button4);
    TEST_ASSERT_FALSE(states.button5);
    TEST_ASSERT_FALSE(states.button6);
    TEST_ASSERT_FALSE(states.button7);
    TEST_ASSERT_FALSE(states.encoderButton);
    TEST_ASSERT_EQUAL(0, states.encoderPosition);
}

void test_input_manager_button_states() {
    InputManager& input_manager = InputManager::getInstance();
    
    // Simulate button press by directly writing to the pin
    digitalWrite(PinMap::BUTTON, LOW);  // Active LOW
    input_manager.update();
    
    const InputManager::InputStates& states = input_manager.getStates();
    TEST_ASSERT_TRUE(states.button);
    
    // Reset button state
    digitalWrite(PinMap::BUTTON, HIGH);
    input_manager.update();
    TEST_ASSERT_FALSE(states.button);
}

void test_encoder_position() {
    InputManager& input_manager = InputManager::getInstance();
    const InputManager::InputStates& initial_states = input_manager.getStates();
    int32_t initial_position = initial_states.encoderPosition;
    
    // Simulate encoder rotation clockwise
    digitalWrite(PinMap::ENCODER_A, HIGH);
    delayMicroseconds(1000);
    digitalWrite(PinMap::ENCODER_B, HIGH);
    delayMicroseconds(1000);
    digitalWrite(PinMap::ENCODER_A, LOW);
    delayMicroseconds(1000);
    digitalWrite(PinMap::ENCODER_B, LOW);
    
    input_manager.update();
    const InputManager::InputStates& final_states = input_manager.getStates();
    
    TEST_ASSERT_EQUAL(initial_position + 1, final_states.encoderPosition);
} 