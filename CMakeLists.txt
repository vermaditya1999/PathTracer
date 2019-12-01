cmake_minimum_required(VERSION 3.5)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG=1)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_STANDARD 14)

project(PathTracer)
set(SOURCE_FILES src/main.cpp include/debug.h include/vec3.h include/geometry/Object.h src/Ray.cpp include/geometry/Ray.h include/Color.h include/renderer/Renderer.h include/Scene.h include/Image.h src/Image.cpp src/Sphere.cpp include/geometry/Sphere.h include/material/Material.h include/camera/Camera.h include/Light.h include/Options.h include/camera/SimpleCamera.h src/SimpleCamera.cpp include/renderer/SimpleRenderer.h src/SimpleRenderer.cpp src/Camera.cpp src/Triangle.cpp include/geometry/Triangle.h src/Rectangle.cpp include/geometry/Rectangle.h include/material/Glossy.h include/material/Diffused.h include/material/Dielectric.h src/RealisticRenderer.cpp include/renderer/RealisticRenderer.h src/Object.cpp include/material/SpecularDiffused.h)
include_directories(include)
add_executable(PathTracer ${SOURCE_FILES})
