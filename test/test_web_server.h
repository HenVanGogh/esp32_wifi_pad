#pragma once
#include <unity.h>
#include <ArduinoJson.h>
#include "WebServer.h"
#include "mocks/AsyncWebSocket.h"

String createJsonState(const InputManager::InputStates& states);
void test_web_server_initialization(void);
void test_web_server_update(void);
void test_json_format(void); 