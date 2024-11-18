# ESP32 Controller Project

A web-based interface for monitoring and controlling ESP32 I/O states, featuring real-time updates via WebSocket communication.

## Features

- Real-time button state monitoring
- Rotary encoder support with position tracking
- LED status indicators
- Web interface with live updates
- JSON API endpoint
- WebSocket support for real-time data streaming
- Comprehensive unit testing framework
  
![image](https://github.com/user-attachments/assets/b6ffc261-ab85-4fbb-a5c7-49a7864b63ff)

## Hardware Requirements

- ESP32-S2-SAOLA-1 board
- Push buttons (x8)
- Rotary encoder with push button
- LEDs (x2)
- Pull-up resistors as needed

## Pin Configuration

- Buttons: GPIO 0-3, 38, 33, 21, 11
- Encoder: GPIO 4 (A), 5 (B), 7 (Button)
- LEDs: GPIO 15, 6

## Software Dependencies

- Arduino framework
- ESPAsyncWebServer-esphome (v3.1.0+)
- AsyncTCP (v1.1.1+)
- ArduinoJson (v6.19.4+)
- Unity (for testing)

## Setup

1. Clone the repository
2. Copy `credentials.h.template` to `credentials.h` and update WiFi settings
3. Install dependencies through PlatformIO:
```bash
pio lib install
```

## Building and Flashing

Using PlatformIO:
```bash
# Build
pio run

# Upload
pio run --target upload

# Monitor
pio device monitor
```

## Running Tests

```bash
# Run all tests
pio test

# Run specific test
pio test -f test_input_manager
```

## Project Structure

- `src/` - Main source files
- `include/` - Header files
- `test/` - Unit tests
- `platformio.ini` - Project configuration

## Web Interface

Access the web interface at `http://<esp32-ip-address>`. Features include:
- Real-time button state display
- Encoder position monitoring
- LED state indicators

## API Endpoints

- `/api/inputs` - GET: Returns JSON of all input states
- `/ws` - WebSocket endpoint for real-time updates

## Contributing

1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## License

This project is released under the MIT License.
