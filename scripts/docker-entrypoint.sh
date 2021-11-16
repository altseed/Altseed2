#!/bin/sh

echo set current directory
cd `dirname $0`

python3 generate_tool.py --clang-file /usr/lib/llvm-11/lib/libclang-11.so.1
echo done python3 generate_tool.py

python3 generate_cbg_definition.py --clang-file /usr/lib/llvm-11/lib/libclang-11.so.1
echo done python3 generate_cbg_definition.py

python3 generate_wrapper.py
echo done python3 generate_wrapper.py

cd ../.ci/

python3 check_format.py
echo done python3 check_format.py
