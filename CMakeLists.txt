cmake_minimum_required(VERSION 3.10)

project(Graphics)
set(CMAKE_CXX_RELEASE_FLAGS -O3)
set(CMAKE_CXX_DEBUG_FLAGS -Og -g)

add_executable(gfx_test
    gfx/2d/canvas.cpp
    gfx/2d/shapes.cpp
    gfx/3d/object.cpp
    main.cpp)
set_property(TARGET gfx_test PROPERTY CXX_STANDARD 17)

target_include_directories(gfx_test PRIVATE .)