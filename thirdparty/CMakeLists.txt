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
    GIT_REPOSITORY  https://github.com/altseed/zlib
    GIT_TAG         v1.2.11
    SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/zlib-src
    BINARY_DIR      ${CMAKE_CURRENT_BINARY_DIR}/zlib-build
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
                    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/libpng/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/libpng/lib)

if(MSVC)
    set(LIBPNG_LIB_DEBUG "libpng16_staticd" PARENT_SCOPE)
    set(LIBPNG_LIB_RELEASE "libpng16_static" PARENT_SCOPE)
elseif(BUILD_WITH_POSTFIX)
    set(LIBPNG_LIB_DEBUG "png16d" PARENT_SCOPE)
    set(LIBPNG_LIB_RELEASE "png16" PARENT_SCOPE)
else()
    set(LIBPNG_LIB_DEBUG "png16" PARENT_SCOPE)
    set(LIBPNG_LIB_RELEASE "png16" PARENT_SCOPE)
endif()

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

if(BUILD_WITH_POSTFIX)
    set(GLFW3_LIB_DEBUG "glfw3d" PARENT_SCOPE)
    set(GLFW3_LIB_RELEASE "glfw3" PARENT_SCOPE)
else()
    set(GLFW3_LIB_DEBUG "glfw3" PARENT_SCOPE)
    set(GLFW3_LIB_RELEASE "glfw3" PARENT_SCOPE)
endif()

# glslang
ExternalProject_Add(
    ExternalProject_glslang
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/glslang
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/glslang
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/glslang
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/glslang
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DBUILD_SHARED_LIBS=OFF
                    -DBUILD_TEST=OFF
                    -DENABLE_PCH=OFF
                    -DENABLE_RTTI=ON
)

list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/glslang/include)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/glslang/include/glslang/Include)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/glslang/include/glslang)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/glslang/lib)

# SPIRV
ExternalProject_Add(
    ExternalProject_SPIRV-Cross
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/SPIRV-Cross
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/Build/SPIRV-Cross
    INSTALL_DIR     ${CMAKE_CURRENT_BINARY_DIR}/Install/SPIRV-Cross
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/Install/SPIRV-Cross
                    -DCMAKE_DEBUG_POSTFIX=d
                    -DCMAKE_USER_MAKE_RULES_OVERRIDE=${CMAKE_CURRENT_SOURCE_DIR}/CFlagOverrides.cmake
                    -DUSE_MSVC_RUNTIME_LIBRARY_DLL=${USE_MSVC_RUNTIME_LIBRARY_DLL}
                    -DBUILD_SHARED_LIBS=OFF
                    -DSPIRV_CROSS_ENABLE_TESTS=OFF
                    -DSPIRV_CROSS_FORCE_PIC=ON
)


