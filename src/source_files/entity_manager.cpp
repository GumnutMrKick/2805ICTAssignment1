// esential includes
#include <stdio.h>
#include <string>
#include <math.h>
#include <ctime>
#include <utility>

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
    this->frame = 0;
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

void Entity::updateAnimationHandler (string state) {

    this->animation_handler->update(state);

}

// runs the rendering process of the entity
void Entity::basicEntityRender() {

    this->animation_handler->render(this->entity_location.x, this->entity_location.y);

}

// constructor
Enigma::Enigma (const int gamemode) {

    this->run = false;
    this->state = "run";

    // initialise basic components
    this->basicEntityInitialisation(gamemode, -16,  80, 104);

}

void Enigma::setRun(const bool state) {

    this->run = state;

} 

void Enigma::entityUpdate (string state) {

    if (!this->run) {

        if ((this->frame % this->animation_frame) == 0) {

            this->updateAnimationHandler(this->state);

        }

        if ((this->frame % this->movement_frame) == 0) {
            
            Location current_location = this->getCurrentLocation();
            this->changeCurrentLocation((current_location.x + this->propulsion), current_location.y);

        }

    } else if (this->frame == 3600) {

        this->run = true;
        this->frame = 0;

    }

}

// constructor
Player::Player () {


    
}

// constructor
Ghost::Ghost () {



}

// constructor
EntityManager::EntityManager (const int game_mode) {

    // initialise the display manager holder for the Animation class
    Animation::getDisplayManager();
    Entity::frame = 0;


    this->enigma = new Enigma(game_mode);

    cout << "hello";

    
}


// preforms the nessary updates to the game's active entities
void EntityManager::updateEntities() {



    this->enigma->entityUpdate("hi");

}

// renders the game's active entities
void EntityManager::renderEntities() {

    this->enigma->basicEntityRender();

}








// these functions contain the animation information
// for all the active entities (they will be defined
// at the bottom of the cpp file for readability)
void EntityManager::supplyEnigmaAnimations () {

    // initialise the animation holder
    pair < string, Animation* > animation;
    // initialise sprite if holder
    int *sprite_ids;

    // initialise the animations variable
    pair < vector < pair < string, Animation* > >, int > enigma_animations;

    // set number of animations
    enigma_animations.second = 1;

    // create Animations

    // create animation 1 - run
    // set animation name
    animation.first = "run";
    // create the sprite_ids array
    sprite_ids = (int[2]) {116, 117};
    // create Animation object
    animation.second = new Animation(sprite_ids, 2);
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