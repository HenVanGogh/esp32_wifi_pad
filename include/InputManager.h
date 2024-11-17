#pragma once

#include <Arduino.h>
#include "config.h"

class InputManager {
public:
    struct InputStates {
        bool button;
        bool button1;
        bool button2;
        bool button3;
        bool button4;
        bool button5;
        bool button6;
        bool button7;
        bool encoderButton;
        int32_t encoderPosition;
    };

    static InputManager& getInstance();
    void begin();
    void update();
    const InputStates& getStates() const { return states; }
    
private:
    InputManager() = default;
    static void IRAM_ATTR encoderISR();
    
    InputStates states{};
    static volatile int32_t encoderPosition;
    static volatile int lastEncA;
};

// Definition of the getInstance functio