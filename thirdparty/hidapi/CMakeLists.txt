cmake_minimum_required(VERSION 3.12)

# solution name
project(hidapi)

if(WIN32)
    add_library(hidapi STATIC
        windows/hid.c
    )

    target_link_libraries(
        hidapi
        PRIVATE
        SetupAPI
    )

elseif(APPLE)
    add_library(hidapi STATIC
        windows/hid.c
    )
else()
    add_library(hidapi STATIC
        linux/hid.c
    )
endif()

target_include_directories(
	hidapi
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/hidapi
)