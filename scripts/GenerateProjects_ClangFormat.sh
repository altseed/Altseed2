#!/bin/sh

echo set current directory
cd `dirname $0`

mkdir ../build_clang_format

cd ../build_clang_format

cmake -D BUILD_TEST=ON -D CLANG_FORMAT_ENABLED=ON ../
