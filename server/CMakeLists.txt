cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME triangulum-server)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++14")

set(SOURCE_FILES
    src/Main.cpp
    src/triangulum/EntityFactory.cpp
    src/triangulum/EntityFactory.h
    src/triangulum/Game.cpp
    src/triangulum/Game.h
    src/triangulum/SystemEvents.h
    src/triangulum/component/Bullet.cpp
    src/triangulum/component/Bullet.h
    src/triangulum/component/ClientInfo.cpp
    src/triangulum/component/ClientInfo.h
    src/triangulum/component/Graphics.cpp
    src/triangulum/component/Graphics.h   
    src/triangulum/component/DynamicBody.cpp
    src/triangulum/component/DynamicBody.h
    src/triangulum/component/Weapon.cpp
    src/triangulum/component/Weapon.h
    src/triangulum/component/Input.cpp
    src/triangulum/component/Input.h
    src/triangulum/component/Score.cpp
    src/triangulum/component/Score.h    
    src/triangulum/network/Connection.cpp
    src/triangulum/network/Connection.h
    src/triangulum/network/ConnectionManager.cpp
    src/triangulum/network/ConnectionManager.h
    src/triangulum/network/IConnection.h
    src/triangulum/network/IConnectionManager.h
    src/triangulum/network/Server.cpp
    src/triangulum/network/Server.h
    src/triangulum/system/ConnectionSystem.cpp
    src/triangulum/system/ConnectionSystem.h
    src/triangulum/system/ControlSystem.cpp
    src/triangulum/system/ControlSystem.h
    src/triangulum/system/OutputSystem.cpp
    src/triangulum/system/OutputSystem.h    
    src/triangulum/system/SimulationSystem.cpp
    src/triangulum/system/SimulationSystem.h    
    src/triangulum/system/WeaponSystem.cpp
    src/triangulum/system/WeaponSystem.h
    src/triangulum/system/ForceSystem.cpp
    src/triangulum/system/ForceSystem.h
    src/triangulum/system/ScoreSystem.cpp
    src/triangulum/system/ScoreSystem.h    
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(external/Box2D/Box2D)
add_subdirectory(external/entityx)
add_subdirectory(external/mongoose)

include_directories(external/Box2D/Box2D external/entityx external/json)

include_directories(src)

target_link_libraries(${PROJECT_NAME} Box2D entityx mongoose pthread)
