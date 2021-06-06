enable_testing()
include(CTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://hub.fastgit.org/google/googletest.git
        GIT_TAG release-1.10.0
        GIT_SHALLOW TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(install_gtest OFF)
set(install_gmock OFF)

FetchContent_MakeAvailable(googletest)

# Add test executables
file(GLOB LIBRA_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*test.cpp")

foreach (libra_test_source ${LIBRA_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(libra_test_filename ${libra_test_source} NAME)
    string(REPLACE ".cpp" "" libra_test_name ${libra_test_filename})
    
    add_executable(${libra_test_name} ${libra_test_source})
    target_link_libraries(${libra_test_name} ${PROJECT_NAME} gtest_main)

    add_test(NAME ${libra_test_name} COMMAND ${libra_test_name})
endforeach (libra_test_source ${LIBRA_TEST_SOURCES})