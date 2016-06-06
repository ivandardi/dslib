cmake_minimum_required(VERSION 2.8)

project (dslib)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(dslib SHARED src/dslib_error.c src/dslib_graph.c src/dslib_list.c src/dslib_queue.c src/dslib_slist.c src/dslib_stack.c src/dslib_vector.c)
