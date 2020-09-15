// esential includes
#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

// include self
#include "../header_files/display_manager.h"

// generate display manager's static instance indicator
DisplayManager *DisplayManager::instance = 0;

// generates a valid sprite clipping
SDL_Rect genSquareSheetSprite (const int x, const int y, const int height, const int width) {

    SDL_Rect sprite;

    const int xloc = ((x * 16) + (1 * x)), yloc = ((y * 16) + (1 * y));

    sprite.x = xloc;
    sprite.y = yloc;
    (height == 0) ? sprite.h = 16 : sprite.h = height;
    (width == 0) ? sprite.w = 16 : sprite.w = width;

    return sprite;

}

// generates a valid version of the render task struct
RenderTask generateRenderTask(const int id, const int x, const int y) {

    RenderTask task;

    task.sprite_id = id;
    task.sprite_x = x;
    task.sprite_y = y;

    return task;

}

// opens a texture through the use of a file path
bool DisplayManager::openFile (const string path) {

    // load in the sprite sheet
    SDL_Surface* loaded_sheet = IMG_Load(path.c_str());
    
    if (loaded_sheet == nullptr) {
		
        cout << "Unable to load image at file path" << endl;
        
        return false;
	
    }

    // create texture from surface
    this->texture = SDL_CreateTextureFromSurface(this->renderer, loaded_sheet);

    if( this->texture == NULL ) {

        cout << "unable to create texture";
    
    }

    return true;

}

