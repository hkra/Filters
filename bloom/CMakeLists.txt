cmake_minimum_required (VERSION 3.4)

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

project (BloomFilter)

# Use isntalled CityHash lib
find_library(CITYHASH CityHash)

# Executable
add_executable(BloomFilter driver.cpp)
target_link_libraries(BloomFilter libcityhash.a)

# Minimum of C++11
target_compile_features(BloomFilter PUBLIC cxx_std_11)

# Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS program_options REQUIRED) 
#1.64.0

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(BloomFilter ${Boost_LIBRARIES})
endif()