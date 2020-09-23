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

        int getIntConfig () {

            return stoi(this->returnNewConfig());

        }

        bool getBoolConfig () {

            return (this->returnNewConfig() == "true") ? true : false;

        }

        ~FileInput () {

            config_file.close();

        }

};

int main(int argc, char *argv[]) {

    // -------------------- file config input --------------------

    // things to be gathered from the config file
    string up;
    string left;
    string down;
    string right;
    
    int FPS;

    string title;
    int x_pos;
    int y_pos;
    int segments_wide;
    int segments_tall;
    int gamemode;

    // gain input from the file
    FileInput *config = new FileInput();    

    // if the opening of the file was successful, extract the inputs
    if (config->config_file) {
       
        // copy out the configs
        up = config->returnNewConfig();
        left = config->returnNewConfig();
        down = config->returnNewConfig();
        right = config->returnNewConfig();

        FPS = config->getIntConfig();
        title = config->returnNewConfig();
        x_pos = config->getIntConfig();
        y_pos = config->getIntConfig();

        segments_wide = config->getIntConfig();
        segments_tall = config->getIntConfig();

        gamemode = config->getIntConfig();

        cout << "config successfully gotten from the config file" << endl;

    // otherwise give error msg and assign defualt values
    } else {

        cout << "Error getting config file input loading defualt values" << endl;
    
        up = "SDLK_UP";
        left = "SDLK_LEFT";
        down = "SDLK_DOWN";
        right = "SLDK_RIGHT";

        FPS = 60;
        title = "Pacman";
        x_pos = 0;
        y_pos = 0;

        segments_wide = 3;
        segments_tall = 3;

        gamemode = 0;

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
    Control_bindings bindings = Control_bindings(up.c_str(), left.c_str(), down.c_str(), right.c_str());
    
    // test key bindings
    cout << "---------- testing key bindings ----------" << endl;
    cout << "expected : recieved" << endl;
    cout << "up : " << bindings.SDLToCommand(up.c_str()) << endl;
    cout << "left : " << bindings.SDLToCommand(left.c_str()) << endl;
    cout << "down : " << bindings.SDLToCommand(down.c_str()) << endl;
    cout << "right : " << bindings.SDLToCommand(right.c_str()) << endl;

    // -------------------- game settings / creation --------------------

    // these are the settings that will be parsed through to
    // the main game loop
    // if I have time I'll go back and add a config file that
    // can loaded in to get the users desired control bindings


    Game *game = new Game(title.c_str(), x_pos, y_pos, gamemode, segments_wide, segments_tall);

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





