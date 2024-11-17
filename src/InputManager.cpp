#include "InputManager.h"

volatile int32_t InputManager::encoderPosition = 0;
volatile int InputManager::lastEncA = 0;

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void IRAM_ATTR InputManager::encoderISR() {
    int encA = digitalRead(PinMap::ENCODER_A);
    int encB = digitalRead(PinMap::ENCODER_B);
    
    if (encA != lastEncA) {
        if (encB != encA) {
            encoderPosition++;
        } else {
            encoderPosition--;
        }
    }
    lastEncA = encA;
}

void InputManager::begin() {
    // Initialize buttons with pullup
    pinMode(PinMap::BUTTON, INPUT_PULLUP);
    pinMode(PinMap::BUTTON1, INPUT_PULLUP);
    pinMode(PinMap::BUTTON2, INPUT_PULLUP);
    pinMode(PinMap::BUTTON3, INPUT_PULLUP);
    pinMode(PinMap::BUTTON4, INPUT_PULLUP);
    pinMode(PinMap::BUTTON5, INPUT_PULLUP);
    pinMode(PinMap::BUTTON6, INPUT_PULLUP);
    pinMode(PinMap::BUTTON7, INPUT_PULLUP);
    pinMode(PinMap::ENCODER_BUTTON, INPUT_PULLUP);
    
    // Initialize encoder pins
    pinMode(PinMap::ENCODER_A, INPUT_PULLUP);
    pinMode(PinMap::ENCODER_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PinMap::ENCODER_A), encoderISR, CHANGE);
    
    // Initialize LEDs
    pinMode(PinMap::LED1, OUTPUT);
    pinMode(PinMap::LED2, OUTPUT);
    digitalWrite(PinMap::LED1, LOW);
    digitalWrite(PinMap::LED2, LOW);
}

void InputManager::update() {
    states.button = !digitalRead(PinMap::BUTTON);
    states.button1 = !digitalRead(PinMap::BUTTON1);
    states.button2 = !digitalRead(PinMap::BUTTON2);
    states.button3 = !digitalRead(PinMap::BUTTON3);
    states.button4 = !digitalRead(PinMap::BUTTON4);
    states.button5 = !digitalRead(PinMap::BUTTON5);
    states.button6 = !digitalRead(PinMap::BUTTON6);
    states.button7 = !digitalRead(PinMap::BUTTON7);
    states.encoderButton = !digitalRead(PinMap::ENCODER_BUTTON);
    states.encoderPosition = encoderPosition;
} 