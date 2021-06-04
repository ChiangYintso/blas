cmake_minimum_required(VERSION 3.19)
project(blas)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_INSTALL_DIR ${PROJECT_SOURCE_DIR}/include)

include(CMakePackageConfigHelpers)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
        ${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
