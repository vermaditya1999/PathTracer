cmake_minimum_required(VERSION 3.10)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp include/debug.h include/vec3.h include/Object.h src/Ray.cpp include/Ray.h include/Color.h include/Renderer.h include/Scene.h include/Image.h src/Image.cpp src/Sphere.cpp include/Sphere.h include/Material.h include/Camera.h include/Light.h include/Options.h include/SimpleCamera.h src/SimpleCamera.cpp include/SimpleRenderer.h src/SimpleRenderer.cpp src/Camera.cpp include/Triangle.cpp include/Triangle.h src/Rectangle.cpp include/Rectangle.h include/Shiny.h include/Glossy.h include/Diffused.h include/Dielectric.h)

include_directories(include)
add_executable(PathTracer ${SOURCE_FILES})

