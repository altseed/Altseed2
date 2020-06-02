#!/bin/sh

echo set current directory
cd `dirname $0`

mkdir ../build_clang_tidy

cd ../build_clang_tidy

cmake -D BUILD_TEST=ON -D CLANG_TIDY_ENABLED=ON ../
