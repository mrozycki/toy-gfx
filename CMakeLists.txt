cmake_minimum_required(VERSION 3.10)

project(Graphics CXX)

add_executable(gfx_test
    gfx/2d/canvas.cpp
    gfx/2d/shapes.cpp
    main.cpp)