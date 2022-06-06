cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall)

# socketpp library
add_subdirectory(socketpp)

# examples
add_subdirectory(examples)
