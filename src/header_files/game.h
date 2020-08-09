// esential includes
#include <SDL.h>

#ifndef game_H
#define game_H

class Game {

    private:

        // properties
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

    public:
    
        // constructor
        Game (const char* window_title, const int x_pos, const int y_pos,
                const int width, const int height, const bool fullscreen_bool);
        
        void handleGameEvent(const char* event);

        void update ();
        
        // updates the render displayed on the screen
        void renderScreen ();
        
        void gameLoop();
        
        // deconstructor    
        ~Game ();

};

#endif