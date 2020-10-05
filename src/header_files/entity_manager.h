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
        virtual void resolveEntityState() = 0;

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
        Enigma (const int gamemode, Location spawn);

        // sets the state of the run bool variable
        void setRun (const bool state);

        // resolves the enigma's state
        void resolveEntityState();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class Player : public Entity {

    private:
        // properties
        

    public:

        // constructor
        Player (const int gamemode, Location spawn);

        // resolves the players state deciding if the
        // collisions have happened
        void resolveEntityState();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class Ghost : public Entity {

    private:
        // properties
        Location spawn;
        int ghost_number;
        bool dead;

    public:

        // constructor
        Ghost (const int gamemode, const int ghost_number, Location spawn);

        // returns the death state of the ghost
        bool getdeadstate();

        // sets the death state of the ghost
        void setdeadstate();

        // decides the next move that will be taken
        // by the entity
        void resolveEntityState ();

        // updates the entites location properties
        void entityMovementUpdate ();

};

class EntityManager {

    private:

        // properties
        Enigma* enigma;
        Player* player;
        Ghost* ghosts[4];
        int frame, playerMove;

        // playspace instance
        PlaySpace *play_space;

        // increases a given number with respect to
        // it's ghost number
        int incByGN (const int number, const int ghostNumber);

        // these functions contain the animation information
        // for all the active entities (they will be defined
        // at the bottom of the cpp file for readability)
      
        // supplies the enigma with their animations
        void supplyEnigmaAnimations ();
        // supplies the player with their animations
        void supplyPlayerAnimations ();
        // supplies each ghost with their animations
        void supplyGhostAnimations (const int gN);
        // this function calls the above functions
        void supplyEntityAnimations ();

        // this function generates the targeting for
        // the ghost path seeking
        Location genGhostTarget (const int ghost_number, string ghost_state);

    public:

        // constructor
        EntityManager (const int game_mode);

        // a function used to take in user input
        void updateInput(const int code);

        // preforms the nessary updates to the game's active entities
        void updateEntities();

        // renders the game's active entities
        void renderEntities();

};

#endif