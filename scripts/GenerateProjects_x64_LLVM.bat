echo set current directory
cd /d %~dp0

mkdir ..\build

cd /d ..\build

cmake -A x64 -T LLVM -D BUILD_TEST=ON ../

pause