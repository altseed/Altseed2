cmake_minimum_required(VERSION 3.8)

# add directories
add_subdirectory(src)

if(BUILD_TEST)
  add_subdirectory(test)
endif()
