echo set current directory
cd /d %~dp0

mkdir ..\build_sanitizer

cd /d ..\build_sanitizer

cmake -A Win32 -D BUILD_TEST=ON -D MSVC_SANITIZE_ENABLED=ON ../

cd /d %~dp0

python GenerateProjects_Sanitizer_MSVC.py

pause