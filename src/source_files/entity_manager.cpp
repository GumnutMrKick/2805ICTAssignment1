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

// include self
#include "../header_files/entity_manager.h"

// loads the animations of the entity
void Entity::loadAnimations(pair < vector < pair < string, Animation* > > , int > loaded_animations) {

    // initiailise the animation handler for the basic entity
    this->animation_handler = new AnimationHandler(loaded_animations.first, loaded_animations.second);

}

// the basic initialisation required by any form of entity
void Entity::basicEntityInitialisation (const int game_mode, Location spawn) {

    // initialise the entities location
    this->spawn = spawn;
    this->entity_location.x = spawn.x;
    this->entity_location.y = spawn.y;
 
    // set propulsion
    this->propulsion = ((game_mode < 2) ?  16 : 1);

    // set entity direction to up for initialisation
    this->direction = 0;

    // initialise death flag
    this->dead = false;

}

// changes the current location of the entity
void Entity::changeCurrentLocation (const int x, const int y) {

    this->entity_location.x = x;
    this->entity_location.y = y;

}

// returns the current location of the entity
Location Entity::getCurrentLocation () {

    return this->entity_location;

}

// changes the current state of the entity
void Entity::changeCurrentState (string str) {

    this->state = str;

}

// returns the current state of the entity
string Entity::getCurrentState () {

    return this->state;

}

void Entity::entityAnimationUpdate () {

    this->animation_handler->update(this->state);

}

// runs the rendering process of the entity
void Entity::entityRender() {

    this->animation_handler->render(this->entity_location.x, this->entity_location.y);

}

// sets the dead bool to given state
void Entity::setDeadState (bool state) {

    this->dead = state;

}

// returns the state of the dead bool property
bool Entity::isDead () {

    return this->dead;

}

//respawns the entity at it's spawn
void Entity::respawn () {

    this->setDeadState(false);
    this->changeCurrentLocation(this->spawn.x, this->spawn.y);
    this->direction = 0;
    this->changeCurrentState("up");

}

// constructor
Player::Player (const int gamemode, Location spawn) {

    // get the playspace instance
    this->play_space = PlaySpace::getInstance();

    // initialise basic components
    this->basicEntityInitialisation(gamemode, spawn);
    
}

// decides the statenext move that will be taken
// by the entity
void Player::resolveEntityState(const int direction) {

    // if the given direction is different
    if ((direction != -1) && (this->direction != direction)) {

        this->change = true;
        this->direction = direction;

    }

}

// updates the entites location properties
void Player::entityMovementUpdate() {

    // if the player isn't dead try to move
    // the character in it's desired direction
    if (!this->dead) {

        string animation_state;
        int x_change, y_change;

        // get current map coords
        int map_x, map_y;

        map_x = (int) ((this->entity_location.x - (this->entity_location.x % 16)) / 16);
        map_y = (int) ((this->entity_location.y - (this->entity_location.y % 16)) / 16);

        switch(this->direction) {

            case (0) :

                x_change = 0;
                y_change = -1;
                animation_state = "up";

            break;

            case (1) :

                x_change = 1;
                y_change = 0;
                animation_state = "right";

            break;

            case (2) :

                x_change = 0;
                y_change = 1;
                animation_state = "down";

            break;

            case (3) :

                x_change = -1;
                y_change = 0;
                animation_state = "left";

            break;

            default :

                x_change = 0;
                y_change = 0;
                animation_state = "nothing";

        }
        
        // initialise new value holders
        int new_x = this->entity_location.x;
        int new_y = this->entity_location.y;

        // set the new state value
        this->state = animation_state;

        if (!this->play_space->isWall((map_x + x_change), (map_y + y_change))) {

            if (this->change) {

                new_x -= (this->entity_location.x % 16);
                new_y -= (this->entity_location.y % 16);

                this->entityAnimationUpdate();
                this->change = false;

            }

            new_x += (x_change * this->propulsion);
            new_y += (y_change * this->propulsion);

            this->changeCurrentLocation(new_x, new_y);

        }

    }

}

// transitions the player into the death state
void Player::die () {

    this->setDeadState(true);
    this->state = "death";
    this->entityAnimationUpdate();

}

