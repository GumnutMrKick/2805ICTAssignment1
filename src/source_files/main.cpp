// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
// import game
#include "../header_files/game.h"

// import esentials
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <cstring> 
#include <string>

// import SDL
#include <SDL.h>

// SDL main naming error fix
#define SDL_MAIN_HANDLED

// std namespace 
using namespace std;

class FileInput {

    public:

        ifstream config_file;

        FileInput () {
            
            config_file.open("rescource_files/config.txt");

        }

        string returnNewConfig () {

            string str;
            getline(config_file, str);
            getline(config_file, str);
            return str;

        }

        ~FileInput () {

            config_file.close();

        }

};

int main(int argc, char *argv[]) {

    // -------------------- file config input --------------------

    // things to be gathered from the config file
    char* up;
    char* left;
    char* down;
    char* right;
    
    int FPS;

    char* title;
    int x_pos;
    int y_pos;
    int width;
    int height;
    bool fullscreen;
    bool square;
    int segments_wide;
    int segments_tall;

    // gain input from the file
    FileInput *config = new FileInput();    

    // if the opening of the file was successful, extract the inputs
    if (config->config_file) {

        cout << "config successfully gotten from the config file" << endl;
        
        // copy out the configs
        strcpy(up, config->returnNewConfig().c_str());
        strcpy(left, config->returnNewConfig().c_str());
        strcpy(down, config->returnNewConfig().c_str());
        strcpy(right, config->returnNewConfig().c_str());
        FPS = stoi(config->returnNewConfig());
        strcpy(title, config->returnNewConfig().c_str());
        x_pos = stoi(config->returnNewConfig());
        y_pos = stoi(config->returnNewConfig());
        width = stoi(config->returnNewConfig());
        height = stoi(config->returnNewConfig());
        fullscreen = (config->returnNewConfig() == "true") ? true : false;
        square = (config->returnNewConfig() == "true") ? true : false;
        segments_wide = stoi(config->returnNewConfig());
        segments_tall = stoi(config->returnNewConfig());

    // otherwise give error msg and assign defualt values
    } else {

        cout << "Error getting config file input loading defualt values" << endl;
    
        up = "SDLK_UP";
        left = "SDLK_LEFT";
        down = "SDLK_DOWN";
        right = "SLDK_RIGHT";
        FPS = 60;
        title = "Pacman";
        x_pos = 20;
        y_pos = 20;
        width = 800;
        height = 800;
        fullscreen = false;
        square = true;

    }

    // variables for capping the frame rate
    const int frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int time_used;
    
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


    Game *game = new Game(title, x_pos, y_pos, width, height, fullscreen, square, 0,0);

    // -------------------- game loop creation and running --------------------

	while (game->isRunning()) {

        // record frame start
        frame_start = SDL_GetTicks();

		game->handleGameEvents();
		game->update();
		game->renderScreen();
    
        // record the time spent
        time_used = SDL_GetTicks() - frame_start;
	
        if (frame_delay > time_used) {

            SDL_Delay(frame_delay - time_used);

        }

    }

	game->~Game();
    return 0;

}





