cmake_minimum_required(VERSION 3.2)
project(relex_task)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(relex_task ${SOURCE_FILES} Sensor.cpp Sensor.h Gardener.cpp Gardener.h Flowerbed.cpp Flowerbed.h WateringMachine.cpp WateringMachine.h common.h common.cpp)