#pragma once

#include "credentials.h"

// GPIO Definitions
namespace PinMap {
    constexpr uint8_t BUTTON = 0;     // GPIO0 for button
    constexpr uint8_t BUTTON1 = 1;    // GPIO pin for button1
    constexpr uint8_t BUTTON2 = 2;    // GPIO pin for button2
    constexpr uint8_t BUTTON3 = 3;    // GPIO pin for button3
    constexpr uint8_t BUTTON4 = 38;   // GPIO pin for button4
    constexpr uint8_t BUTTON5 = 33;   // GPIO pin for button5
    constexpr uint8_t BUTTON6 = 21;   // GPIO pin for button6
    constexpr uint8_t BUTTON7 = 11;   // GPIO pin for button7
    constexpr uint8_t ENCODER_BUTTON = 7;  // GPIO pin for encoder button
    constexpr uint8_t ENCODER_A = 4;   // GPIO pin for encoder A
    constexpr uint8_t ENCODER_B = 5;   // GPIO pin for encoder B
    constexpr uint8_t LED1 = 15;      // GPIO15 for LED1
    constexpr uint8_t LED2 = 6;       // GPIO6 for LED2
}

// Web server configuration
constexpr uint16_t SERVER_PORT = 80;
constexpr const char* WS_PATH = "/ws";
constexpr unsigned long UPDATE_INTERVAL_MS = 200; 