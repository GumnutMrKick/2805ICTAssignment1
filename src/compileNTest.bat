@echo OFF
TITLE COMPILATION AND TESTING MACHINE
color 0a
MinGW32-make --makefile="make/Makefile"
pause
..\out\test_S5132483_Pacman.exe
PAUSE