@echo off
cd /d %~dp0
if not exist build (
    mkdir build
)
cd build

cmake -DWIN=ON -G "Visual Studio 12" ..
pause
