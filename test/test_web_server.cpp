#include <unity.h>
#include <ArduinoJson.h>
#include "WebServer.h"
#include "mocks/AsyncWebSocket.h"

// Helper function to create JSON state
String createJsonState(const InputManager::InputStates& states) {
    StaticJsonDocument<256> doc;
    doc["button"] = states.button;
    doc["button1"] = states.button1;
    doc["button2"] = states.button2;
    
    String output;
    serializeJson(doc, output);
    return output;
}

void test_web_server_initialization() {
    WebServer& server = WebServer::getInstance();
    server.begin();
    TEST_PASS();
}

void test_web_server_update() {
    WebServer& server = WebServer::getInstance();
    server.update();
    delay(UPDATE_INTERVAL_MS + 10);
    server.update();
    TEST_PASS();
}

void test_json_format() {
    // Set up input manager
    InputManager& input_manager = InputManager::getInstance();
    input_manager.begin();
    
    // Set known button states
    digitalWrite(PinMap::BUTTON, LOW);
    digitalWrite(PinMap::BUTTON1, LOW);
    input_manager.update();
    
    const auto& states = input_manager.getStates();
    String jsonString = createJsonState(states);
    
    // Verify JSON format
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    
    // Check if parsing was successful
    TEST_ASSERT_TRUE(error.code() == DeserializationError::Ok);
    
    // Check the JSON values
    bool buttonState = doc["button"].as<bool>();
    bool button1State = doc["button1"].as<bool>();
    bool button2State = doc["button2"].as<bool>();
    
    TEST_ASSERT_TRUE(buttonState);
    TEST_ASSERT_TRUE(button1State);
    TEST_ASSERT_FALSE(button2State);
} 