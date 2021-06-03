cmake_minimum_required(VERSION 3.19)
project(blas)

set(CMAKE_CXX_STANDARD 20)

add_library(blas library.cpp library.h)