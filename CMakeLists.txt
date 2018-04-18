cmake_minimum_required(VERSION 3.10)
project(secretdb)

set(CMAKE_CXX_STANDARD 11)

add_library(secretdb src/db.c src/db.h src/utils.h src/utils.c src/type.h)