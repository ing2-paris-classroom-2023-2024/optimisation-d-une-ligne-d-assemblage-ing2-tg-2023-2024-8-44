cmake_minimum_required(VERSION 3.23)

project(project C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_executable(project src/main.c src/fonction.c src/graphe.c src/lectureFichier.c src/precedenceTemps.c src/Menu.c src/pileFonction.c src/reunionDesCode.c)