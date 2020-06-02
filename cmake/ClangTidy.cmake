# Based on https://qiita.com/tenmyo/items/f8548ee9bab78f18cd25

cmake_minimum_required(VERSION 3.6)
option(CLANG_TIDY_ENABLED "Specifies whether clang-tidy is automatically applied." OFF)
find_program(CLANG_TIDY_EXE clang-tidy)

function(clang_tidy target)
if(CLANG_TIDY_ENABLED)
  if(CLANG_TIDY_EXE)
    message(STATUS "Enable Clang-Tidy ${target}")
    set_target_properties(${target} PROPERTIES
      C_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*;-header-filter=${CMAKE_CURRENT_SOURCE_DIR}/*;-fix"
      CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*;-header-filter=${CMAKE_CURRENT_SOURCE_DIR}*;-fix")
  else()
    message(STATUS "Clang-tidy is not found.")
  endif()
endif()
endfunction()
