
enable_language(CXX)

# set files
set(core_files
    Core.h
    Core.cpp
    BaseObject.h
    BaseObject.cpp
    Wrapper.cpp
    Scene.h
    Scene.cpp
    Common/Array.h
    Common/ResourceContainer.h
    Common/Resource.h
    Common/Resources.h
    Common/Resources.cpp
    Common/StringHelper.h
    Platform/FileSystem.h
    Window/Window.h
    Window/Window.cpp
    Input/ButtonState.h
    Input/Keyboard.h
    Input/Keyboard.cpp
    Input/Joystick.h
    Input/Joystick.cpp
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
    Graphics/Texture2D.h
    Graphics/Texture2D.cpp
    Graphics/LLGIWindow.h
    Graphics/LLGIWindow.cpp
    Graphics/Shader.h
    Graphics/Shader.cpp
    Graphics/Material.h
    Graphics/Material.cpp
    Graphics/Font.h
    Graphics/Font.cpp
    Graphics/Color.h
    Graphics/Color.cpp
    Graphics/CommandList.h
    Graphics/CommandList.cpp
    Graphics/RenderTexture.h
    Graphics/RenderTexture.cpp
    Graphics/BatchRenderer.h
    Graphics/BatchRenderer.cpp
    Graphics/BuildinShader.h
    Graphics/BuildinShader.cpp
    Graphics/ShaderCompiler/ShaderCompiler.h
    Graphics/ShaderCompiler/ShaderCompiler.cpp
    Graphics/ShaderCompiler/ShaderTranspiler.h
    Graphics/ShaderCompiler/ShaderTranspiler.cpp
    Graphics/ShaderCompiler/ResourceLimits.h
    Graphics/ShaderCompiler/ResourceLimits.cpp
	Graphics/Renderer/Rendered.h
	Graphics/Renderer/Rendered.cpp
	Graphics/Renderer/RenderedCamera.h
	Graphics/Renderer/RenderedCamera.cpp
	Graphics/Renderer/RenderedSprite.h
	Graphics/Renderer/RenderedSprite.cpp
	Graphics/Renderer/Renderer.h
	Graphics/Renderer/Renderer.cpp
    Math/Easing.cpp
    Math/Easing.h
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
    Math/Vector2F.cpp
    Math/Vector2F.h
    Math/Vector2I.cpp
    Math/Vector2I.h
    Math/Vector3F.cpp
    Math/Vector3F.h
    Math/Vector3I.cpp
    Math/Vector3I.h
    Math/Vector4F.cpp
    Math/Vector4F.h
    Math/Vector4I.cpp
    Math/Vector4I.h
    Sound/SoundMixer.h
    Sound/SoundMixer.cpp
    Sound/Sound.h
    Sound/Sound.cpp
    Tool/Tool.h
    Tool/Tool.cpp
)

# imgui

if(WIN32)
    list(APPEND
        core_files
        Tool/Platform/ImGuiPlatformDX12.h
    )
elseif(APPLE)
    list(APPEND
        core_files
        Tool/Platform/ImGuiPlatformMetal.h
        Tool/Platform/ImGuiPlatformMetal.mm)
endif()

if(BUILD_VULKAN)
    list(APPEND
        core_files
        Tool/Platform/ImGuiPlatformVulkan.h
        Tool/Platform/ImGuiPlatformVulkan.cpp)
endif()


if(WIN32)

    list(APPEND core_files
        Platform/FileSystemWin.cpp
    )

elseif(APPLE)

    list(APPEND core_files
        Platform/FileSystemMac.cpp
    )

else()

    list(APPEND core_files
        Platform/FileSystemLinux.cpp
    )

endif()

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
    OpenSoundMixer
    zip
	imgui
    debug "${LIBPNG_LIB_DEBUG}"
    optimized "${LIBPNG_LIB_RELEASE}"

    debug "${GLFW3_LIB_DEBUG}"
    optimized "${GLFW3_LIB_RELEASE}"

    debug "${LIBSPIRVCROSS_CORE_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_C_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_CPP_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_HLSL_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_GLSL_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_MSL_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_REFLECT_LIB_DEBUG}"
    debug "${LIBSPIRVCROSS_UTIL_LIB_DEBUG}"

    optimized "${LIBSPIRVCROSS_CORE_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_C_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_CPP_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_HLSL_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_GLSL_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_MSL_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_REFLECT_LIB_RELEASE}"
    optimized "${LIBSPIRVCROSS_UTIL_LIB_RELEASE}"
)

if (MSVC)

    target_link_libraries(
        Altseed_Core
        PRIVATE
        debug zlibstaticd
        optimized zlibstatic
        debug glslangd
        optimized glslang
        debug HLSLd
        optimized HLSL
        debug OGLCompilerd
        optimized OGLCompiler
        debug OSDependentd
        optimized OSDependent
        debug SPIRVd
        optimized SPIRV
        debug SPVRemapperd
        optimized SPVRemapper
    )

elseif(APPLE)

    find_library(OPEN_AL OpenAL)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(METAL_LIBRARY Metal)
    find_library(APPKIT_LIBRARY AppKit)
    find_library(METALKIT_LIBRARY MetalKit)
    find_library(QUARTZ_CORE_LIBRARY QuartzCore)

    target_link_libraries(
        Altseed_Core
        PRIVATE
        z
        glslang
        HLSL
        OGLCompiler
        OSDependent
        SPIRV
        SPVRemapper
        ${OPEN_AL}
        ${COCOA_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${CORE_FOUNDATION_FRAMEWORK}
        ${CORE_VIDEO_FRAMEWORK}
        ${APPKIT_LIBRARY}
        ${METAL_LIBRARY}
        ${METALKIT_LIBRARY}
        ${QUARTZ_CORE_LIBRARY}
    )

else()

    find_package(X11 REQUIRED)
    target_link_libraries(Altseed_Core PRIVATE ${X11_LIBRARIES})

    target_link_libraries(
        Altseed_Core
        PRIVATE
        z
        stdc++fs
        ssl
        crypto
        X11
        X11-xcb
        glslang
        HLSL
        OGLCompiler
        OSDependent
        SPIRV
        SPVRemapper
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
    ExternalProject_libzip
    ExternalProject_glslang
    ExternalProject_SPIRV-Cross)

# export all functions to out of dll for testing
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# make c++17 enabled
SET_TARGET_PROPERTIES(Altseed_Core PROPERTIES CXX_STANDARD 17)
