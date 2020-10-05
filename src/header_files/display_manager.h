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

// render task data structure
struct RenderTask {

    int sprite_id, sprite_x, sprite_y;

};

// generates a valid sprite clipping
SDL_Rect genSquareSheetSprite (const int x, const int y, const int height = 0, const int width = 0);

// generates a valid version of the render task struct
RenderTask generateRenderTask(const int id, const int x, const int y);

// render task data structure
struct Location {

    int x, y;

};

// generates a valid version of the render task struct
Location generateLocationHolder(const int x, const int y);

// a class that manages the sprite_sheet display for the game
class DisplayManager {

    private:

        // properties
        // general information
        // stack
        stack <RenderTask> render_stack;

        // sprite_sheet holder
        SDL_Texture* sprite_sheet = nullptr;
        SDL_Rect sprite_locations[123]; // this is the maxium number of sprites
        // I know this is bad practice but I don't have time to fix it right now
        
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

        // constructor
        DisplayManager (const char* window_title, const int x_pos, const int y_pos, const int gamemode,
            const int segments_wide, const int segments_tall);

    public:

        // instance holder for static singleton class
        static DisplayManager *instance;

        static DisplayManager *getInstance(const char* window_title = "", const int x_pos = 0, const int y_pos = 0, const int gamemode = 0,
            const int segments_wide = 0, const int segments_tall = 0);

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