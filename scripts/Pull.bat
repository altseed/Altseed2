echo set current directory
cd /d %~dp0

cd ..
git pull
git submodule update --init

pause