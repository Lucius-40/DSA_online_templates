@echo off
g++ -O2 -std=c++17 test.cpp hash_functions/metroHash/metrohash64.cpp hash_functions/"MurMur hash"/MurmurHash3.cpp -o test.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo Running hash function comparison test...
echo.
test.exe

pause
