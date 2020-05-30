cmake_minimum_required(VERSION 3.15)

if(CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "" FORCE)
endif()

# solution name
project(Altseed)

# option
option(BUILD_TEST "build test" ON)
option(SANITIZE_ENABLED "make sanitize enabled" OFF)
option(USE_MSVC_RUNTIME_LIBRARY_DLL, "Bulid as MultithreadedDLL" ON)

# specify project type
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# specify destionation directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/DEBUG")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/DEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RELEASE")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RELEASE")

# specify msvc runtime library
if (USE_MSVC_RUNTIME_LIBRARY_DLL)
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

message(${CMAKE_MSVC_RUNTIME_LIBRARY})

# python must be required
find_package (Python3 COMPONENTS Interpreter)

if(${Python3_FOUND})
    message("Found Python version is ${Python3_VERSION}")
else()
    message(FATAL_ERROR "Python3.x is not found. Please check or install it.")
endif()

if(${Python3_Interpreter_FOUND})
    message("Found Interpreter")
else()
    message(FATAL_ERROR "Python3.x Interpreter is not found. Please check or install it.")
endif()

# detect IDE
if(CMAKE_GENERATOR MATCHES "Visual Studio|Xcode")
    message("Build with postfix")
    set(BUILD_WITH_POSTFIX ON)
else()
    set(BUILD_WITH_POSTFIX OFF)
endif()

# code encoding
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
endif()

# sanitize for Debug
if(SANITIZE_ENABLED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address")
endif()

if(BUILD_TEST)
    add_custom_target(TestData
        SOURCES TestData.dummy
    )

    add_custom_command(
        OUTPUT TestData.dummy
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/setup.py ${CMAKE_CURRENT_SOURCE_DIR}/TestData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/setup.py ${CMAKE_CURRENT_SOURCE_DIR}/TestData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
    )
endif()

# specify C# framework
set(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION v4.6.1)

# add directories
add_subdirectory(thirdparty)
add_subdirectory(core)

# specify filters
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_target_properties (ExternalProject_zlib PROPERTIES FOLDER thirdparty)
set_target_properties (ExternalProject_libpng PROPERTIES FOLDER thirdparty)
set_target_properties (ExternalProject_libzip PROPERTIES FOLDER thirdparty)
set_target_properties (ExternalProject_glfw PROPERTIES FOLDER thirdparty)
set_target_properties (ExternalProject_glslang PROPERTIES FOLDER thirdparty)
set_target_properties (ExternalProject_SPIRV-Cross PROPERTIES FOLDER thirdparty)

set_target_properties (box2d PROPERTIES FOLDER thirdparty)
set_target_properties (hidapi PROPERTIES FOLDER thirdparty)
set_target_properties (spdlog PROPERTIES FOLDER thirdparty)
set_target_properties (LLGI PROPERTIES FOLDER thirdparty)
set_target_properties (imgui PROPERTIES FOLDER thirdparty)
set_target_properties (nativefiledialog PROPERTIES FOLDER thirdparty)
set_target_properties (OpenSoundMixer PROPERTIES FOLDER thirdparty)

if(BUILD_TEST)
    set_target_properties (gtest PROPERTIES FOLDER thirdparty)
endif()

# specify a startup project
# set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CSharpCaller)

