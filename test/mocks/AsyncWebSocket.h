#pragma once
#include <IPAddress.h>
#include <functional>
#include <AsyncWebSocket.h>

// We'll only mock the methods we need, using the real class definitions
class MockWebSocket : public AsyncWebSocket {
public:
    MockWebSocket(const char* url) : AsyncWebSocket(url) {}
    
    // The actual method signature from AsyncWebSocket
    void textAll(const char* message, size_t len) {
        lastMessage = String(message);
    }
    
    // Helper method for testing
    String getLastMessage() const { return lastMessage; }
    
private:
    String lastMessage;
}; 