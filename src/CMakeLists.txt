cmake_minimum_required (VERSION 2.6)
project (NeuralNetwork)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++0x -funroll-loops -march=native" )
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -s")
set(CMAKE_VERBOSE_MAKEFILE off)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")


add_executable(simulator simulator.cpp)
add_executable(splitter splitter.cpp)

target_link_libraries(simulator boost_program_options)
target_link_libraries(splitter boost_program_options)
