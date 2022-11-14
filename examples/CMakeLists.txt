cmake_minimum_required(VERSION 3.10)

project(sodl_examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

include_directories(../include)
include_directories(.)

# Load function example
add_executable(load_function load_function/app.cpp)

add_library(cat SHARED load_function/plugin_cat.cpp)
add_library(dog SHARED load_function/plugin_dog.cpp)
add_library(robot SHARED load_function/plugin_robot.cpp)

# Load class example
add_executable(load_class load_class/app.cpp)

add_library(class_cat SHARED load_class/plugin_cat.cpp)
add_library(class_dog SHARED load_class/plugin_dog.cpp)
add_library(class_robot SHARED load_class/plugin_robot.cpp)