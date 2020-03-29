cmake_minimum_required(VERSION 3.15)
project(raytracer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(raytracer
        camera.h
        hittable.h
        hittable_list.cpp
        hittable_list.hpp
        light.cpp
        light.h
        main.cpp
        surface.cpp
        surface.h
        parser.cpp
        parser.h
        ray.h
        sphere.cpp
        sphere.h
        tracer.cpp
        tracer.h
        utils.h
        vec3.h)
