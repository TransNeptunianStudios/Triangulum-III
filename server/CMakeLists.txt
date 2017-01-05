cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME triangulum-server)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(external/mongoose)

target_link_libraries(${PROJECT_NAME} mongoose)
