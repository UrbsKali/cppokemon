cmake_minimum_required(VERSION 3.16)
project(cppokemon LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Directories
set(SRC_DIR src)
set(LIBS_DIR libs)
set(DATA_DIR data)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Source files
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE LIB_FILES ${LIBS_DIR}/*/src/*.cpp)

# Include directories
include_directories(
    ${LIBS_DIR}/pokemons/includes
    ${LIBS_DIR}/utils/includes
    ${LIBS_DIR}/game/includes
)

# Output binary
set(TARGET cppokemon)

# Add executable
add_executable(${TARGET} ${SRC_FILES} ${LIB_FILES})