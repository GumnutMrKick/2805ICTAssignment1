// include my stuff
// import key bindings file
#include "../header_files/control_bindings.h"
// import display manager file
#include "../header_files/display_manager.h"
// import play space file
#include "../header_files/play_space.h"
// import info bar manager file
#include "../header_files/info_bar_manager.h"

// esential includes
#include <iostream>
#include <SDL.h>
using namespace std;

// include self
#include "../header_files/game.h"
// import entity manager file
#include "../header_files/entity_manager.h"
// import info bar manager file
#include "../header_files/info_bar_manager.h"

// file global properties
// general
int info_bar_addition = 1;
int cntr = 0;

// constructor
Game::Game (const char* window_title, const int x_pos, const int y_pos, const int gamemode,
    const int segments_wide, const int segments_tall) {
    
    // initialisation
    // texture managaer initialisation
    this->display_manager = display_manager->getInstance(window_title, x_pos, y_pos, gamemode, segments_wide, (segments_tall + info_bar_addition));
    // play space initialisation
    this->play_space = play_space->getInstance(gamemode, segments_wide, segments_tall);
    // entity manager initialisation
    this->entity_manager = new EntityManager(0);
    // info bar manager initialisation
    this->info_bar = new InfoBarManager(segments_wide, segments_tall, ((info_bar_addition * 16) * 11));

    // -------------------- errors? --------------------
    cout << "texture manager : " << ((this->display_manager) ? "OK" : "error") << endl;
    cout << "entity manager : " << ((this->entity_manager) ? "OK" : "error") << endl;
    cout << "info bar manager : " << ((true) ? "OK" : "error") << endl;

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



    // -------------------- update --------------------






    // -------------------- update --------------------

    cntr++;

    if (cntr > 799) {

        cntr = 0;

    }

    cntr += 50;

    // -------------------- render --------------------

    // render entities


    // render map
    this->play_space->renderPlaySpace();

    // update and render the info bar
    this->info_bar->updateInfoBar(0, cntr);
    this->info_bar->renderInfoBar();

}
        
// updates the render displayed on the screen
void Game::renderScreen () {

    this->display_manager->updateScreen();

}

bool Game::isRunning() {return this->running;}

// deconstructor    
Game::~Game () {
    // clean memory of the game

    this->display_manager->~DisplayManager();

}