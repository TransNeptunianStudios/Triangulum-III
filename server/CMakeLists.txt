cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME triangulum-server)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++14")

set(SOURCE_FILES
    src/Main.cpp
    src/triangulum/Game.cpp
    src/triangulum/component/PlayerInfo.cpp
    src/triangulum/message/Message.h
    src/triangulum/message/MessageManager.cpp
    src/triangulum/message/MessageManager.h
    src/triangulum/message/MessageMap.cpp
    src/triangulum/message/MessageMap.h
    src/triangulum/system/ConnectionSystem.cpp
    src/triangulum/system/InputSystem.cpp
    src/triangulum/web/WebServer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(external/entityx)

add_subdirectory(external/mongoose)

include_directories(external/entityx external/json external/moodycamel)

include_directories(src)

target_link_libraries(${PROJECT_NAME} entityx mongoose pthread)
