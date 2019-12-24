cmake_minimum_required(VERSION 3.15)
project(Es__2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Es__2 equipArray.h gdr.c inv.h invArray.h pg.h pgList.h inv.c invArray.c pg.c equipArray.c pgList.c)