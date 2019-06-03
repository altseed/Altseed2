cmake_minimum_required(VERSION 3.10)

enable_language(CXX)

# set files
set(core_files
    Core.h
    Core.cpp
    BaseObject.h
    BaseObject.cpp
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
         set(GROUP "Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.c")
         set(GROUP "Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.cxx")
         set(GROUP "Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
         set(GROUP "Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.mm")
        set(GROUP "Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()


# create dll
add_library(Altseed_Core
    SHARED
    ${core_files}
)

target_link_libraries(Altseed_Core PRIVATE glfw)

# export all functions to out of dll for testing
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# make c++17 enabled
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES CXX_STANDARD 17)