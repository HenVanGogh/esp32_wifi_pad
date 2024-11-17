cmake_minimum_required(VERSION 3.16.0)

# Include the ESP-IDF components
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp_controller)

# Add source files
set(SOURCES
    src/main.cpp
    src/InputManager.cpp
    src/WebServer.cpp
)

# Add header files
set(INCLUDES
    include
)

# Create the executable
idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES driver esp_wifi esp_http_server freertos nvs_flash
) 