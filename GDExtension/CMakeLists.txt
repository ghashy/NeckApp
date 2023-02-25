# Toolchain file should be provided
cmake_minimum_required(VERSION 3.26.0)

# User-settings
set(androidcpu "arm64-v8a") # armeabi-v7a, arm64-v8a, x86, x86_64
set(androidplatform "23") # 23 is android 6.0
set(iosplatform "OS64") # OS or OS64

# General variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
# Macos variables
set(CMAKE_OSX_ARCHITECTURES "arm64" "x86_64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12")
# Ios variables
set(PLATFORM ${iosplatform})
set(ENABLE_BITCODE OFF)
# Android variables
set(ANDROID_ABI ${androidcpu})
set(ANDROID_PLATFORM ${androidplatform})
set(ANDROID_STL "c++_shared")

# All variables should be defined before project() function
project(lib_neck VERSION 1.1 LANGUAGES CXX C)

# Define host
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(host "macos")
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(host "ios")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(host "android")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(host "windows")
endif()

# Define build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(buildtype "debug")
else()
    set(buildtype "release")
endif()

# Define cpu-name
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(cpuname "universal")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(cpuname ${ANDROID_ABI})
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(cpuname ${ARCHS})
endif()

# Define godot bindings filename
set(godot_obj libgodot-cpp.${host}.template_${buildtype}.${cpuname}.a)
# Define godot bindings
add_library(godot_lib STATIC OBJECT IMPORTED)
set_target_properties(godot_lib PROPERTIES
    IMPORTED_OBJECTS "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/bin/${godot_obj}")

# Add detector-lib library
add_subdirectory("ChordDetector")
set(detector_include "ChordDetector/src")

# Define our sources
file(GLOB sources "source/src/*.cpp")
set(include "source/include")
# Define our library
add_library(${PROJECT_NAME} SHARED ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    MACOSX_FRAMEWORK_IDENTIFIER "com.ghashy.necklib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/products"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/products"
    OUTPUT_NAME ${PROJECT_NAME}.${host}.${buildtype}.${cpuname}
    PREFIX ""
    )
target_include_directories(${PROJECT_NAME} PUBLIC  "godot-cpp/include"
                                                   "godot-cpp/gen/include"
                                                   "godot-cpp/gdextension"
                                           PRIVATE ${include}
                                                   ${detector_include}
                                           )
target_link_libraries(${PROJECT_NAME} PUBLIC godot_lib PRIVATE detector-lib)