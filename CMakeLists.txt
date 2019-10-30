cmake_minimum_required(VERSION 3.10)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp include/debug.h include/vec3.h src/Object.cpp include/Object.h src/Ray.cpp include/Ray.h include/Color.h src/Renderer.cpp include/Renderer.h src/Scene.cpp include/Scene.h include/Image.h src/Image.cpp src/Circle.cpp include/Circle.h include/Material.h include/Camera.h)


include_directories(include)
add_executable(PathTracer ${SOURCE_FILES})

