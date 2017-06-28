cmake_minimum_required (VERSION 3.4)

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

SET( COMPILE_FLAGS "-std=c++14" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

project (BloomFilter)

find_library(CITYHASH CityHash)

add_executable(BloomFilter driver.cpp)
target_link_libraries(BloomFilter libcityhash.a)