if(BUILD_WITH_POSTFIX)
    set(LIBSPIRVCROSS_CORE_LIB_DEBUG "spirv-cross-cored" PARENT_SCOPE)
    set(LIBSPIRVCROSS_C_LIB_DEBUG "spirv-cross-cd" PARENT_SCOPE)
    set(LIBSPIRVCROSS_CPP_LIB_DEBUG "spirv-cross-cppd" PARENT_SCOPE)
    set(LIBSPIRVCROSS_HLSL_LIB_DEBUG "spirv-cross-hlsld" PARENT_SCOPE)
    set(LIBSPIRVCROSS_GLSL_LIB_DEBUG "spirv-cross-glsld" PARENT_SCOPE)
    set(LIBSPIRVCROSS_MSL_LIB_DEBUG "spirv-cross-msld" PARENT_SCOPE)
    set(LIBSPIRVCROSS_REFLECT_LIB_DEBUG "spirv-cross-reflectd" PARENT_SCOPE)
    set(LIBSPIRVCROSS_UTIL_LIB_DEBUG "spirv-cross-utild" PARENT_SCOPE)

    set(LIBSPIRVCROSS_CORE_LIB_RELEASE "spirv-cross-core" PARENT_SCOPE)
    set(LIBSPIRVCROSS_C_LIB_RELEASE "spirv-cross-c" PARENT_SCOPE)
    set(LIBSPIRVCROSS_CPP_LIB_RELEASE "spirv-cross-cpp" PARENT_SCOPE)
    set(LIBSPIRVCROSS_HLSL_LIB_RELEASE "spirv-cross-hlsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_GLSL_LIB_RELEASE "spirv-cross-glsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_MSL_LIB_RELEASE "spirv-cross-msl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_REFLECT_LIB_RELEASE "spirv-cross-reflect" PARENT_SCOPE)
    set(LIBSPIRVCROSS_UTIL_LIB_RELEASE "spirv-cross-util" PARENT_SCOPE)
else()
    set(LIBSPIRVCROSS_CORE_LIB_DEBUG "spirv-cross-core" PARENT_SCOPE)
    set(LIBSPIRVCROSS_C_LIB_DEBUG "spirv-cross-c" PARENT_SCOPE)
    set(LIBSPIRVCROSS_CPP_LIB_DEBUG "spirv-cross-cpp" PARENT_SCOPE)
    set(LIBSPIRVCROSS_HLSL_LIB_DEBUG "spirv-cross-hlsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_GLSL_LIB_DEBUG "spirv-cross-glsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_MSL_LIB_DEBUG "spirv-cross-msl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_REFLECT_LIB_DEBUG "spirv-cross-reflect" PARENT_SCOPE)
    set(LIBSPIRVCROSS_UTIL_LIB_DEBUG "spirv-cross-util" PARENT_SCOPE)

    set(LIBSPIRVCROSS_CORE_LIB_RELEASE "spirv-cross-core" PARENT_SCOPE)
    set(LIBSPIRVCROSS_C_LIB_RELEASE "spirv-cross-c" PARENT_SCOPE)
    set(LIBSPIRVCROSS_CPP_LIB_RELEASE "spirv-cross-cpp" PARENT_SCOPE)
    set(LIBSPIRVCROSS_HLSL_LIB_RELEASE "spirv-cross-hlsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_GLSL_LIB_RELEASE "spirv-cross-glsl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_MSL_LIB_RELEASE "spirv-cross-msl" PARENT_SCOPE)
    set(LIBSPIRVCROSS_REFLECT_LIB_RELEASE "spirv-cross-reflect" PARENT_SCOPE)
    set(LIBSPIRVCROSS_UTIL_LIB_RELEASE "spirv-cross-util" PARENT_SCOPE)
endif()

list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Install/SPIRV-Cross/include)
list(APPEND THIRDPARTY_LIBRARY_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/Install/SPIRV-Cross/lib)

# box2d
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "disable box2d unit test" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "disable box2d testbed" FORCE)
add_subdirectory(box2d)
set_property(TARGET box2d PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/box2d/include)

# hidapi
add_subdirectory(hidapi EXCLUDE_FROM_ALL)

# spdlog
add_subdirectory(spdlog EXCLUDE_FROM_ALL)
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)

# imgui
add_subdirectory(imgui EXCLUDE_FROM_ALL)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# nativefiledialog
set(NFD_BUILD_UNIT_TESTS OFF CACHE BOOL "disable NFD unit test" FORCE)
add_subdirectory(nativefiledialog)
set_property(TARGET nativefiledialog PROPERTY POSITION_INDEPENDENT_CODE ON)
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/nativefiledialog/src/include)

# LLGI
set(BUILD_TEST_TEMP ${BUILD_TEST})
set(BUILD_TEST OFF)
add_subdirectory(LLGI)
set(BUILD_TEST ${BUILD_TEST_TEMP})
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/LLGI/src)

# OSM
set(BUILD_TEST_TEMP ${BUILD_TEST})
set(BUILD_TEST OFF)
add_subdirectory(OpenSoundMixer)
set(BUILD_TEST ${BUILD_TEST_TEMP})
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/OpenSoundMixer/src)

# stb
list(APPEND THIRDPARTY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/stb)

# assign valiables into the parent scope
set(THIRDPARTY_INCLUDES ${THIRDPARTY_INCLUDES} PARENT_SCOPE)
set(THIRDPARTY_LIBRARY_DIRECTORIES ${THIRDPARTY_LIBRARY_DIRECTORIES} PARENT_SCOPE)
