echo set current directory
cd /d %~dp0

mkdir ..\build_clang_format

cd /d ..\build_clang_format

cmake -D BUILD_TEST=ON -D CLANG_FORMAT_ENABLED=ON ../
