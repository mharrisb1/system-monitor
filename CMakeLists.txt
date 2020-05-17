cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

option(TEST "Run tests only? (No build)" OFF)

if(TEST)
    add_executable(elapsed_time_formatter test/format.test.cpp src/format.cpp)
    enable_testing()
    add_test(
            NAME elapsed_time_formatter
            COMMAND $<TARGET_FILE:elapsed_time_formatter>
    )
else()
    add_executable(monitor ${SOURCES})
    target_link_libraries(monitor ${CURSES_LIBRARIES})
    # TODO: Run -Werror in CI.
    target_compile_options(monitor PRIVATE -Wall -Wextra)
endif()



