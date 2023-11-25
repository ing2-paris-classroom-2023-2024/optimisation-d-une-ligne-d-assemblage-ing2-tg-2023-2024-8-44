cmake_minimum_required(VERSION 3.23)

project(project C)

set(CMAKE_C_STANDARD 17)

add_executable(project main.c src/fonction.c include/fonction.h src/test.c)