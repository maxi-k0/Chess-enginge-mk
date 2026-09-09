cmake_minimum_required(VERSION 3.20)
project(chess_engine)

# C++17 gives us useful features like std::optional and structured bindings.
# Always good practice to use a modern standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#copied from GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
# Automatically find all .cpp files inside the src/ folder.
# GLOB_RECURSE walks subdirectories too, so adding new .cpp files
# to src/board/, src/search/, etc. will be picked up automatically.
file(GLOB_RECURSE SOURCES "src/*.cpp")


# The executable is built from main.cpp plus everything found above.
add_executable(chess_engine main.cpp ${SOURCES}
        src/bitboard_utils.h
        src/moveGeneration/move.h
        src/moveGeneration/attackTables.h
        src/moveGeneration/slidingAttacks.cpp
        src/moveGeneration/slidingAttacks.h
        src/moveGeneration/moveGen.cpp
        src/moveGeneration/moveGen.h
        src/board/UndoInfo.h
)
target_include_directories(chess_engine PRIVATE src)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")


add_executable(chess_engine_tests ${TEST_SOURCES} ${SOURCES}
)
target_include_directories(chess_engine_tests PRIVATE src)
target_link_libraries(chess_engine_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(chess_engine_tests)