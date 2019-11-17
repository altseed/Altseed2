#!/bin/sh

echo set current directory
cd `dirname $0`

git submodule update --init bindings/CppBindingGenerator

git submodule update --init ../TestData
git submodule update --init ../thirdparty/SPIRV-Cross
git submodule update --init ../thirdparty/glfw
git submodule update --init ../thirdparty/glslang
git submodule update --init ../thirdparty/googletest
git submodule update --init ../thirdparty/libpng
git submodule update --init ../thirdparty/libzip
git submodule update --init ../thirdparty/spdlog
git submodule update --init ../thirdparty/zlib

echo finished