// constructor
Ghost::Ghost (const int gamemode, const int ghost_number, Location ghost_spawn) {

    // get the playspace instance
    this->play_space = PlaySpace::getInstance();

    // initailise the properties
    this->ghost_number = ghost_number;

    // initialise basic components
    this->basicEntityInitialisation(gamemode, ghost_spawn);

    // intialise scared flag
    this->scared = false;

}

// decides the next move that will be taken
// by the entity
void Ghost::resolveEntityState(const int direction) {

    // if the given direction is the same leave
    if (this->direction == direction) return;

    this->change = true;
    this->direction = direction;

}

// updates the entites location properties
void Ghost::entityMovementUpdate () {

    string animation_state;
    int x_change, y_change;

    // get current map coords
    int map_x, map_y;

    map_x = (int) ((this->entity_location.x - (this->entity_location.x % 16)) / 16);
    map_y = (int) ((this->entity_location.y - (this->entity_location.y % 16)) / 16);

    switch(this->direction) {

        case (0) :

            x_change = 0;
            y_change = -1;
            animation_state = "up";

        break;

        case (1) :

            x_change = 1;
            y_change = 0;
            animation_state = "right";

        break;

        case (2) :

            x_change = 0;
            y_change = 1;
            animation_state = "down";

        break;

        case (3) :

            x_change = -1;
            y_change = 0;
            animation_state = "left";

        break;

    }
    
    // initialise new value holders
    int new_x = this->entity_location.x;
    int new_y = this->entity_location.y;

    // set the new state value
    // if dead add the dead prefix
    if (this->isDead()) {

        string add_back = "dead";
        add_back = add_back.append(animation_state);
        animation_state = add_back;

    }    
    
    // if scared change state to scared, else set calculated state
    this->state = (((!this->isDead()) && this->scared) ? "scared" : animation_state);

    if (!this->play_space->isWall((map_x + x_change), (map_y + y_change))) {

        if (this->change) {

            new_x -= (this->entity_location.x % 16);
            new_y -= (this->entity_location.y % 16);

            this->entityAnimationUpdate();

            this->change = false;

        }

        new_x += (x_change * this->propulsion);
        new_y += (y_change * this->propulsion);

        this->changeCurrentLocation(new_x, new_y);

    }

}

// transitions the ghost into the death state
void Ghost::die () {

    this->setDeadState(true);
    this->state = "deadup";
    this->entityAnimationUpdate();

}

// changes the value of the ghosts scared flag
void Ghost::setScared (bool state) {

    this->scared = state;
    this->state = ((state) ? "scared" : "up");
    this->entityAnimationUpdate();

}

// converts a locatition made to work with the entity
// manager into one that can work the playspace
Location EntityManager::convertLocationToMap (Location entity_location) {

    entity_location.x = ((entity_location.x - (entity_location.x % 16)) / 16);
    entity_location.y = ((entity_location.y - (entity_location.y % 16)) / 16);
   
    return entity_location;

}

// this function generates the targeting for
// the ghost path seeking
Location EntityManager::genGhostTarget (const int ghost_number) {

    // get the location of pacman
    Location target = this->convertLocationToMap(this->player->getCurrentLocation());

    int closest = -1;

    switch (ghost_number) {

        case (0) :
        break;

        case (1) :
            
            for (int y = 0; y <= target.y; y++) {

                if (!this->play_space->isWall(target.x, y)) closest = y;

                if ((((target.y - y) <=5) && (closest != -1))) break;

            }

            target.x = closest;

        break;

        case (2) :

            for (int x = 0; x <= target.x; x++) {

                if (!this->play_space->isWall(x, target.y)) closest = x;

                if ((((target.x - x) <=5) && (closest != -1))) break;

            }

            target.y = closest;

        break;

        case (3) :

            target = this->convertLocationToMap(this->play_space->giveRanEntitySpawn("player"));

        break;

    };

    return target;

}

// adjusts the score depending on how far into
// the game the score was obtained
double EntityManager::scaleScore (const int score) {

    // generate the scaler, it's equation is to find the ammount of time that has passed
    // since game start as a percentage of 5 minutes, this will then
    // be taken away from 1 giving the scaler
    float x, score_scaler; 
    x = (float) score;
    score_scaler = (float)  ((float) 1 - (float) this->tick_cntr / 18000);
    // don't let it go below .5
    if (score_scaler < 0.5) score_scaler = 0.5;

    return ((int) (score * score_scaler));

}

