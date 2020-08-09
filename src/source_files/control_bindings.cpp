// esential includes
#include <stdio.h>
#include <iostream>
#include <SDL.h>
using namespace std;

// include self
#include "../header_files/control_bindings.h"

// constructor
Control_bindings :: Control_bindings (const char* up, const char* left,
                                        const char* down, const char* right) {
    // bind commands to SDL keycodes

    this->up = up;
    this->left = left;
    this->down = down;
    this->right = right;

}
        
// SDL keycode to code command
const char * Control_bindings :: SDLToCommand (const char * keycode) {
    // the command word based on it being equal one of the bindings

    if (keycode == this->up) return "up";
    if (keycode == this->left) return "left";
    if (keycode == this->down) return "down";
    if (keycode == this->right) return "right";

    return "error";

}
        
// deconstructor    
Control_bindings :: ~Control_bindings () {}