#pragma once

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "InputManager.h"

class WebServer {
public:
    static WebServer& getInstance();
    void begin();
    void update();
    
    #ifdef UNIT_TEST
    String createStateJson() const;
    AsyncWebSocket& getWebSocket() { return ws; }
    #endif
    
private:
    WebServer();
    void setupRoutes();
    void broadcastInputStates();
    static void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, 
                         AwsEventType type, void* arg, uint8_t* data, size_t len);
    
    AsyncWebServer server;
    AsyncWebSocket ws;
    unsigned long lastUpdate;
}; 