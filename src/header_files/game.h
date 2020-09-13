// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
// import display manager file
#include "../header_files/display_manager.h"
// import play space file
#include "../header_files/play_space.h"

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
        PlaySpace *play_space;
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














// include <maths.h>
// include <ctime.h>

// // this class manages the scaling of values so that they
// // can reach their max values every 1 second irl, this allows
// // the game to run stable regardless the framerate
// class ValueScaleHandler {

// Private:

// double last_frame, scaler;

// Public:

// ValueScaleHandler () {

// this-->last_frame = currentTime();
// this->updateSelf();

// }

// // updates the class with the new frame time and
// // calculated frame time 
// void updateSelf() {

// double current_frame = currentTime();
// this->scaler = ((1000 / (current_frame - this->last_frame)) / 100);
// this->last_frame = current_frame;

// }

// // returns the appropriatly scaled input value
// scale(const double value) {

// return(value * this->scaler);

// }

// };

// // this class stores the int value location of something
// // on the map for the map
// class MapLocation {

// Public:

// int x, y;

// MapLocation(const int location_x = 0, const int location_y = 0) {

// this->x = location_x;
// this->y = location_y;

// }

// };

// // this class stores the float value location of something
// // on the map
// class Location {

// Public:

// float x,y;

// Location (const float location_x = 0, const float location_y = 0) {

// this->x = location_x;
// this->y = location_y;

// }

// MapLocation* ConvertToMapLoc() {

// const int x = round(this->x), y = round(this->y);

// return new MapLocation(x, y);

// }

// }

// // this class acts as the most basic form of an entity
// // before they diversify through inheritence
// class Entity {

// Public:

// Location* entity_location;
// int sprite_id;

// Entity(const float x = 0, const float y = 0, const int id) {

// this->entity_location = new Location(x, y);
// this->sprite_id = id;

// }

// };

// class Wall inherits Entity {};




#endif