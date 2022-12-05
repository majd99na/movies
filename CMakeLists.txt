cmake_minimum_required(VERSION 3.19)
project(MoviesDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(MoviesDB main.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")