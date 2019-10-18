cd %~dp0
FOR /f "usebackq tokens=*" %%i IN (`cd`) DO set PYTHONPATH=%%i;%%i\cbg

cd ..\core\src

python ..\..\scripts\generate_wrapper.py

pause