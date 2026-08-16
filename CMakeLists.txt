cmake_minimum_required(VERSION 3.20)
project(chess_engine)

# C++17 gives us useful features like std::optional and structured bindings.
# Always good practice to use a modern standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically find all .cpp files inside the src/ folder.
# GLOB_RECURSE walks subdirectories too, so adding new .cpp files
# to src/board/, src/search/, etc. will be picked up automatically.
file(GLOB_RECURSE SOURCES "src/*.cpp")

# The executable is built from main.cpp plus everything found above.
add_executable(chess_engine main.cpp ${SOURCES})

# Tell the compiler to look in src/ when resolving #include paths.
# This means we can write  #include "board/board.h"  instead of
# a long relative path like  #include "../src/board/board.h".
target_include_directories(chess_engine PRIVATE src)
