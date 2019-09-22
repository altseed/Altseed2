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

# zlib
ExternalProject_Add(
    ExternalProject_zlib
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/zlib
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/zlib
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/zlib
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/zlib
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DASM686=off
                    -DAMD64=off
)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/zlib/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/zlib/lib)

# libpng
ExternalProject_Add(
    ExternalProject_libpng
    DEPENDS         ExternalProject_zlib
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/libpng
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/libpng
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/libpng
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/libpng
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DZLIB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/Install/zlib/include
                    -DPNG_BUILD_ZLIB=ON
                    -DPNG_SHARED=OFF
                    -DPNG_TESTS=OFF
)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/libpng/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/libpng/lib)

# libzip
ExternalProject_Add(
    ExternalProject_libzip
    DEPENDS         ExternalProject_zlib
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/libzip
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/libzip
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/libzip
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/libzip
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DZLIB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/Install/zlib/include
                    -DZLIB_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/Install/zlib/lib
                    -DBUILD_SHARED_LIBS=OFF
                    -DBUILD_TOOLS=OFF
                    -DBUILD_REGRESS=OFF
                    -DBUILD_EXAMPLES=OFF
                    -DBUILD_DOC=OFF
                    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
                    -DENABLE_BZIP2=OFF
)

list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/libzip/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/libzip/lib)

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

# hidapi
add_subdirectory(hidapi EXCLUDE_FROM_ALL)

# spdlog
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

# LLGI
set(BUILD_TEST_TEMP ${BUILD_TEST})
set(BUILD_TEST OFF)
add_subdirectory(LLGI)
set(BUILD_TEST ${BUILD_TEST_TEMP})
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/LLGI/src)

# stb
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/stb)

# assign valiables into the parent scope
set(THIRDPARTY_INCLUDES ${THIRDPARTY_INCLUDES} PARENT_SCOPE)
set(THIRDPARTY_LIBRARY_DIRECTORIES ${THIRDPARTY_LIBRARY_DIRECTORIES} PARENT_SCOPE)
