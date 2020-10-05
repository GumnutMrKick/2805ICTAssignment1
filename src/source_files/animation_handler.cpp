// esential includes
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

// include my stuff
// import display manager file
#include "../header_files/entity_manager.h"

using namespace std;

// include self
#include "../header_files/animation_handler.h"

// generate the Animation display manager static instance indicator
DisplayManager *Animation::display_manager = 0;

// constructor
AnimationNode::AnimationNode (const int sprite_id) {

    this->sprite_id = sprite_id;
    this->next_node = nullptr;

}

// creates the next linked node
void AnimationNode::createNextNode (const int sprite_id) {

    this->next_node = new AnimationNode(sprite_id);

}

// returns the next linked node
AnimationNode* AnimationNode::getNextNode () {

    return this->next_node;

}

// sets the next node to be a given node
void AnimationNode::setNextNode (AnimationNode *next_node) {

    this->next_node = next_node;

}

// returns the stored sprite id
int AnimationNode::getSpriteID () {

    return this->sprite_id;

}

// adds a sprite to the loop
void Animation::addSprite (const int sprite_id) {

    this->animation_loop.second->createNextNode(sprite_id);

}

void Animation::getDisplayManager () {

    // texture managaer initialisation for Animation
    display_manager = display_manager->getInstance();

}

// constructor
Animation::Animation (int* sprites, const int length, const int loop_back) {

    // create first sprite
    AnimationNode *loop_node = new AnimationNode(sprites[0]);
    // assign it to start and current
    this->animation_loop.first = loop_node;
    this->resetLoop();

    // add the rest of the id's in the animation
    for (int x = 1; x < length; x++) {

        // add the node
        this->addSprite(sprites[x]);
        
        // keep note of the pointer if this is the node
        // where the animation should loop to
        if (x == loop_back) loop_node = this->animation_loop.second->getNextNode();

        // set current to equal the next
        this->nextSprite();

    }

    // set the loop back point to the last node
    this->animation_loop.second->setNextNode(loop_node);

}

// sets the current sprite to the next sprite
void Animation::nextSprite () {

    this->animation_loop.second = this->animation_loop.second->getNextNode();

}

// reset the current sprite to the start sprite
void Animation::resetLoop () {

    this->animation_loop.second = this->animation_loop.first;

}

// gets the sprite id of the current node
int Animation::getSpriteID () {

    return this->animation_loop.second->getSpriteID();

}

// uses the display manager to render to the window
void Animation::renderSprite (const int x, const int y) {

    this->display_manager->addRenderTask(this->getSpriteID(), x, y);

}

// gets the index of the animation that contains
// a given string
int AnimationHandler::getAnimationIndex (string state) {

    for (int x = 0; x < this->length; x++) {

        if (this->animations[x].first == state) {

            return x;

        }

    }

    // announce that the index could not be found
    return 0;

}

// changes the class to start playing a different animation
void AnimationHandler::startNewAnimation (string state) {

    // set new animation details
    this->current_animation = state;

    this->current_animation_index = this->getAnimationIndex(state);

    // reset the animation
    this->animations[this->current_animation_index].second->resetLoop();

}

//constructor
AnimationHandler::AnimationHandler (vector < pair < string, Animation* > > animations, const int length) {

    // set length
    this->length = length;

    // get the animation information
    copy(animations.begin(), animations.end(), back_inserter(this->animations));

}

// handles the change to the next frame of an animation,
// or the change to a new animation entirely
void AnimationHandler::update (string state) {

    // if this is a new animation, start it
    if (this->current_animation != state) {

        this->startNewAnimation(state);

    } else {

        this->animations[this->current_animation_index].second->nextSprite();

    }

}

// render the entities current apperance based on the
// setting of the current animation
void AnimationHandler::render (const int x, const int y) {

    this->animations[this->current_animation_index].second->getSpriteID();

    this->animations[this->current_animation_index].second->renderSprite(x, y);

}