// constructor
EntityManager::EntityManager (const int game_mode, const int segments_wide, const int segments_tall) {


    // ----- initialise the entity manager properties and flags -----
    // initialise the display manager instance
    // for the Animation class
    Animation::getDisplayManager();
    
    // get the playspace instance
    this->play_space = PlaySpace::getInstance();

    //initialise the path manager instance holder
    this->path_manager = new PathManager(this->play_space->width, this->play_space->height);

    // initialise the tick counter
    this->tick_cntr = 0;

    // initialise event timers, and timer 
    this->frame = 0;
    this->animation_frame = 10;
    this->movement_frame = ((game_mode < 2) ?  40 : 4);
    this->pellet_eaten = false;
    this->ghost_eaten = false;
    this->power_eaten = false;

    // initialise cooldowns
    this->player_invulnrable = false;
    this->invulnrability_over = 0;
    this->player_respawn = 0;
    this->blinky_respawn = 0;
    this->pinky_respawn = 0;
    this->inky_respawn = 0;
    this->clyde_respawn = 0;

    // ----- initialise the active entities -----
    // player
    this->player = new Player(game_mode, this->play_space->giveRanEntitySpawn("player"));
    // ghosts
    // blinky
    this->ghosts[0] = new Ghost(game_mode, 0, this->play_space->giveRanEntitySpawn("ghost"));
    // pinky
    this->ghosts[1] = new Ghost(game_mode, 1, this->play_space->giveRanEntitySpawn("ghost"));
    // inky
    this->ghosts[2] = new Ghost(game_mode, 2, this->play_space->giveRanEntitySpawn("ghost"));
    // clyde
    this->ghosts[3] = new Ghost(game_mode, 3, this->play_space->giveRanEntitySpawn("ghost"));

    // give entities their animations
    this->supplyEntityAnimations();

    // set the initial animations
    this->player->state = "nothing";
    this->ghosts[0]->state = "up";
    this->ghosts[1]->state = "up";
    this->ghosts[2]->state = "up";
    this->ghosts[3]->state = "up";

    // start the initial animations
    this->player->entityAnimationUpdate();
    this->ghosts[0]->entityAnimationUpdate();
    this->ghosts[1]->entityAnimationUpdate();
    this->ghosts[2]->entityAnimationUpdate();
    this->ghosts[3]->entityAnimationUpdate();

    // ----- info bar manager initialisation -----
    this->info_bar = new InfoBarManager(segments_wide, segments_tall, ((1 * 16) * 11));
    cout << "info bar manager : " << ((this->info_bar) ? "OK" : "error") << endl;

}

// a function used to take in user input
void EntityManager::updateInput (const int code) {

    if ((code >= 0) && (code <= 3))this->player_move = code;

}

