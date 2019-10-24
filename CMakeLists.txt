cmake_minimum_required(VERSION 3.12)

if(CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "" FORCE)
endif()

# solution name
project(Altseed)

# option
option(BUILD_TEST "build test" OFF)
option(SANITIZE_ENABLED "make sanitize enabled" OFF)

# specify project type
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# specify destionation directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/DEBUG")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/DEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RELEASE")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RELEASE")

if(BUILD_TEST)
    find_package(PythonInterp 3)

    add_custom_target(TestData
        SOURCES TestData.dummy
    )

    add_custom_command(
        OUTPUT TestData.dummy
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/setup.py ${CMAKE_CURRENT_SOURCE_DIR}/TestData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/setup.py ${CMAKE_CURRENT_SOURCE_DIR}/TestData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
    )
endif()

# sanitize for Debug
if(SANITIZE_ENABLED)
    set(CMAKE_CXX_FLAGS " -fsanitize=undefined,address" ${CMAKE_CXX_FLAGS})
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

set_target_properties (hidapi PROPERTIES FOLDER thirdparty)
set_target_properties (spdlog PROPERTIES FOLDER thirdparty)
set_target_properties (LLGI PROPERTIES FOLDER thirdparty)

if(BUILD_TEST)
    set_target_properties (gtest PROPERTIES FOLDER thirdparty)
endif()

# specify a startup project
# set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CSharpCaller)

