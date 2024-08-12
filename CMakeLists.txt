cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MathLib)

# Add the library
add_library(mathlib STATIC mathlib.cpp)

# Specify include directories
target_include_directories(mathlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, specify C++ standard
set_target_properties(mathlib PROPERTIES CXX_STANDARD 17)
