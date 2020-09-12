// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
#include "../header_files/display_manager.h"

// esential includes
#include <iostream>
#include <SDL.h>
using namespace std;

// include self
#include "../header_files/game.h"

// constructor
Game::Game (const char* window_title, const int x_pos, const int y_pos, const int width,
    const int height, const bool fullscreen_bool, const bool is_square) {
    
    // initialiseation

    // texture managaer initialisation
    this->display_manager = display_manager->getInstance(window_title, x_pos, y_pos, width, height, fullscreen_bool, is_square);

    // -------------------- errors? --------------------
    cout << "texture manager : " << ((this->display_manager) ? "OK" : "error") << endl;

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
    // cout << this->cntr << endl;

    this->display_manager->addRenderTask(1, this->cntr, 200);
    this->display_manager->addRenderTask(4, 500, 500);


    if (this->cntr > 799) {

        cntr = 0;

    }

}
        
// updates the render displayed on the screen
void Game::renderScreen () {

    this->display_manager->updateScreen();

}

bool Game::isRunning() {return this->running;}

void Game::gameLoop(){

}

// deconstructor    
Game::~Game () {
    // clean memory of the game

    this->display_manager->~DisplayManager();

}