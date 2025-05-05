@echo off
echo [INFO] Compilare joc...
g++ -std=c++17 -ISFML/include -LSFML/lib src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o main.exe

if %errorlevel% neq 0 (
    echo [ERROR] Compilarea a esuat.
    exit /b
)

echo [INFO] Rulare joc...
set PATH=%CD%\dll;%PATH%
main.exe