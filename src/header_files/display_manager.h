// esential includes
#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#ifndef display_manager_H
#define display_manager_H

// file global properties
// general
const int sprite_count = 123;

// square sprite sheet properties
const string square_sprite_sheet_file_path = "rescource_files/square_sprite_sheet.png";
const int square_sprite_sheet_width = 254;
const int square_sprite_sheet_height = 152;

// hexagon sprite sheet properties
const string hexagon_sprite_sheet_file_path = "rescource_files/hexagon_sprite_sheet.png";
const int hexagon_sprite_sheet_width = 254;
const int hexagon_sprite_sheet_height = 152;

// render task data structure
struct RenderTask {

    int sprite_id, sprite_x, sprite_y;

};

// generates a valid sprite clipping
SDL_Rect genSquareSheetSprite (const int x, const int y, const int height = 0, const int width = 0);


// generates a valid version of the render task struct
RenderTask generateRenderTask(const int id, const int x, const int y);


// a class that manages the texture display for the game
class DisplayManager {

    private:

        // properties
        // general information
        SDL_Texture *sprite_sheet = nullptr;
        SDL_Rect sprite_locations[sprite_count];

        // stack
        stack <RenderTask> render_stack;

        // texture holder
        SDL_Texture* texture = nullptr;
        
        // window holder
        SDL_Window *window = nullptr;

        // render holder
        SDL_Renderer* renderer = nullptr;

        bool openFile (const string path);

        // initialises the the square version of the display
        void squareInitialisation ();

        // initialises the the hexagon version of the display
        void hexagonInitialisation ();

        int renderTask(const SDL_Rect* sprite, const SDL_Rect* location);

    public:
    
        // constructor
        DisplayManager (const char* window_title, const int x_pos, const int y_pos, const int width,
    const int height, const bool fullscreen_bool, const bool is_square);
        
        // adds a render task to the queue
        void addRenderTask (const int id, const int x, const int y);

        // renders all the render tasks
        void renderTasks ();

        // updates game logic
        void updateScreen ();
        
        // deconstructor    
        ~DisplayManager ();

};

#endif