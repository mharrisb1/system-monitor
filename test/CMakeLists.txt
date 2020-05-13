cmake_minimum_required(VERSION 3.13)

set(This ExampleTests)

set(Sources
        format.test.cpp)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
        gtest_main)

add_test(
        NAME ${This}
        COMMAND ${This}
)