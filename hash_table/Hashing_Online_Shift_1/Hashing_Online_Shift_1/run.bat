@echo off
g++ -O2 -std=c++17 main.cpp hashTable/hash_functions/metroHash/metrohash64.cpp hashTable/hash_functions/"MurMur hash"/MurmurHash3.cpp -o test.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)


test.exe

pause