// initialises the the square version of the display
void DisplayManager::squareInitialisation () {

    // text

        this->sprite_locations[0] = genSquareSheetSprite(0, 0); // a
        this->sprite_locations[1] = genSquareSheetSprite(1, 0); // b
        this->sprite_locations[2] = genSquareSheetSprite(2, 0); // c
        this->sprite_locations[3] = genSquareSheetSprite(3, 0); // d
        this->sprite_locations[4] = genSquareSheetSprite(4, 0); // e
        this->sprite_locations[5] = genSquareSheetSprite(5, 0); // f
        this->sprite_locations[6] = genSquareSheetSprite(6, 0); // g
        this->sprite_locations[7] = genSquareSheetSprite(7, 0); // h
        this->sprite_locations[8] = genSquareSheetSprite(8, 0); // i
        this->sprite_locations[9] = genSquareSheetSprite(9, 0); // j
        this->sprite_locations[10] = genSquareSheetSprite(10, 0); // k
        this->sprite_locations[11] = genSquareSheetSprite(11, 0); // l
        this->sprite_locations[12] = genSquareSheetSprite(12, 0); // m
        this->sprite_locations[13] = genSquareSheetSprite(13, 0); // n
        this->sprite_locations[14] = genSquareSheetSprite(14, 0); // o
        this->sprite_locations[15] = genSquareSheetSprite(0, 1); // p
        this->sprite_locations[16] = genSquareSheetSprite(1, 1); // q
        this->sprite_locations[17] = genSquareSheetSprite(2, 1); // r
        this->sprite_locations[18] = genSquareSheetSprite(3, 1); // s
        this->sprite_locations[19] = genSquareSheetSprite(4, 1); // t
        this->sprite_locations[20] = genSquareSheetSprite(5, 1); // u
        this->sprite_locations[21] = genSquareSheetSprite(6, 1); // v
        this->sprite_locations[22] = genSquareSheetSprite(7, 1); // w
        this->sprite_locations[23] = genSquareSheetSprite(8, 1); // x
        this->sprite_locations[24] = genSquareSheetSprite(9, 1); // y
        this->sprite_locations[25] = genSquareSheetSprite(10, 1); // z
        this->sprite_locations[26] = genSquareSheetSprite(11, 1); // !
        this->sprite_locations[27] = genSquareSheetSprite(12, 1); // 0
        this->sprite_locations[28] = genSquareSheetSprite(13, 1); // 1
        this->sprite_locations[29] = genSquareSheetSprite(14, 1); // 2
        this->sprite_locations[30] = genSquareSheetSprite(0, 2); // 3
        this->sprite_locations[31] = genSquareSheetSprite(1, 2); // 4
        this->sprite_locations[32] = genSquareSheetSprite(2, 2); // 5
        this->sprite_locations[33] = genSquareSheetSprite(3, 2); // 6
        this->sprite_locations[34] = genSquareSheetSprite(4, 2); // 7
        this->sprite_locations[35] = genSquareSheetSprite(5, 2); // 8
        this->sprite_locations[36] = genSquareSheetSprite(6, 2); // 9
        this->sprite_locations[37] = genSquareSheetSprite(8, 2, 16, 118); // namco

    // wall

        this->sprite_locations[38] = genSquareSheetSprite(10, 3); // external top wall
        this->sprite_locations[39] = genSquareSheetSprite(11, 3); // external top right wall
        this->sprite_locations[40] = genSquareSheetSprite(13, 5); // external top right internal corner
        this->sprite_locations[41] = genSquareSheetSprite(11, 4); // external right wall
        this->sprite_locations[42] = genSquareSheetSprite(11, 5); // external bottom right wall
        this->sprite_locations[43] = genSquareSheetSprite(13, 6); // external bottom right internal corner
        this->sprite_locations[44] = genSquareSheetSprite(10, 5); // external bottom wall
        this->sprite_locations[45] = genSquareSheetSprite(9, 5); // external bottom left wall
        this->sprite_locations[46] = genSquareSheetSprite(12, 6); // external bottom left internal corner
        this->sprite_locations[47] = genSquareSheetSprite(9, 4); // external left wall
        this->sprite_locations[48] = genSquareSheetSprite(9, 3); // external top left wall
        this->sprite_locations[49] = genSquareSheetSprite(12, 5); // external top left wall internal corner
        this->sprite_locations[50] = genSquareSheetSprite(13, 3); // internal top right wall
        this->sprite_locations[51] = genSquareSheetSprite(13, 4); // internal bottom right wall
        this->sprite_locations[52] = genSquareSheetSprite(12, 4); // internal bottom left wall
        this->sprite_locations[53] = genSquareSheetSprite(12, 3); // internal top left wall
        this->sprite_locations[54] = genSquareSheetSprite(11, 4); // internal horizontal wall
        this->sprite_locations[55] = genSquareSheetSprite(13, 7); // internal vertical wall
        this->sprite_locations[56] = genSquareSheetSprite(0, 8); // internal horizontal door
        this->sprite_locations[57] = genSquareSheetSprite(2, 8); // internal end cap wall
        this->sprite_locations[58] = genSquareSheetSprite(3, 8); // blank space
        this->sprite_locations[59] = genSquareSheetSprite(3, 8); // ghost respawn

    // pick-ups

        this->sprite_locations[60] = genSquareSheetSprite(8, 1); // pellet
        this->sprite_locations[61] = genSquareSheetSprite(10, 4); // power pellet

    // ghosts

        // blinky

            this->sprite_locations[62] = genSquareSheetSprite(4, 4); // blinky up 1
            this->sprite_locations[63] = genSquareSheetSprite(5, 4); // blinky up 2
            this->sprite_locations[64] = genSquareSheetSprite(0, 4); // blinky right 1
            this->sprite_locations[65] = genSquareSheetSprite(1, 4); // blinky right 2
            this->sprite_locations[66] = genSquareSheetSprite(6, 4); // blinky down 1
            this->sprite_locations[67] = genSquareSheetSprite(7, 4); // blinky down 2
            this->sprite_locations[68] = genSquareSheetSprite(2, 4); // blinky left 1
            this->sprite_locations[69] = genSquareSheetSprite(3, 4); // blinky left 2

        // pinky
            this->sprite_locations[70] = genSquareSheetSprite(4, 5); // pinky up 1
            this->sprite_locations[71] = genSquareSheetSprite(5, 5); // pinky up 2
            this->sprite_locations[72] = genSquareSheetSprite(0, 5); // pinky right 1
            this->sprite_locations[73] = genSquareSheetSprite(1, 5); // pinky right 2
            this->sprite_locations[74] = genSquareSheetSprite(6, 5); // pinky down 1
            this->sprite_locations[75] = genSquareSheetSprite(7, 5); // pinky down 2
            this->sprite_locations[76] = genSquareSheetSprite(2, 5); // pinky left 1
            this->sprite_locations[77] = genSquareSheetSprite(3, 5); // pinky left 2

        // inky
            this->sprite_locations[78] = genSquareSheetSprite(4, 6); // inky up 1
            this->sprite_locations[79] = genSquareSheetSprite(5, 6); // inky up 2
            this->sprite_locations[80] = genSquareSheetSprite(0, 6); // inky right 1
            this->sprite_locations[81] = genSquareSheetSprite(1, 6); // inky right 2
            this->sprite_locations[82] = genSquareSheetSprite(6, 6); // inky down 1
            this->sprite_locations[83] = genSquareSheetSprite(7, 6); // inky down 2
            this->sprite_locations[84] = genSquareSheetSprite(2, 6); // inky left 1
            this->sprite_locations[85] = genSquareSheetSprite(3, 6); // inky left 2

        // clyde
            this->sprite_locations[86] = genSquareSheetSprite(4, 7); // clyde up 1
            this->sprite_locations[87] = genSquareSheetSprite(5, 7); // clyde up 2
            this->sprite_locations[88] = genSquareSheetSprite(0, 7); // clyde right 1
            this->sprite_locations[89] = genSquareSheetSprite(1, 7); // clyde right 2
            this->sprite_locations[90] = genSquareSheetSprite(6, 7); // clyde down 1
            this->sprite_locations[91] = genSquareSheetSprite(7, 7); // clyde down 2
            this->sprite_locations[92] = genSquareSheetSprite(2, 7); // clyde left 1
            this->sprite_locations[93] = genSquareSheetSprite(3, 7); // clyde left 2

        // scared

            this->sprite_locations[94] = genSquareSheetSprite(8, 4); // scared 1
            this->sprite_locations[95] = genSquareSheetSprite(8, 7); // scared 2
            this->sprite_locations[96] = genSquareSheetSprite(8, 5); // scared 3
            this->sprite_locations[97] = genSquareSheetSprite(8, 6); // scared 4

        // dead

            this->sprite_locations[98] = genSquareSheetSprite(11, 7); // dead up
            this->sprite_locations[99] = genSquareSheetSprite(9, 6); // dead right
            this->sprite_locations[100] = genSquareSheetSprite(12, 6); // dead down
            this->sprite_locations[101] = genSquareSheetSprite(10, 6); // dead left

    // player

        this->sprite_locations[102] = genSquareSheetSprite(8, 3); // pacman stopped
        this->sprite_locations[103] = genSquareSheetSprite(0, 3); // pacman up
        this->sprite_locations[104] = genSquareSheetSprite(1, 3); // pacman up open
        this->sprite_locations[105] = genSquareSheetSprite(3, 3); // pacman right
        this->sprite_locations[106] = genSquareSheetSprite(2, 3); // pacman right open
        this->sprite_locations[107] = genSquareSheetSprite(5, 3); // pacman down
        this->sprite_locations[108] = genSquareSheetSprite(4, 3); // pacman down open
        this->sprite_locations[109] = genSquareSheetSprite(6, 3); // pacman left
        this->sprite_locations[110] = genSquareSheetSprite(7, 3); // pacman left open
        this->sprite_locations[111] = genSquareSheetSprite(14, 3); // pacman pop
        this->sprite_locations[112] = genSquareSheetSprite(14, 4); // pacman explode 1
        this->sprite_locations[113] = genSquareSheetSprite(14, 5); // pacman explode 2
        this->sprite_locations[114] = genSquareSheetSprite(14, 6); // pacman explode 3
        this->sprite_locations[115] = genSquareSheetSprite(14, 7); // pacman explode 4

    // misc
        
        this->sprite_locations[116] = genSquareSheetSprite(9, 6); // ??? 1
        this->sprite_locations[117] = genSquareSheetSprite(10, 6); // ??? 2
        this->sprite_locations[118] = genSquareSheetSprite(7, 2); // debug texture

}

