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
    Common/Resource.h
    Common/Resources.h
    Common/Resources.cpp
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
	Graphics/Graphics.h
	Graphics/Graphics.cpp
	Graphics/Sprite.h
	Graphics/Sprite.cpp
	Graphics/Texture2D.h
    Graphics/Texture2D.cpp
    Math/MathTemplate.h
    Math/Matrix33F.cpp
    Math/Matrix33F.h
    Math/Matrix33I.cpp
    Math/Matrix33I.h
    Math/Matrix44F.cpp
    Math/Matrix44F.h
    Math/Matrix44I.cpp
    Math/Matrix44I.h
    Math/RectF.cpp
    Math/RectF.h
    Math/RectI.cpp
    Math/RectI.h
    Math/Vector2DF.cpp
    Math/Vector2DF.h
    Math/Vector2DI.cpp
    Math/Vector2DI.h
    Math/Vector3DF.cpp
    Math/Vector3DF.h
    Math/Vector3DI.cpp
    Math/Vector3DI.h
    Math/Vector4DF.cpp
    Math/Vector4DF.h
    Math/Vector4DI.cpp
    Math/Vector4DI.h
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
	LLGI
    debug glfw3d
    optimized glfw3
    debug zip
    optimized zip
    )

if (MSVC OR APPLE)

    target_link_libraries(
        Altseed_Core
        PRIVATE
        debug libpng16_staticd
        optimized libpng16_static
        debug zlibstaticd
        optimized zlibstatic
        )

else()

    find_package(X11 REQUIRED)
    target_link_libraries(Altseed_Core PRIVATE ${X11_LIBRARIES})

    target_link_libraries(
        Altseed_Core
        PRIVATE
        png16
        z
        stdc++fs
        ssl
        crypto
        )

endif()

if(MSVC)

else()
	find_package(Threads REQUIRED)
	target_link_libraries(Altseed_Core PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()

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