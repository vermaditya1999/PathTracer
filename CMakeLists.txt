cmake_minimum_required(VERSION 3.10)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp include/vec3.h include/debug.h)

include_directories(include)
add_executable(PathTracer ${SOURCE_FILES})

