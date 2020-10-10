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
            
            config_file.open("resource_files/config.txt");

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
    int up, left, down, right;
    int x_pos, y_pos;
    int segments_wide, segments_tall;
    int FPS, gamemode;
    string title;

    // gain input from the file
    FileInput *config = new FileInput();    

    // if the opening of the file was successful, extract the inputs
    if (config->config_file) {
       
        // copy out the configs
        up = config->getIntConfig();
        left = config->getIntConfig();
        down = config->getIntConfig();
        right = config->getIntConfig();

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
    
        up = 1073741906;
        left = 1073741904;
        down = 1073741905;
        right = 1073741903;

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
    Control_bindings bindings = Control_bindings(up, left, down, right);
    
    // test key bindings
    cout << "---------- testing key bindings ----------" << endl;
    cout << "expected : recieved" << endl;
    cout << "up : " << bindings.SDLToCommand(up) << endl;
    cout << "right : " << bindings.SDLToCommand(right) << endl;
    cout << "down : " << bindings.SDLToCommand(down) << endl;
    cout << "left : " << bindings.SDLToCommand(left) << endl;

    // -------------------- game settings / creation --------------------

    // these are the settings that will be parsed through to
    // the main game loop
    // if I have time I'll go back and add a config file that
    // can loaded in to get the users desired control bindings

    Game *game = new Game(title.c_str(), x_pos, y_pos, gamemode, segments_wide, segments_tall, bindings);

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





