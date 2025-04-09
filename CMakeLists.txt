# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(namesmerizer C)

# Create a static library from anyascii and letter_case files
add_library(anyascii
    "src/anyascii.c"
    "src/letter_case.c"    # Added file that likely contains convert_to_uppercase
)

# Collect all source files for namesmerizer
file(GLOB MAIN_SOURCES "*.c" "src/*.c")

# Exclude test.c from MAIN_SOURCES
list(REMOVE_ITEM MAIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test.c")

# Create the namesmerizer executable
add_executable(namesmerizer ${MAIN_SOURCES})

# Link the anyascii library to namesmerizer
target_link_libraries(namesmerizer anyascii)

# Create a separate executable for tests
add_executable(test_runner test.c)

# Link the anyascii library to test_runner too
target_link_libraries(test_runner anyascii)
