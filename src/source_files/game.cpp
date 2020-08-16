// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"

// esential includes
#include <iostream>
#include <SDL.h>
using namespace std;

// include self
#include "../header_files/game.h"

// constructor
Game::Game (const char* window_title, const int x_pos, const int y_pos,
        const int width, const int height, const bool fullscreen_bool) {
    // initialiseation of game window and other required content

    int flags = 0;
    if(fullscreen_bool) flags = SDL_WINDOW_FULLSCREEN;

    // -------------------- initialisation --------------------

    // game window initialisation
    this->window = SDL_CreateWindow(window_title, x_pos, y_pos, width, height, flags);
    
    // renderer initialisation
    this->renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
    
    // -------------------- errors? --------------------
    cout << "---------- testing game intialisation ----------" << endl;
    cout << "window : " << ((this->window) ? "OK" : "error") << endl;
    cout << "renderer : " << ((this->renderer) ? "OK" : "error") << endl;

    this->running = true;

}

void Game::handleGameEvents() {  //const char* event) {

    SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
	
        case SDL_QUIT :
            this->running = false;
            break;
	
        default:
		    break;
	
    }

}
        
void Game::update () {

    this->cntr++;
    cout << this->cntr << endl;

}
        
// updates the render displayed on the screen
void Game::renderScreen () {

    // clear the current render
    SDL_RenderClear(this->renderer);

    // render current state
    SDL_RenderPresent(this->renderer);

}

bool Game::isRunning() {return this->running;}

void Game::gameLoop(){

}

// deconstructor    
Game::~Game () {
    // clean memory of the game

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    cout << "game successfully closed" << endl;

}