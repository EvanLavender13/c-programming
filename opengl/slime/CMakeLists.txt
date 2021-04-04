cmake_minimum_required(VERSION 3.10)

project(opengl C)
set(CMAKE_C_STANDARD 11)
set(CMAKE)
add_compile_options(-Wall -Wextra -pedantic)

include_directories(./)
include_directories(../)
include_directories(../include/)
include_directories(../render/)
add_executable(main main.c)
target_link_libraries(main glfw GLEW GL m spng)
