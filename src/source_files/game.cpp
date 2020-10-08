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
    const int segments_wide, const int segments_tall, Control_bindings &bindings) {
    
    // initialisation
    this->bindings_manager = new Control_bindings(bindings);
    // texture managaer initialisation
    this->display_manager = display_manager->getInstance(window_title, x_pos, y_pos, gamemode, segments_wide, (segments_tall + info_bar_addition));
    // play space initialisation
    this->play_space = play_space->getInstance(gamemode, segments_wide, segments_tall);
    // entity manager initialisation
    this->entity_manager = new EntityManager(gamemode);
    // info bar manager initialisation
    this->info_bar = new InfoBarManager(segments_wide, segments_tall, ((info_bar_addition * 16) * 11));

    // -------------------- errors? --------------------
    cout << "texture manager : " << ((this->display_manager) ? "OK" : "error") << endl;
    cout << "entity manager : " << ((this->entity_manager) ? "OK" : "error") << endl;
    cout << "info bar manager : " << ((this->info_bar) ? "OK" : "error") << endl;

    this->running = true;

}

// gets the users keyboard inputs
void Game::handleGameEvents() {  //const char* event) {

    SDL_Event event;

	while (SDL_PollEvent(&event)) {

        switch (event.type) {
        
            case SDL_KEYDOWN :

                int direction = this->bindings_manager->SDLToCommand(event.key.keysym.sym);
                if (direction != (-1)) this->entity_manager->updateInput(direction);

            break;

            case SDL_QUIT :

                cout << "the sdl quit event has been called";
                this->running = false;
            
            break;
        
        }

    }

}

// updates the games model and calls for all the components to
// add themselves to the render queue
void Game::update () {


    // -------------------- update --------------------






    // -------------------- update --------------------
    // update entities
    this->entity_manager->updateEntities();

    // -------------------- render --------------------

    // render entities
    this->entity_manager->renderEntities();

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