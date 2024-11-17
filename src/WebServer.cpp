#include "WebServer.h"
#include <ArduinoJson.h>

WebServer::WebServer() 
    : server(SERVER_PORT)
    , ws(WS_PATH)
    , lastUpdate(0) {
}

WebServer& WebServer::getInstance() {
    static WebServer instance;
    return instance;
}

void WebServer::onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, 
                         AwsEventType type, void* arg, uint8_t* data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.printf("WebSocket client #%u connected from %s\n", 
                     client->id(), client->remoteIP().toString().c_str());
    }
}

void WebServer::setupRoutes() {
    // Serve the HTML interface
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>ESP32 Button Status</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
        .status { font-size: 24px; margin-top: 20px; }
        .status span { font-weight: bold; color: green; }
    </style>
    <script>
        var ws;
        function start() {
            ws = new WebSocket('ws://' + window.location.host + '/ws');
            ws.onmessage = function(event) {
                var data = JSON.parse(event.data);
                document.getElementById('button_status').innerHTML = data.button ? 'pressed' : 'not pressed';
                document.getElementById('button1_status').innerHTML = data.button1 ? 'pressed' : 'not pressed';
                document.getElementById('button2_status').innerHTML = data.button2 ? 'pressed' : 'not pressed';
                document.getElementById('button3_status').innerHTML = data.button3 ? 'pressed' : 'not pressed';
                document.getElementById('button4_status').innerHTML = data.button4 ? 'pressed' : 'not pressed';
                document.getElementById('button5_status').innerHTML = data.button5 ? 'pressed' : 'not pressed';
                document.getElementById('button6_status').innerHTML = data.button6 ? 'pressed' : 'not pressed';
                document.getElementById('button7_status').innerHTML = data.button7 ? 'pressed' : 'not pressed';
                document.getElementById('encoder_button_status').innerHTML = data.encoder_button ? 'pressed' : 'not pressed';
                document.getElementById('encoder_position').innerHTML = data.encoder_position;
            };
        }
        window.onload = start;
    </script>
</head>
<body>
    <h1>ESP32 Button Status</h1>
    <div class='status'>Button is <span id='button_status'>unknown</span></div>
    <div class='status'>Button1 is <span id='button1_status'>unknown</span></div>
    <div class='status'>Button2 is <span id='button2_status'>unknown</span></div>
    <div class='status'>Button3 is <span id='button3_status'>unknown</span></div>
    <div class='status'>Button4 is <span id='button4_status'>unknown</span></div>
    <div class='status'>Button5 is <span id='button5_status'>unknown</span></div>
    <div class='status'>Button6 is <span id='button6_status'>unknown</span></div>
    <div class='status'>Button7 is <span id='button7_status'>unknown</span></div>
    <div class='status'>Encoder Button is <span id='encoder_button_status'>unknown</span></div>
    <div class='status'>Encoder Position is <span id='encoder_position'>unknown</span></div>
</body>
</html>
        )";
        request->send(200, "text/html", html);
    });

    // JSON API endpoint
    server.on("/api/inputs", HTTP_GET, [](AsyncWebServerRequest *request) {
        auto& inputManager = InputManager::getInstance();
        const auto& states = inputManager.getStates();
        
        StaticJsonDocument<256> doc;
        doc["button"] = states.button;
        doc["button1"] = states.button1;
        doc["button2"] = states.button2;
        doc["button3"] = states.button3;
        doc["button4"] = states.button4;
        doc["button5"] = states.button5;
        doc["button6"] = states.button6;
        doc["button7"] = states.button7;
        doc["encoder_button"] = states.encoderButton;
        doc["encoder_position"] = states.encoderPosition;

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    // WebSocket setup
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
}

void WebServer::begin() {
    setupRoutes();
    server.begin();
}

void WebServer::broadcastInputStates() {
    auto& inputManager = InputManager::getInstance();
    const auto& states = inputManager.getStates();
    
    StaticJsonDocument<256> doc;
    doc["button"] = states.button;
    doc["button1"] = states.button1;
    doc["button2"] = states.button2;
    doc["button3"] = states.button3;
    doc["button4"] = states.button4;
    doc["button5"] = states.button5;
    doc["button6"] = states.button6;
    doc["button7"] = states.button7;
    doc["encoder_button"] = states.encoderButton;
    doc["encoder_position"] = states.encoderPosition;

    String jsonString;
    serializeJson(doc, jsonString);
    ws.textAll(jsonString);
}

void WebServer::update() {
    if (millis() - lastUpdate >= UPDATE_INTERVAL_MS) {
        broadcastInputStates();
        lastUpdate = millis();
    }
    ws.cleanupClients();
}

#ifdef UNIT_TEST
String WebServer::createStateJson() const {
    auto& inputManager = InputManager::getInstance();
    const auto& states = inputManager.getStates();
    
    StaticJsonDocument<256> doc;
    doc["button"] = states.button;
    doc["button1"] = states.button1;
    doc["button2"] = states.button2;
    doc["button3"] = states.button3;
    doc["button4"] = states.button4;
    doc["button5"] = states.button5;
    doc["button6"] = states.button6;
    doc["button7"] = states.button7;
    doc["encoder_button"] = states.encoderButton;
    doc["encoder_position"] = states.encoderPosition;

    String output;
    serializeJson(doc, output);
    return output;
}
#endif 