// preforms the nessary updates to the game's active entities
int EntityManager::updateEntities() {

    if (this->frame != 0) {

        // time for a movement update
        if ((frame % this->movement_frame) == 0) {

            // ----- check cool downs -----
            // is invul over
            if ((this->player_invulnrable) && (this->tick_cntr >= this->invulnrability_over)) {
                
                this->player_invulnrable = false;

                // remove scared flag for ghosts
                for (int x = 0; x < 4; x++) this->ghosts[x]->setScared(false);

            }

            // should the player be respawned
            if ((this->player->isDead()) && (this->tick_cntr >= this->player_respawn)) {

                if (this->lives != 0) {

                    this->player->respawn();
                    this->lives--;

                } else {
                    
                    return -1;
                    
                }
                
            }

            // should blinky be respawned
            if ((this->ghosts[0]->isDead()) && (this->tick_cntr >= this->blinky_respawn)) this->ghosts[0]->respawn();
            
            // should pinky be respawned
            if ((this->ghosts[1]->isDead()) && (this->tick_cntr >= this->pinky_respawn)) this->ghosts[1]->respawn();
            
            // should inky be respawned
            if ((this->ghosts[2]->isDead()) && (this->tick_cntr >= this->inky_respawn)) this->ghosts[2]->respawn();
            
            // should clyde be respawned
            if ((this->ghosts[3]->isDead()) && (this->tick_cntr >= this->clyde_respawn)) this->ghosts[3]->respawn();

            // ----- resolve entity updates and run them -----
            // resolve player update
            if (!this->player->isDead()) {

                this->player->resolveEntityState(this->player_move);
                this->player->entityMovementUpdate();

            }

            // resolve blinky update
            if (this-ghosts[0]->isDead()){
            
                this->ghosts[0]->resolveEntityState(
                    this->path_manager->randomlyChooseNextMove(
                        this->convertLocationToMap(this->ghosts[0]->getCurrentLocation()),
                        this->ghosts[0]->direction
                    )
                );

            } else {

                this->ghosts[0]->resolveEntityState(
                    this->path_manager->calculateNextMove(
                        this->convertLocationToMap(this->ghosts[0]->getCurrentLocation()),
                        this->genGhostTarget(0),
                        this->ghosts[0]->direction
                    )
                );
            
            }
            this->ghosts[0]->entityMovementUpdate();

            // resolve pinky update
            this->ghosts[1]->resolveEntityState(
                this->path_manager->randomlyChooseNextMove(
                    this->convertLocationToMap(this->ghosts[1]->getCurrentLocation()),
                    this->ghosts[1]->direction
                )
            );
            this->ghosts[1]->entityMovementUpdate();

            // resolve inky update
            this->ghosts[2]->resolveEntityState(
                this->path_manager->randomlyChooseNextMove(
                    this->convertLocationToMap(this->ghosts[2]->getCurrentLocation()),
                    this->ghosts[2]->direction
                )
            );
            this->ghosts[2]->entityMovementUpdate();

            // resolve clyde update
            this->ghosts[3]->resolveEntityState(
                this->path_manager->randomlyChooseNextMove(
                    this->convertLocationToMap(this->ghosts[3]->getCurrentLocation()),
                    this->ghosts[3]->direction
                )
            );
            this->ghosts[3]->entityMovementUpdate();

            // ----- calculate collisions -----
            if (!this->player->isDead()) {
            
                Location map_pacman = this->convertLocationToMap(this->player->getCurrentLocation());
                
                // pellets
                this->pellet_eaten = this->play_space->checkForPellet(map_pacman.x, map_pacman.y);

                // power pellets
                this->power_eaten = this->play_space->checkForPowerPellet(map_pacman.x, map_pacman.y);

                // apply powerup if applicable
                if (this->power_eaten) {

                    this->player_invulnrable = true;
                    this->invulnrability_over = (this->tick_cntr + this->invulnrability_tick_duration);
                    
                    // set scared flag for ghosts
                    for (int x = 0; x < 4; x++) this->ghosts[x]->setScared(true);

                }

                // ghosts
                for (int x = 0; x < 4; x++) {

                    if (!this->ghosts[x]->isDead()) {

                        Location map_ghost = this->convertLocationToMap(this->ghosts[x]->getCurrentLocation());

                        // if a collision has been made with pacman
                        if ((map_pacman.x == map_ghost.x) && (map_pacman.y == map_ghost.y)) {

                            // if the player is invulnrable kill the ghost
                            if (this->player_invulnrable) {

                                // kill the ghost
                                this->ghosts[x]->die();

                                // set the appropriate respawn timer
                                if (x == 0) this->blinky_respawn = (this->tick_cntr + this->respawn_tick_duration);
                                if (x == 1) this->pinky_respawn = (this->tick_cntr + this->respawn_tick_duration);
                                if (x == 2) this->inky_respawn = (this->tick_cntr + this->respawn_tick_duration);
                                if (x == 3) this->clyde_respawn = (this->tick_cntr + this->respawn_tick_duration);

                                this->ghost_eaten = true;

                            // otherwise kill the player 
                            } else {

                                this->player->die();
                                this->player_respawn = (this->tick_cntr + this->respawn_tick_duration);

                            }

                        }

                    }

                }

            }

        }

        // time for an animation update
        if ((this->frame % this->animation_frame) == 0) {

            // prompt entity animation updates
            this->player->entityAnimationUpdate();
            this->ghosts[0]->entityAnimationUpdate();
            this->ghosts[1]->entityAnimationUpdate();
            this->ghosts[2]->entityAnimationUpdate();
            this->ghosts[3]->entityAnimationUpdate();

        }

    }

    // ----- update and queue render of info bar -----
    if (this->pellet_eaten) this->player_score += (int) this->scaleScore(this->score_pellet);
    if (this->ghost_eaten) this->player_score += (int) this->scaleScore(this->score_ghost);
    if (this->power_eaten) this->player_score += (int) this->scaleScore(this->score_power);

    // get the player's state for the info bar
    int info_bar_player_state;

    if (this->player->isDead()) {

        info_bar_player_state = 3;

    } else info_bar_player_state = ((player_invulnrable)? 2 : 1);

    //update and render
    this->info_bar->updateInfoBar(info_bar_player_state, this->player_score);
    this->info_bar->renderInfoBar();

    // ----- update frame and tick counters -----
    this->tick_cntr++;

    if (this->frame == 60) {

        this->frame = 0;

    } else {

        this->frame++;

    }

    // ----- reset the game enviroment movement and utility variables -----
    this->pellet_eaten = false;
    this->ghost_eaten = false;
    this->power_eaten = false;

    return 0;

}

