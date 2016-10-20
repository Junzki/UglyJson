cmake_minimum_required (VERSION 2.6)

project (UglyJson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(uglyjson uglyjson.c)
add_executable(uglyjson_test test.c)
target_link_libraries(uglyjson_test uglyjson)
