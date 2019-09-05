cmake_minimum_required(VERSION 3.10)

enable_language(CXX)

# set files
set(core_files
    Core.h
    Core.cpp
    BaseObject.h
    BaseObject.cpp
    Common/Int8Array.h
    Common/ResourceContainer.h
    Common/StringHelper.h
    Window/Window.h
    Window/Window.cpp
    Input/ButtonState.h
    Input/Keyboard.h
    Input/Keyboard.cpp
    Input/Mouse.h
    Input/Mouse.cpp
    IO/File.h
    IO/File.cpp
    IO/PackFile.h
    IO/PackFile.cpp
    IO/StaticFile.h
    IO/StaticFile.cpp
    IO/StreamFile.h
    IO/StreamFile.cpp
    IO/FileRoot.h
    IO/FileRoot.cpp
    IO/BaseFileReader.h
    IO/BaseFileReader.cpp
    IO/PackFileReader.h
    IO/PackFileReader.cpp
)

# specify project filters
foreach(FILE ${core_files}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
         set(GROUP "Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.c")
         set(GROUP "Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.cxx")
         set(GROUP "Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
         set(GROUP "Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.mm")
        set(GROUP "Files\\${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()


# create dll
add_library(Altseed_Core
    SHARED
    ${core_files}
)

target_link_libraries(
    Altseed_Core
    PRIVATE
    spdlog
    hidapi
    debug glfw3d
    optimized glfw3
    debug zip
    optimized zip
    debug libpng16_staticd
    optimized libpng16_static
    debug zlibstaticd
    optimized zlibstatic
    )

# to use external projects
target_include_directories(
    Altseed_Core 
    PRIVATE 
    ${THIRDPARTY_INCLUDES})

# to use external projects
target_link_directories(
    Altseed_Core
    PRIVATE
    ${THIRDPARTY_LIBRARY_DIRECTORIES})

# specify dependencies about external projects. 
# It is required to use external projects in addition of target_link_libraries
add_dependencies(
    Altseed_Core
    ExternalProject_glfw
    ExternalProject_zlib
    ExternalProject_libpng
    ExternalProject_libzip)

# export all functions to out of dll for testing
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# make c++17 enabled
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES CXX_STANDARD 17)