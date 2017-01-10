cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME triangulum-server)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

set(SOURCE_FILES
    src/Main.cpp
    src/triangulum/Game.cpp
    src/triangulum/system/InputSystem.cpp
    src/triangulum/web/WebServer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(external/entityx)

add_subdirectory(external/mongoose)

include_directories(external/entityx external/json)

include_directories(src)

target_link_libraries(${PROJECT_NAME} entityx mongoose)
