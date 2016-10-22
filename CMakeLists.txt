cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "dslib")
project(${PROJECT_NAME})


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
        test/main.c
        test/test_vector_int.c
        test/test_stack_int.c
)
