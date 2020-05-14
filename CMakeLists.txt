cmake_minimum_required(VERSION 3.13)
project(monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

# uncomment for build
#add_executable(monitor ${SOURCES})
#target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
#target_compile_options(monitor PRIVATE -Wall -Wextra)

# uncomment for test
add_executable(cpp_test test/format.test.cpp src/format.cpp)
enable_testing()
add_test(
        NAME cpp_test
        COMMAND $<TARGET_FILE:cpp_test>
)



