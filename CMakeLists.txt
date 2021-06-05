cmake_minimum_required(VERSION 3.19)
project(blas)

set(CMAKE_CXX_STANDARD 20)

set(BLAS_BUILD_TESTS "Build ${PROJECT_NAME}'s unit tests" ON)

set(INCLUDE_INSTALL_DIR ${PROJECT_SOURCE_DIR}/include)


if (BLAS_BUILD_TESTS)
    add_subdirectory(test)
endif (BLAS_BUILD_TESTS)

include(FetchContent)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://hub.fastgit.org/google/benchmark.git
        GIT_TAG v1.5.4
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(benchmark)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
        ${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