// renders the game's active entities
void EntityManager::renderEntities() {

    this->player->entityRender();
    this->ghosts[0]->entityRender();
    this->ghosts[1]->entityRender();
    this->ghosts[2]->entityRender();
    this->ghosts[3]->entityRender();

}

// these functions contain the animation information
// for all the active entities (they will be defined
// at the bottom of the cpp file for readability)
void EntityManager::supplyPlayerAnimations () {

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > player_animations;

    // set number of animations
    player_animations.second = 6;

    // create Animations

    // create animation 1 - nothing
    // initialise the animation holder
    pair < string, Animation* > nothing_animation;
    // set animation name
    nothing_animation.first = "nothing";
    // create the sprite_ids array
    int* nothing_sprite_ids = new int[2] {102, 102};
    // create Animation object
    nothing_animation.second = new Animation(nothing_sprite_ids, 2);
    // push back animation 1 - run
    player_animations.first.push_back(nothing_animation);

    // create animation 2 - up
    // initialise the animation holder
    pair < string, Animation* > up_animation;
    // set animation name
    up_animation.first = "up";
    // create the sprite_ids array
    int* up_sprite_ids = new int[4] {102, 103, 104, 103};
    // create Animation object
    up_animation.second = new Animation(up_sprite_ids, 4);
    // push back animation 2 - up
    player_animations.first.push_back(up_animation);

    // create animation 3 - right
    // initialise the animation holder
    pair < string, Animation* > right_animation;
    // set animation name
    right_animation.first = "right";
    // create the sprite_ids array
    int* right_sprite_ids = new int[4] {102, 105, 106, 105};
    // create Animation object
    right_animation.second = new Animation(right_sprite_ids, 4);
    // push back animation 3 - right
    player_animations.first.push_back(right_animation);

    // create animation 4 - down
    // initialise the animation holder
    pair < string, Animation* > down_animation;
    // set animation name
    down_animation.first = "down";
    // create the sprite_ids array
    int* down_sprite_ids = new int[4] {102, 107, 108, 107};
    // create Animation object
    down_animation.second = new Animation(down_sprite_ids, 4);
    // push back animation 4 - down
    player_animations.first.push_back(down_animation);

    // create animation 5 - left
    // initialise the animation holder
    pair < string, Animation* > left_animation;
    // set animation name
    left_animation.first = "left";
    // create the sprite_ids array
    int* left_sprite_ids = new int[4] {102, 109, 110, 109};
    // create Animation object
    left_animation.second = new Animation(left_sprite_ids, 4);
    // push back animation 5 - left
    player_animations.first.push_back(left_animation);

    // create animation 6 - death
    // initialise the animation holder
    pair < string, Animation* > death_animation;
    // set animation name
    death_animation.first = "death";
    // create the sprite_ids array
    int* death_sprite_ids = new int[6] {102, 111, 112, 113, 114, 115};
    // create Animation object
    death_animation.second = new Animation(death_sprite_ids, 6, 2);
    // push back animation 6 - death
    player_animations.first.push_back(death_animation);

    // load all of the animations into the handler
    this->player->loadAnimations(player_animations);

}

int EntityManager::incByGN (const int number, const int ghostNumber) {

    return (number + (8 * ghostNumber));

}

