#include <Arduino.h>
#include <WiFi.h>
#include "InputManager.h"
#include "WebServer.h"
#include "config.h"

void setup() {
    Serial.begin(115200);
    
    // Initialize input manager
    InputManager::getInstance().begin();
    
    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    // Initialize web server
    WebServer::getInstance().begin();
}

void loop() {
    // Update input states
    InputManager::getInstance().update();
    
    // Update LED2 based on button state
    digitalWrite(PinMap::LED2, !digitalRead(PinMap::BUTTON));
    
    // Update web server
    WebServer::getInstance().update();
}