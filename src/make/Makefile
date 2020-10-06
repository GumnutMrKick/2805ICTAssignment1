# src folder
SRC_FOLDER = ..\source_files

#Packages path
PACKAGES = ..\..\install_packages\Packages

# compiler
CC = g++

# include flags
INCLUDE_FLAGS = -I"C:\Development\C++\Packages\SDL2_32bit\include\SDL2" -I"C:\Development\C++\Packages\SDL2_image_32bit\include\SDL2"

# libary flags
LIBARY_FLAGS = -L"$(PACKAGES)\SDL2_32bit\lib" -L"$(PACKAGES)\SDL2_image_32bit\lib"

# linker flags
LINKER_FLAGS = -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# compiler flags I'll need to add -mwindows to remove the console from launching on run
COMPILER_FLAGS = -std=c++17 $(INCLUDE_FLAGS) $(LIBARY_FLAGS) $(LINKER_FLAGS)

# object compiler flags
OBJECT_COMPILERFLAGS = -c $(COMPILER_FLAGS)

# object files
OBJECT_FILES = main.o control_bindings.o game.o display_manager.o play_space.o entity_manager.o animation_handler.o info_bar_manager.o path_manager.o

output: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(COMPILER_FLAGS) -o "..\..\out\test_S5132483_Pacman"

# individual files
main.o: $(SRC_FOLDER)\main.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\main.cpp"

control_bindings.o: $(SRC_FOLDER)\control_bindings.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\control_bindings.cpp"

game.o: $(SRC_FOLDER)\game.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\game.cpp"

display_manager.o: $(SRC_FOLDER)\display_manager.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\display_manager.cpp"

play_space.o: $(SRC_FOLDER)\play_space.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\play_space.cpp"

entity_manager.o: $(SRC_FOLDER)\entity_manager.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\entity_manager.cpp"
	
animation_handler.o: $(SRC_FOLDER)\animation_handler.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\animation_handler.cpp"

info_bar_manager.o: $(SRC_FOLDER)\info_bar_manager.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\info_bar_manager.cpp"

path_manager.o: $(SRC_FOLDER)\path_manager.cpp
	$(CC) $(OBJECT_COMPILERFLAGS) "$(SRC_FOLDER)\path_manager.cpp"

clean:
	rm *.o output