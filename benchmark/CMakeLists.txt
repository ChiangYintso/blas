enable_testing()
include(CTest)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://hub.fastgit.org/google/benchmark.git
        GIT_TAG v1.5.4
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(benchmark)

function(add_benchmark source)
    # Create a human readable name.
    get_filename_component(libra_bench_filename ${source} NAME)
    string(REPLACE ".cpp" "" libra_bench_name ${libra_bench_filename})

    add_executable(${libra_bench_name} ${source})
    target_link_libraries(${libra_bench_name} ${PROJECT_NAME} benchmark::benchmark)

    add_test(NAME ${source} COMMAND ${libra_bench_name})
endfunction(add_benchmark source)

# Add bench executables
file(GLOB LIBRA_BENCH_SOURCES "${PROJECT_SOURCE_DIR}/benchmark/libra/*bench.cpp")
foreach (libra_bench_source ${LIBRA_BENCH_SOURCES})
    add_benchmark(${libra_bench_source})
endforeach(libra_bench_source ${LIBRA_BENCH_SOURCES})

# Build benchmark for Eigen3
find_package (Eigen3 3.3 NO_MODULE)
if (TARGET Eigen3::Eigen)
    # Add Eigen3 bench executables
    file(GLOB EIGEN_BENCH_SOURCES "${PROJECT_SOURCE_DIR}/benchmark/eigen/*bench.cpp")
    foreach(eigen_bench_source ${EIGEN_BENCH_SOURCES})
        add_benchmark(${eigen_bench_source})
    endforeach(eigen_bench_source ${EIGEN_BENCH_SOURCES})

endif (TARGET Eigen3::Eigen)