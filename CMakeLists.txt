cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(PriorityQueue LANGUAGES CXX C)

file(GLOB_RECURSE SOURCE ./src/*.cpp)
set(HEADER ./src/ CACHE STRING "Include folder path")

add_executable(${PROJECT_NAME} ${SOURCE})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER})