cmake_minimum_required(VERSION 3.10)
project(secretdb)

set(CMAKE_CXX_STANDARD 11)

add_library(secretdb db.c db.h utils.h utils.c)