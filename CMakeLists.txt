cmake_minimum_required (VERSION 2.6)

project (UglyJson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(uglyjson src/uglyjson.c)
add_library(number src/number.c)

include_directories(src/include)

add_executable(uglyjson_test tests/test.c)
add_executable(ugly_number_test tests/test_digit.c)
target_link_libraries(uglyjson_test uglyjson number)
target_link_libraries(ugly_number_test number)
