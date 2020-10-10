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
// import path manager file
#include "../header_files/path_manager.h"
// import info bar manager file
#include "../header_files/info_bar_manager.h"

using namespace std;

#ifndef entity_manager_H
#define entity_manager_H

// is the abstract class which all higher order entities inherit
class Entity {

    private:

        // properties
        AnimationHandler* animation_handler;

    public:
        // properties that need to stay public for the inherited classes
        // general variables to run the basic animation / movement
        // and rendering of any entity
        string state;
        Location entity_location, spawn;
        int propulsion, direction;
        bool dead, change;

        // loads the animations of the entity
        void loadAnimations(pair < vector < pair < string, Animation* > >, int > loaded_animations);

        // the basic initialisation required by any form of entity
        void basicEntityInitialisation (const int gamemode, Location spawn);

        // changes the current location of the entity
        void changeCurrentLocation (const int x, const int y);

        // returns the current location of the entity
        Location getCurrentLocation ();
        
        // changes the current state of the entity
        void changeCurrentState (string str);

        // returns the current state of the entity
        string getCurrentState ();

        // decides the next move that will be taken by the
        // entity
        virtual void resolveEntityState (const int direction = 0) = 0;

        // updates the entites location properties
        virtual void entityMovementUpdate () = 0;

        // updates the entites animation settings
        void entityAnimationUpdate ();


        // runs the rendering process of the entity
        void entityRender ();

        // sets the dead bool to given state
        void setDeadState (bool state);

        // returns the state of the dead bool property
        bool isDead ();

        // respawns the entity at it's spawn
        void respawn ();

        // transitions the entity into the death state
        virtual void die () = 0;

};

class Player : public Entity {
        
        // properties
        PlaySpace *play_space; 

    public:

        // constructor
        Player (const int game_mode, Location spawn);

        // resolves the players state
        void resolveEntityState(const int direction = 0);

        // updates the entites location properties
        void entityMovementUpdate ();

        // transitions the player into the death state
        void die ();

};

class Ghost : public Entity {

    private:
        // properties
        int ghost_number;
        bool scared;
        PlaySpace *play_space; 

    public:


        // constructor
        Ghost (const int gamemode, const int ghost_number, Location spawn);

        // decides the next move that will be taken
        // by the entity
        void resolveEntityState (const int direction = 0);

        // updates the entites location properties
        void entityMovementUpdate ();

        // transitions the ghost into the death state
        void die ();

        // changes the value of the ghosts scared flag
        void setScared (bool state);

};

class EntityManager {

    private:

        // properties
        Player* player;
        Ghost* ghosts[4];
        int frame, movement_frame, animation_frame, player_move, lives = 3;
        const int respawn_tick_duration = 500, invulnrability_tick_duration = 2000;
        bool player_invulnrable;
        Uint32 tick_cntr, invulnrability_over, player_respawn, blinky_respawn, pinky_respawn, inky_respawn, clyde_respawn;
        
        //info bar properties
        bool ghost_eaten, pellet_eaten, power_eaten;
        InfoBarManager *info_bar = nullptr;
        const int score_pellet = 100, score_ghost = 1000, score_power = 500;
        int player_score = 0;

        // playspace instance
        PlaySpace *play_space = nullptr;

        // path manager instance
        PathManager *path_manager = nullptr;

        // increases a given number with respect to
        // it's ghost number
        int incByGN (const int number, const int ghostNumber);

        // these functions contain the animation information
        // for all the active entities (they will be defined
        // at the bottom of the cpp file for readability)
      
        // supplies the player with their animations
        void supplyPlayerAnimations ();
        // supplies each ghost with their animations
        void supplyGhostAnimations (const int gN);
        // this function calls the above functions
        void supplyEntityAnimations ();

        // converts a locatition made to work with the entity
        // manager into one that can work the playspace
        Location convertLocationToMap (Location entity_location);

        // this function generates the targeting for
        // the ghost path seeking
        Location genGhostTarget (const int ghost_number);

        // adjusts the score depending on how far into
        // the game the score was obtained
        double scaleScore (const int score);

    public:

        // constructor
        EntityManager (const int game_mode, const int segments_wide, const int segments_tall);

        // a function used to take in user input
        void updateInput(const int code);

        // preforms the nessary updates to the game's active entities
        int updateEntities();

        // renders the game's active entities
        void renderEntities();

};

#endif