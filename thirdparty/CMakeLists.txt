cmake_minimum_required(VERSION 3.12)

# make ExternalProject_Add enabled
include(ExternalProject)

# Google Test
if(BUILD_TEST)
    set(BUILD_GMOCK OFF CACHE INTERNAL "" FORCE)
    set(INSTALL_GTEST OFF CACHE INTERNAL "" FORCE)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE INTERNAL "" FORCE)
    endif()
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
endif()

# glfw
ExternalProject_Add(
    ExternalProject_glfw
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/glfw
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/glfw
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/glfw
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/glfw
                    -DCMAKE_DEBUG_POSTFIX=d
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DGLFW_BUILD_EXAMPLES=OFF
                    -DGLFW_BUILD_TESTS=OFF
                    -DGLFW_BUILD_DOCS=OFF
                    -DGLFW_INSTALL=ON
)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/glfw/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/glfw/lib)

# spdlog
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

# assign valiables into the parent scope
set(THIRDPARTY_INCLUDES ${THIRDPARTY_INCLUDES} PARENT_SCOPE)
set(THIRDPARTY_LIBRARY_DIRECTORIES ${THIRDPARTY_LIBRARY_DIRECTORIES} PARENT_SCOPE)
