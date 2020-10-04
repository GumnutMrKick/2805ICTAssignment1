// esential includes
#include <stdio.h>
#include <string>
#include <math.h>
#include <ctime>
#include <utility>
#include <vector>


// include my stuff
// import play space file
#include "../header_files/play_space.h"

using namespace std;

// include self
#include "../header_files/entity_manager.h"

// generates a valid version of the render task struct
Location generateLocationHolder(const int x, const int y) {

    Location loc;

    loc.x = x;
    loc.y = y;

    return loc;

}

// loads the animations of the entity
void Entity::loadAnimations(pair < vector < pair < string, Animation* > > , int > loaded_animations) {

    // initiailise the animation handler for the basic entity
    this->animation_handler = new AnimationHandler(loaded_animations.first, loaded_animations.second);

}

// the basic initialisation required by any form of entity
void Entity::basicEntityInitialisation (const int gamemode, const int x, const int y, const int propulsion) {

    // initialise the entities location
    this->entity_location.x = x;
    this->entity_location.y = y;
 
    // initialise the frame counter and animation timer 
    this->animation_frame = 10;

    // change movement frame based on gamemode
    this->movement_frame = ((gamemode < 2) ?  60 : 4);

    // set propulsion
    this->propulsion = propulsion;

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

// updates the entities properties
void Entity::entityUpdate (const int frame) {

    if ((frame % this->animation_frame) == 0) {

        this->entityAnimationUpdate(this->state);

    }

    if ((frame % this->movement_frame) == 0) {
        
        this->entityMovementUpdate();

    }

}

void Entity::entityAnimationUpdate (string state) {

    this->animation_handler->update(state);

}

// runs the rendering process of the entity
void Entity::entityRender() {

    this->animation_handler->render(this->entity_location.x, this->entity_location.y);

}

// constructor
Enigma::Enigma (const int gamemode) {

    this->run = false;
    this->state = "run";

    // initialise basic components
    this->basicEntityInitialisation(gamemode, -16,  80, 16);

}

// sets the state of the run bool variable
void Enigma::setRun(const bool state) {

    this->run = state;

}

// decides the next move that will be taken
// by the entity
void Enigma::resolveEntityState() {

    this->state = "run";

}

// updates the entites location properties
void Enigma::entityMovementUpdate () {

    Location current_location = this->getCurrentLocation();

    if ((!this->run) || !( true )) { //current_location.x <)) {

        this->changeCurrentLocation((current_location.x + this->propulsion), current_location.y);

    } else {

        Location current_location = this->getCurrentLocation();
        this->changeCurrentLocation(-16, current_location.y);

    }

}

// constructor
Player::Player (const int game_mode) {


    
}

// decides the next move that will be taken
// by the entity
void Player::resolveEntityState() {



}

// updates the entites location properties
void Player::entityMovementUpdate() {



}

// constructor
Ghost::Ghost (const int game_mode, string ghost_name) {



}

// decides the next move that will be taken
// by the entity
void Ghost::resolveEntityState() {



}

// updates the entites location properties
void Ghost::entityMovementUpdate () {



}

// constructor
EntityManager::EntityManager (const int game_mode) {

    // initialise the display manager holder for the Animation class
    Animation::getDisplayManager();
    // initialise the frame counter
    this->frame = 0;

    // initialise the active entities
    // enigma
    this->enigma = new Enigma(game_mode);
    // player
    this->player = new Player(game_mode);
    // ghosts
    // blinky
    this->ghosts[0] = new Ghost(game_mode, "blinky");
    // pinky
    this->ghosts[1] = new Ghost(game_mode, "pinky");
    // inky
    this->ghosts[2] = new Ghost(game_mode, "inky");
    // clyde
    this->ghosts[3] = new Ghost(game_mode, "clyde");

    this->supplyEntityAnimations();

}


// preforms the nessary updates to the game's active entities
void EntityManager::updateEntities() {



    // get player the user inputs




    // resolve updates
    this->enigma->resolveEntityState();
    this->player->resolveEntityState();
    this->ghosts[0]->resolveEntityState();
    this->ghosts[1]->resolveEntityState();
    this->ghosts[2]->resolveEntityState();
    this->ghosts[3]->resolveEntityState();


    //deliver updates
    this->enigma->entityUpdate(this->frame);
    // this->player->entityUpdate(this->frame);
    // this->ghosts[0]->entityUpdate(this->frame);
    // this->ghosts[1]->entityUpdate(this->frame);
    // this->ghosts[2]->entityUpdate(this->frame);
    // this->ghosts[3]->entityUpdate(this->frame);

    if (this->frame == 60) {

        this->frame = 0;

    } else {

        this->frame++;

    }

}

// renders the game's active entities
void EntityManager::renderEntities() {

    this->enigma->entityRender();
    //this->player->entityRender();
    //this->ghosts[0]->entityRender();
    //this->ghosts[1]->entityRender();
    //this->ghosts[2]->entityRender();
    //this->ghosts[3]->entityRender();

}

// these functions contain the animation information
// for all the active entities (they will be defined
// at the bottom of the cpp file for readability)
void EntityManager::supplyEnigmaAnimations () {
    
    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > enigma_animations;

    // set number of animations
    enigma_animations.second = 1;

    // create Animations

    // create animation 1 - run
    // initialise the animation holder
    pair < string, Animation* > run_animation;
    // set animation name
    run_animation.first = "run";
    // create the sprite_ids array
    int* sprite_ids_1 = new int[2] {116, 117};
    // create Animation object
    run_animation.second = new Animation(sprite_ids_1, 2);
    // push back animation 1 - run
    enigma_animations.first.push_back(run_animation);

    // load all of the animations into the handler
    this->enigma->loadAnimations(enigma_animations);

} 

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
    int* scared_sprite_ids = new int[4] {incByGN(94, gN), incByGN(95, gN), incByGN(96, gN), incByGN(97, gN)};
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
    int* deadup_sprite_ids = new int[2] {incByGN(98, gN), incByGN(98, gN)};
    // create Animation object
    deadup_animation.second = new Animation(deadup_sprite_ids, 2);
    // push back animation 6 - deadup
    ghost_animations.first.push_back(deadup_animation);

    // create animation 7 - deadright
    // initialise the animation holder
    pair < string, Animation* > deadright_animation;
    // set animation name
    deadup_animation.first = "deadright";
    // create the sprite_ids array
    int* deadright_sprite_ids = new int[2] {incByGN(99, gN), incByGN(99, gN)};
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
    int* deaddown_sprite_ids = new int[2] {incByGN(100, gN), incByGN(100, gN)};
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
    int* deadleft_sprite_ids = new int[2] {incByGN(101, gN), incByGN(101, gN)};
    // create Animation object
    deadup_animation.second = new Animation(deadleft_sprite_ids, 2);
    // push back animation 9 - deadleft
    ghost_animations.first.push_back(deadleft_animation);

    // load all of the animations into the handler
    this->ghosts[gN]->loadAnimations(ghost_animations);

}

// this function calls the above functions
void EntityManager::supplyEntityAnimations () {

    this->supplyEnigmaAnimations();
    this->supplyPlayerAnimations();
    this->supplyGhostAnimations(0);
    this->supplyGhostAnimations(1);
    this->supplyGhostAnimations(2);
    this->supplyGhostAnimations(3);

}