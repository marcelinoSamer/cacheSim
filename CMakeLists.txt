cmake_minimum_required(VERSION 3.29)
project(cacheSim)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cacheSim
    cache_cpp.cpp
    cache_h.h
    main.cpp)
