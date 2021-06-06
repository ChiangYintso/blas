cmake_minimum_required(VERSION 3.16)
project(libra)

set(CMAKE_CXX_STANDARD 20)

set(LIBRA_BUILD_TESTS "Build ${PROJECT_NAME}'s unit tests" ON)
set(LIBRA_BUILD_BENCHMARK "Build ${PROJECT_NAME}'s unit benchmark" ON)

set(INCLUDE_INSTALL_DIR ${PROJECT_SOURCE_DIR}/include)

add_compile_definitions(LIBRA_USE_SSE2)

include(FetchContent)

if (LIBRA_BUILD_TESTS)
    add_subdirectory(test)
endif (LIBRA_BUILD_TESTS)

set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
if (LIBRA_BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif(LIBRA_BUILD_BENCHMARK)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
        ${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
