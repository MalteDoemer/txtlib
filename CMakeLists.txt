cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

message("hi: ${CMAKE_CROSSCOMPILING}")

project("txtlib"
        VERSION 0.1.0
        DESCRIPTION "A library for the robotics txt controller"
        LANGUAGES CXX
)

add_subdirectory(txtlib)
add_subdirectory(txtapp)