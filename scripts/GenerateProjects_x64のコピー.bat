echo set current directory
cd /d %~dp0

mkdir ..\build

cd /d ..\build

cmake -A x64 -D BUILD_TEST=ON ../

pause