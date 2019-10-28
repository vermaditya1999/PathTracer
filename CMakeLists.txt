cmake_minimum_required(VERSION 3.12)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp)

include_directories(include)
add_executable(PathTracer ${SOURCE_FILES})