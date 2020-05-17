cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
include_directories(include)

list(APPEND TESTER
        test/testkit/tester.hpp)

list(APPEND BUILD_SOURCES
        src/main.cpp
        src/format.cpp
        src/linux_parser.cpp
        src/ncurses_display.cpp
        src/process.cpp
        src/processor.cpp
        src/system.cpp)

# file(GLOB SOURCES "src/*.cpp")
list(APPEND TEST1
        src/format.cpp
        test/format.test.cpp)

list(APPEND TEST2
        test/memUtilization.test.cpp)


option(TEST "Run tests only?" OFF)
message(STATUS "Run tests only = " ${TEST})

if(TEST)
    add_library(tester INTERFACE)
    target_sources(tester INTERFACE ${TESTER})

    add_executable(test1 ${TEST1})
    target_link_libraries(test1 tester)

    add_executable(test2 ${TEST2})
    target_link_libraries(test2 tester)
    enable_testing()
    add_test(
            NAME ElapsedTimeFormatter
            COMMAND $<TARGET_FILE:test1>
    )
    add_test(
            NAME MemoryUtilization
            COMMAND $<TARGET_FILE:test2>
    )
else()
    add_executable(monitor ${BUILD_SOURCES})
    target_link_libraries(monitor ${CURSES_LIBRARIES})
    # TODO: Run -Werror in CI.
    target_compile_options(monitor PRIVATE -Wall -Wextra)
endif()



