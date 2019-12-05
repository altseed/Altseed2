
enable_language(CXX)

# set files
set(core_test_files
    BaseObject.cpp
    Core.cpp
    Window.cpp
    File.cpp
    Graphics.cpp
    Texture2D.cpp
    Font.cpp
    ShaderCompiler.cpp
)

# specify project filters
foreach(FILE ${core_test_files}) 
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
add_executable(Altseed_Core_Test
    ${core_test_files}
)

target_include_directories(
    Altseed_Core_Test 
    PRIVATE
    ../src)

target_link_libraries(
    Altseed_Core_Test
    PRIVATE
    Altseed_Core
    gtest)



if (MSVC)

target_link_libraries(
    Altseed_Core_Test
    PRIVATE
    debug glfw3d
    optimized glfw3)

elseif(APPLE)

target_link_libraries(
    Altseed_Core_Test
    PRIVATE
    debug glfw3d
    optimized glfw3)

else()

target_link_libraries(
    Altseed_Core_Test
    PRIVATE
    glfw3)

    find_package(X11 REQUIRED)
    target_link_libraries(Altseed_Core_Test PRIVATE ${X11_LIBRARIES})
endif()

# to use external projects
target_include_directories(
    Altseed_Core_Test
    PRIVATE 
    ${THIRDPARTY_INCLUDES})

# to use external projects
target_link_directories(
    Altseed_Core_Test
    PRIVATE
    ${THIRDPARTY_LIBRARY_DIRECTORIES})

# specify dependencies about external projects. 
# It is required to use external projects in addition of target_link_libraries
add_dependencies(
    Altseed_Core_Test
    ExternalProject_glfw
    TestData)


# make c++17 enabled
SET_TARGET_PROPERTIES(Altseed_Core_Test PROPERTIES CXX_STANDARD 17)

 if (MSVC)
    set_target_properties(Altseed_Core_Test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$(Configuration)")
endif()
