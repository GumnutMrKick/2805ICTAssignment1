
// esential includes
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#ifndef texture_manager_H
#define texture_manager_H

// file global properties
// general
const int sprite_count = 123;

// square sprite sheet properties
const int square_sprite_sheet_width = 254;
const int square_sprite_sheet_height = 152;

// square sprite sheet properties
const int square_sprite_sheet_width = 254;
const int square_sprite_sheet_height = 152;


SDL_Rect *genSquareSheetSprite (const int x, const int y);


SDL_Rect *genSquareSheetSprite (const int x, const int y) {

    SDL_Rect sprite;

    const int xloc = ((x * 16) - (1 * x)), yloc = ((y * 16) - (1 * y));

    sprite.x = xloc;
    sprite.y = yloc;
    sprite.h = 16;
    sprite.w = 16;

    return &sprite;

}

















class TextureManager {

    private:

        // properties
        // general information
        SDL_Texture *sprite_sheet = nullptr;
        SDL_Rect sprite_locations[sprite_count];

    public:
    
        // constructor
        TextureManager (bool is_square);
        
        void addRenderTask (const int id, const int x, const int y);

        

        void renderTasks ();









                // is used to handle game events
        void handleGameEvents();  //const char* event);












        // updates game logic
        void update ();
        
        // updates the render displayed on the screen
        void renderScreen ();
        
        bool isRunning();

        void gameLoop();
        
        // deconstructor    
        ~TextureManager ();

};

// constructor
TextureManager::TextureManager (bool is_square, ) {

    // grab the sprites from the sprite sheet


}

TextureManager::addRenderTask (const int id, const int x, const int y) {
            
}

TextureManager::~TextureManager () {

}

#endif