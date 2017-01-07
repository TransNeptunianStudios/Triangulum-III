cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME triangulum-server)

project(${PROJECT_NAME} C)

set(CMAKE_C_FLAGS "-g -Wall")

set(SOURCE_FILES src/main.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(external/mongoose)

add_subdirectory(external/parson)

target_link_libraries(${PROJECT_NAME} mongoose parson)
