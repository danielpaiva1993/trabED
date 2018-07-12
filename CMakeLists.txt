cmake_minimum_required(VERSION 3.10)
project(B___indexing C)

set(CMAKE_C_STANDARD 99)

add_executable(B___indexing main.c B+Tree.c B+Tree.h DataBasys.c DataBasys.h)