// supplies each ghost with their animations
void EntityManager::supplyGhostAnimations (const int gN) {

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > ghost_animations;

    // set number of animations
    ghost_animations.second = 9;

    // create Animations

    // create animation 1 - up
    // initialise the animation holder
    pair < string, Animation* > up_animation;
    // set animation name
    up_animation.first = "up";
    // create the sprite_ids array
    int* up_sprite_ids = new int[2] {incByGN(62, gN), incByGN(63, gN)};
    // create Animation object
    up_animation.second = new Animation(up_sprite_ids, 2);
    // push back animation 1 - up
    ghost_animations.first.push_back(up_animation);

    // create animation 2 - right
    // initialise the animation holder
    pair < string, Animation* > right_animation;
    // set animation name
    right_animation.first = "right";
    // create the sprite_ids array
    int* right_sprite_ids = new int[2] {incByGN(64, gN), incByGN(65, gN)};
    // create Animation object
    right_animation.second = new Animation(right_sprite_ids, 2);
    // push back animation 2 - right
    ghost_animations.first.push_back(right_animation);

    // create animation 3 - down
    // initialise the animation holder
    pair < string, Animation* > down_animation;
    // set animation name
    down_animation.first = "down";
    // create the sprite_ids array
    int* down_sprite_ids = new int[2] {incByGN(66, gN), incByGN(67, gN)};
    // create Animation object
    down_animation.second = new Animation(down_sprite_ids, 2);
    // push back animation 3 - down
    ghost_animations.first.push_back(down_animation);

    // create animation 4 - left
    // initialise the animation holder
    pair < string, Animation* > left_animation;
    // set animation name
    left_animation.first = "left";
    // create the sprite_ids array
    int* left_sprite_ids = new int[2] {incByGN(68, gN), incByGN(69, gN)};
    // create Animation object
    left_animation.second = new Animation(left_sprite_ids, 2);
    // push back animation 4 - left
    ghost_animations.first.push_back(left_animation);

    // create animation 5 - scared
    // initialise the animation holder
    pair < string, Animation* > scared_animation;
    // set animation name
    scared_animation.first = "scared";
    // create the sprite_ids array
    int* scared_sprite_ids = new int[4] {94, 95, 96, 97};
    // create Animation object
    scared_animation.second = new Animation(scared_sprite_ids, 4);
    // push back animation 5 - scared
    ghost_animations.first.push_back(scared_animation);

    // create animation 6 - deadup
    // initialise the animation holder
    pair < string, Animation* > deadup_animation;
    // set animation name
    deadup_animation.first = "deadup";
    // create the sprite_ids array
    int* deadup_sprite_ids = new int[2] {98, 98};
    // create Animation object
    deadup_animation.second = new Animation(deadup_sprite_ids, 2);
    // push back animation 6 - deadup
    ghost_animations.first.push_back(deadup_animation);

    // create animation 7 - deadright
    // initialise the animation holder
    pair < string, Animation* > deadright_animation;
    // set animation name
    deadright_animation.first = "deadright";
    // create the sprite_ids array
    int* deadright_sprite_ids = new int[2] {99, 99};
    // create Animation object
    deadright_animation.second = new Animation(deadright_sprite_ids, 2);
    // push back animation 7 - deadright
    ghost_animations.first.push_back(deadright_animation);

    // create animation 8 - deaddown
    // initialise the animation holder
    pair < string, Animation* > deaddown_animation;
    // set animation name
    deaddown_animation.first = "deaddown";
    // create the sprite_ids array
    int* deaddown_sprite_ids = new int[2] {100, 100};
    // create Animation object
    deaddown_animation.second = new Animation(deaddown_sprite_ids, 2);
    // push back animation 8 - deaddown
    ghost_animations.first.push_back(deaddown_animation);
    
    // create animation 9 - deadleft
    // initialise the animation holder
    pair < string, Animation* > deadleft_animation;
    // set animation name
    deadleft_animation.first = "deadleft";
    // create the sprite_ids array
    int* deadleft_sprite_ids = new int[2] {101, 101};
    // create Animation object
    deadleft_animation.second = new Animation(deadleft_sprite_ids, 2);
    // push back animation 9 - deadleft
    ghost_animations.first.push_back(deadleft_animation);

    // load all of the animations into the handler
    this->ghosts[gN]->loadAnimations(ghost_animations);

}

// this function calls the above functions
void EntityManager::supplyEntityAnimations () {

    this->supplyPlayerAnimations();
    this->supplyGhostAnimations(0);
    this->supplyGhostAnimations(1);
    this->supplyGhostAnimations(2);
    this->supplyGhostAnimations(3);

}