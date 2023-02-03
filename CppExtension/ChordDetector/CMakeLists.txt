cmake_minimum_required(VERSION 3.24)

project(detector-lib VERSION 1.0 LANGUAGES C CXX)

file(GLOB_RECURSE fft_source "libs/*.h" "libs/*.hh" "libs/*.c")
file(GLOB_RECURSE detector_source "src/*.*")
file(GLOB_RECURSE test_source "tests/test.cpp" "tests/Test_Signals.cpp")

add_library(${PROJECT_NAME} ${detector_source} ${fft_source})

target_include_directories(${PROJECT_NAME} PUBLIC "libs/kiss_fft130" "libs/FFTW/include")

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Configure tests
    find_package(Catch2 3 REQUIRED)
    # These tests can use the Catch2-provided main
    add_executable(tests ${test_source})
    target_include_directories(tests PUBLIC "libs/kiss_fft130" "src")
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})
endif()