// initialises the the hexagon version of the display
void DisplayManager::hexagonInitialisation () {



}

int DisplayManager::renderTask(const SDL_Rect* sprite, const SDL_Rect* location) {

	//Render to screen
	return SDL_RenderCopy( this->renderer, this->texture, sprite, location);

}

// constructor
DisplayManager::DisplayManager (const char* window_title, const int x_pos, const int y_pos, const int width,
    const int height, const bool fullscreen_bool, const bool is_square, const int segments_wide, const int segments_tall) {

    // initialiseation of game window and other required content
    int flags = 0;
    if(fullscreen_bool) flags = SDL_WINDOW_FULLSCREEN;

    // -------------------- initialisation --------------------

    // game window initialisation
    this->window = SDL_CreateWindow(window_title, x_pos, y_pos, width, height, flags);
    
    // renderer initialisation
    this->renderer = SDL_CreateRenderer(window, -1, 0);

    // -------------------- errors? --------------------
    cout << "---------- testing game intialisation ----------" << endl;
    
    // initialize PNG loading
    cout << "PNG loading : " << (IMG_Init(IMG_INIT_PNG) ? "OK" : "error") << endl;
    cout << "window : " << ((this->window) ? "OK" : "error") << endl;
    cout << "renderer : " << ((this->renderer) ? "OK" : "error") << endl;

    string path;

    path = (is_square) ? square_sprite_sheet_file_path : hexagon_sprite_sheet_file_path;

    this->openFile(path);

    // run the appropriate initialisation
    (is_square) ? this->squareInitialisation() : this->hexagonInitialisation();

}

