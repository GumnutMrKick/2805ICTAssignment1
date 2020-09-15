// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
// import display manager file
#include "../header_files/display_manager.h"
// import play space file
#include "../header_files/play_space.h"
// import entity manager file
#include "../header_files/entity_manager.h"
// import info bar manager file
#include "../header_files/info_bar_manager.h"

// esential includes
#include <iostream>
#include <SDL.h>

using namespace std;

#ifndef game_H
#define game_H

class Game {

    private:

        // properties
        DisplayManager *display_manager = nullptr;
        PlaySpace *play_space = nullptr;
        EntityManager *entity_manager = nullptr;
        bool running = false;
        int cntr = 0;

    public:
    
        // constructor
        Game (const char* window_title, const int x_pos, const int y_pos, const int width,
            const int height, const bool fullscreen_bool, const bool is_square, const int segments_wide,
            const int segments_tall);
        
        // is used to handle game events
        void handleGameEvents();  //const char* event);

        // updates game logic
        void update ();
        
        // updates the render displayed on the screen
        void renderScreen ();
        
        bool isRunning();

        void gameLoop();
        
        // deconstructor    
        ~Game ();

};

#endif