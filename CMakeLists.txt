cmake_minimum_required(VERSION 3.12)
project(raytracer2)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(raytracer2 src/main.cpp src/Raytracer.cpp src/Raytracer.hpp src/Camera.cpp src/Camera.hpp src/Scene.cpp src/Scene.hpp src/objects/Object.cpp src/objects/Object.hpp src/lights/PointLight.cpp src/lights/PointLight.hpp src/objects/Sphere.cpp src/objects/Sphere.hpp src/materials/Material.cpp src/materials/Material.hpp src/objects/InfinitePlane.cpp src/objects/InfinitePlane.hpp src/objects/BoundedPlane.cpp src/objects/BoundedPlane.hpp src/materials/CheckeredMaterial.cpp src/materials/CheckeredMaterial.hpp src/objects/Triangle.cpp src/objects/Triangle.hpp)
