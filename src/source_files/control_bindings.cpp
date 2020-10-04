// esential includes
#include <stdio.h>
#include <iostream>
#include <SDL.h>
using namespace std;

// include self
#include "../header_files/control_bindings.h"

// constructor
Control_bindings :: Control_bindings (const int up, const int left,
                                        const int down, const int right) {
    // bind commands to SDL keycodes

    this->up = up;
    this->left = left;
    this->down = down;
    this->right = right;

}
        
// SDL keycode to code command
int Control_bindings :: SDLToCommand (const int keycode) {
    // the command word based on it being equal one of the bindings

    if (keycode == this->up) return 0;
    if (keycode == this->right) return 1;
    if (keycode == this->down) return 2;
    if (keycode == this->left) return 3;

    return -1;

}
        
// deconstructor    
Control_bindings :: ~Control_bindings () {}