cmake_minimum_required(VERSION 3.15)
project(Conversione_base_to_base C)

set(CMAKE_C_STANDARD 99)

add_executable(Conversione_base_to_base main.c)
target_link_libraries(Conversione_base_to_base m)