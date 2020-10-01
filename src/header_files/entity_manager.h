// esential includes
#include <stdio.h>
#include <string>
#include <math.h>
#include <ctime>
#include <utility>
#include <vector>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"
// import play space file
#include "../header_files/play_space.h"
// import animation handler file
#include "../header_files/animation_handler.h"

using namespace std;

#ifndef entity_manager_H
#define entity_manager_H

// render task data structure
struct Location {

    int x, y;

};

// generates a valid version of the render task struct
Location generateLocationHolder(const int x, const int y);

// is the abstract class which all higher order entities inherit
class Entity {

    private:

        // properties
        AnimationHandler* animation_handler;

    public:

        // properties
        // the state of the entity
        string state;
        
        // general variables to run the basic animation /movement
        // rendering of any entity
        Location entity_location;
        int movement_frame, animation_frame, propulsion;

        // loads the animations of the entity
        void loadAnimations(pair < vector < pair < string, Animation* > >, int > loaded_animations);

        // the basic initialisation required by any form of entity
        void basicEntityInitialisation (const int gamemode, const int x, const int y, const int propulsion);

        // changes the current location of the entity
        void changeCurrentLocation (const int x, const int y);

        // returns the current location of the entity
        Location getCurrentLocation ();
        
        // changes the current state of the entity
        void changeCurrentState (string str);

        // returns the current state of the entity
        string getCurrentState ();

        // updates the entities properties
        void entityUpdate(const int frame);

        // decides the next move that will be taken by the
        // entity
        virtual string resolveEntityState() = 0;

        // updates the entites location properties
        virtual void entityMovementUpdate () = 0;

        // updates the entites animation settings
        void entityAnimationUpdate (string state);

        // runs the rendering process of the entity
        void entityRender ();

};

class Enigma : public Entity {
    private:
        bool run;

    public:

        // constructor
        Enigma (const int gamemode);

        // sets the state of the run bool variable
        void setRun (const bool state);

        // decides the next move that will be taken
        // by the entity
        string resolveEntityState();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class Player : public Entity {

    private:
        // properties
        

    public:

        // constructor
        Player (const int game_mode);

        // decides the next move that will be taken
        // by the entity
        string resolveEntityState();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class Ghost : public Entity {

    private:
        // properties
        

    public:

        // constructor
        Ghost (const int game_mode, string ghost_name);

        // decides the next move that will be taken
        // by the entity
        string resolveEntityState();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class EntityManager {

    private:

        // properties
        Enigma* enigma;
        Player* player;
        Ghost* ghosts[4];
        int frame;

        // these functions contain the animation information
        // for all the active entities (they will be defined
        // at the bottom of the cpp file for readability)
        void supplyEnigmaAnimations ();
        void supplyPlayerAnimations ();
        void supplyBlinkyAnimations ();
        void supplyPinkyAnimations ();
        void supplyInkyAnimations ();
        void supplyClydeAnimations ();
        // this function calls the above functions
        void supplyEntityAnimations ();

    public:

        // constructor
        EntityManager (const int game_mode);

        // preforms the nessary updates to the game's active entities
        void updateEntities();

        // renders the game's active entities
        void renderEntities();

};




// class Player {

//     private:

//         // properties
//         static DisplayManager *display_manager;

//     public:

//         // constructor
//         Entity ();

//         ~Entity ();

// };


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