DisplayManager *DisplayManager::getInstance (const char* window_title, const int x_pos, const int y_pos, const int width,
    const int height, const bool fullscreen_bool, const bool is_square, const int segments_wide, const int segments_tall) {

    if (!instance) instance = new DisplayManager(window_title, x_pos, y_pos, width, height, fullscreen_bool, is_square, segments_wide, segments_tall);
    return instance;
            
}

// adds a render task to the queue
void DisplayManager::addRenderTask (const int id, const int x, const int y) {

    this->render_stack.push(generateRenderTask(id, x, y));

}

// renders all the render tasks
void DisplayManager::renderTasks () {
    
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
    
    RenderTask tmp_task;

    // while there are still tasks to render
    while (!this->render_stack.empty()) {

        // load in the task and sprite
        tmp_task = this->render_stack.top();
        const SDL_Rect *tmp_sprite = &this->sprite_locations[tmp_task.sprite_id];
        
        // set sprite render location
        SDL_Rect window_location = { tmp_task.sprite_x, tmp_task.sprite_y, tmp_sprite->w, tmp_sprite->h};

    	//Render to screen
	    if (this->renderTask(tmp_sprite, &window_location) < 0) {

            cout << "render task failed" << endl;

        }

        // remove completed render task and tmp sprite
        this->render_stack.pop();
        delete tmp_sprite;

    }

};

// updates window
void DisplayManager::updateScreen () {

    this->renderTasks();    
    SDL_RenderPresent(this->renderer);

};
        
// deconstructor    
DisplayManager::~DisplayManager () {

    // clean memory of the game
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    cout << "display module successfully closed" << endl;

};