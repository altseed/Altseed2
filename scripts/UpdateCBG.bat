echo set current directory
cd /d %~dp0

cd ..
git pull
git submodule update --init
git submodule update --init --remote -- "scripts/bindings/CppBindingGenerator"

cd scripts/bindings/CppBindingGenerator
git submodule update --init
pause