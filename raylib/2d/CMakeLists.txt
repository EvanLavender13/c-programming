cmake_minimum_required(VERSION 3.10)

project(dunno C)
set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic)

include_directories(/usr/local/include/)
include_directories(./)
include_directories(../)
link_directories(/usr/local/lib/)

add_executable(2d main2d.c)
target_link_libraries(2d raylib GL m pthread dl rt X11 g)
