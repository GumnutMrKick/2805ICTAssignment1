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

    cout << "animations " << loaded_animations.first[0].first << endl;
    // initiailise the animation handler for the basic entity
    this->animation_handler = new AnimationHandler(loaded_animations.first, loaded_animations.second);

}

// the basic initialisation required by any form of entity
void Entity::basicEntityInitialisation (const int gamemode, const int x, const int y, const int propulsion) {

    // initialise the entities location
    this->entity_location.x = x;
    this->entity_location.y = y;
 
    // initialise the frame counter and animation timer 
    this->animation_frame = 30;

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
    this->basicEntityInitialisation(gamemode, -16,  80, 104);

}

// sets the state of the run bool variable
void Enigma::setRun(const bool state) {

    this->run = state;

}

// decides the next move that will be taken
// by the entity
string Enigma::resolveEntityState() {

    return "run";

}

// updates the entites location properties
void Enigma::entityMovementUpdate () {

    if (!this->run) {

        Location current_location = this->getCurrentLocation();
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
string Player::resolveEntityState() {



}

// updates the entites location properties
void Player::entityMovementUpdate() {



}

// constructor
Ghost::Ghost (const int game_mode, string ghost_name) {



}

// decides the next move that will be taken
// by the entity
string Ghost::resolveEntityState() {



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
    this->ghosts[0] = new Ghost(game_mode, "pinky");
    // inky
    this->ghosts[0] = new Ghost(game_mode, "inky");
    // clyde
    this->ghosts[0] = new Ghost(game_mode, "clyde");

}


// preforms the nessary updates to the game's active entities
void EntityManager::updateEntities() {


    // get the player the user inputs

    // resolve updates
    this->enigma->resolveEntityState();
    this->player->resolveEntityState();
    this->ghosts[0]->resolveEntityState();
    this->ghosts[1]->resolveEntityState();
    this->ghosts[2]->resolveEntityState();
    this->ghosts[3]->resolveEntityState();

    //deliver updates
    this->enigma->entityUpdate(this->frame);
    this->player->entityUpdate(this->frame);
    this->ghosts[0]->entityUpdate(this->frame);
    this->ghosts[1]->entityUpdate(this->frame);
    this->ghosts[2]->entityUpdate(this->frame);
    this->ghosts[3]->entityUpdate(this->frame);

    if (this->frame == 60) {

        this->frame = 0;

    } else {

        this->frame++;

    }

}

// renders the game's active entities
void EntityManager::renderEntities() {

    this->enigma->entityRender();
    this->player->entityRender();
    this->ghosts[0]->entityRender();
    this->ghosts[1]->entityRender();
    this->ghosts[2]->entityRender();
    this->ghosts[3]->entityRender();

}








// these functions contain the animation information
// for all the active entities (they will be defined
// at the bottom of the cpp file for readability)
void EntityManager::supplyEnigmaAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    
    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > enigma_animations;

    // set number of animations
    enigma_animations.second = 1;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "run";
    // create the sprite_ids array
    int* sprite_ids_1 = new int[2] {116, 117};
    // create Animation object
    animation.second = new Animation(sprite_ids_1, 2);
    // push back animation 1 - run
    enigma_animations.first.push_back(animation);

    this->enigma->loadAnimations(enigma_animations);

} 

void EntityManager::supplyPlayerAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > player_animations;

    // set number of animations
    // player_animations.second = ;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "";
    // create the sprite_ids array
    // sprite_ids = (int[]) {};
    // create Animation object
    // animation.second = new Animation(sprite_ids, );
    // push back animation 1 - run
    // player_animations.first.push_back(animation);

    // this->player->loadAnimations(player_animations);

} 

void EntityManager::supplyBlinkyAnimations () {
    
    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > blinky_animations;

    // set number of animations
    // blinky_animations.second = ;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "";
    // create the sprite_ids array
    // sprite_ids = (int[]) {};
    // create Animation object
    // animation.second = new Animation(sprite_ids, );
    // push back animation 1 - run
    // blinky_animations.first.push_back(animation);

    // this->ghosts[0]->loadAnimations(blinky_animations);

} 

void EntityManager::supplyPinkyAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > pinky_animations;

    // set number of animations
    // pinky_animations.second = ;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "";
    // create the sprite_ids array
    // sprite_ids = (int[]) {};
    // create Animation object
    // animation.second = new Animation(sprite_ids, );
    // push back animation 1 - run
    // pinky_animations.first.push_back(animation);

    // this->ghosts[1]->loadAnimations(pinky_animations);

} 

void EntityManager::supplyInkyAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > inky_animations;

    // set number of animations
    // inky_animations.second = ;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "";
    // create the sprite_ids array
    // sprite_ids = (int[]) {};
    // create Animation object
    // animation.second = new Animation(sprite_ids, );
    // push back animation 1 - run
    // inky_animations.first.push_back(animation);

    // this->ghosts[2]->loadAnimations(inky_animations);

} 

void EntityManager::supplyClydeAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > clyde_animations;

    // set number of animations
    // clyde_animations.second = ;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "";
    // create the sprite_ids array
    // sprite_ids = (int[]) {};
    // create Animation object
    // animation.second = new Animation(sprite_ids, );
    // push back animation 1 - run
    // clyde_animations.first.push_back(animation);

    // this->ghosts[3]->loadAnimations(clyde_animations);

} 

// this function calls the above functions
void EntityManager::supplyEntityAnimations () {

    this->supplyEnigmaAnimations();
    this->supplyPlayerAnimations();
    this->supplyBlinkyAnimations();
    this->supplyPinkyAnimations();
    this->supplyInkyAnimations();
    this->supplyClydeAnimations();

}