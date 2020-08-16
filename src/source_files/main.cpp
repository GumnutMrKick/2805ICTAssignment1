// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
// import game
#include "../header_files/game.h"

// import esentials 
#include <stdio.h>
#include <iostream>

// import SDL
#include <SDL.h>

// SDL main naming error fix
#define SDL_MAIN_HANDLED

// std namespace 
using namespace std;

int main(int argc, char *argv[]) {

    // -------------------- SDL initialisation --------------------

    // check that SDL is installed correctly and
    // that all features intialise successfully
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    
        cout << "Error Initialising SDL: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    
    } else {

        cout << "SDL fully initialised and running" << endl;

    }

    // -------------------- key bindings --------------------

    // these are the buttons that will be binded to commands,
    // if I have time I'll go back and add a config file that
    // can loaded in to get the users desired control bindings
    const char* up = "SDLK_UP";
    const char* left = "SDLK_LEFT";
    const char* down = "SDLK_DOWN";
    const char* right = "SLDK_RIGHT";

    // create key binder
    Control_bindings bindings = Control_bindings(up, left, down, right);
    
    // test key bindings
    cout << "---------- testing key bindings ----------" << endl;
    cout << "expected : recieved" << endl;
    cout << "up : " << bindings.SDLToCommand(up) << endl;
    cout << "left : " << bindings.SDLToCommand(left) << endl;
    cout << "down : " << bindings.SDLToCommand(down) << endl;
    cout << "right : " << bindings.SDLToCommand(right) << endl;

    // -------------------- game settings / creation --------------------

    // these are the settings that will be parsed through to
    // the main game loop
    // if I have time I'll go back and add a config file that
    // can loaded in to get the users desired control bindings


    Game *game = new Game("Pacman", 20, 20, 800, 800, false);

    // -------------------- game loop creation and running --------------------

	while (game->isRunning()) {

		game->handleGameEvents();
		game->update();
		game->renderScreen();
	
    }

	game->~Game();
    return 0;

}





