echo set current directory
cd /d %~dp0

cd ..
git pull
git submodule update --init
git submodule update --init --remote -- "thirdparty/LLGI"

cd thirdparty/LLGI
git submodule update --init
pause