// esential includes
#include <stdio.h>
#include <string>
#include <utility>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"

using namespace std;

#ifndef animation_handler_H
#define animation_handler_H

// a class that will be used to implement the logic
// of the animation loops
class AnimationNode {

    private:

        int sprite_id;
        AnimationNode *next_node;

    public:

        // constructor
        AnimationNode (const int sprite_id);

        // creates the next linked node
        void createNextNode (const int sprite_id);

        // returns the next linked node
        AnimationNode *getNextNode ();

        // sets the next node to be a given node
        void setNextNode (AnimationNode * next_node);

        // returns the stored sprite id
        int getSpriteID ();

};

class Animation {

    private:
        // properties
        // display manager
        DisplayManager *display_manager;
        // loop holder - 1 : start, 2 : current position
        pair <AnimationNode *, AnimationNode *> animation_loop;

        // adds a sprite to the loop
        void addSprite (const int sprite_id);

    public:

        // constructor
        Animation (int* sprites, const int length, const int loop_back = 0);

        // sets the current sprite to the next sprite
        void nextSprite ();

        // reset the current sprite to the start sprite
        void resetLoop ();

        // gets the sprite id of the current node
        int getSpriteID ();

        // uses the display manager to render to the window
        void renderSprite (const int x, const int y);

};

class AnimationHandler {

    private:

        // properties
        int frame, current_animation_index, length;
        const int target = 5;
        string current_animation;
        pair <string, Animation>* animations;

        // gets the index of the animation that contains
        // a given string
        int getAnimationIndex (string str);

        // changes the class to start playing a different animation
        void startNewAnimation (string state);

    public:

        //constructor
        AnimationHandler (pair <string, Animation>* animations, const int length);

        // handles the next frame of the game, rendering the frames,
        // it should given the circumstances
        void update(string state, const int x, const int y);

};

#endif