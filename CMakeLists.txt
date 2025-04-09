# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(namesmerizer C)

# Create a static library from anyascii files
add_library(anyascii "src/anyascii.c")

# Collect all source files
file(GLOB SOURCES "*.c" "src/*.c")

# Create the executable from the source files
add_executable(namesmerizer ${SOURCES})

# Link the anyascii library to the executable
target_link_libraries(namesmerizer anyascii)
