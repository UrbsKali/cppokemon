cmake_minimum_required(VERSION 3.16)
project(cppokemon LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Directories
set(SRC_DIR src)
file(GLOB_RECURSE LIB_DIRS libs/*/src)
file(GLOB_RECURSE INCLUDE_DIRS libs/*/includes)
set(DATA_DIR data)
set(BUILD_DIR ${CMAKE_BINARY_DIR})
set(OUT_DIR ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB LIB_FILES ${LIB_DIRS}/*.cpp)

# Include directories
include_directories(${INCLUDE_DIRS})

# Output binary
set(TARGET cppokemon)

# Add executable
add_executable(${TARGET} ${SRC_FILES} ${LIB_FILES})

# Set output directory
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})