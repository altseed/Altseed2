cmake_minimum_required(VERSION 3.12)

# Google Test
if(BUILD_TEST)
    set(BUILD_GMOCK OFF CACHE INTERNAL "" FORCE)
    set(INSTALL_GTEST OFF CACHE INTERNAL "" FORCE)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE INTERNAL "" FORCE)
    endif()
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
endif()

add_subdirectory(glfw EXCLUDE_FROM_ALL)