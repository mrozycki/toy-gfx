cmake_minimum_required(VERSION 3.10)

project(Graphics CXX)

add_executable(gfx_test
    gfx/canvas.cpp
    gfx/shapes.cpp
    main.cpp)