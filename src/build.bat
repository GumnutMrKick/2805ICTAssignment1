@echo OFF
TITLE COMPILATION MACHINE
color 0a
g++ -std=c++17 "source_files\main.cpp" "source_files\control_bindings.cpp" -I"C:\Development\C++\Packages\SDL2_32bit\include\SDL2" -L"C:\Development\C++\Packages\SDL2_32bit\lib" -Wall -lmingw32 -lSDL2main -lSDL2 -mwindows -o "..\out\S5132483_Pacman"