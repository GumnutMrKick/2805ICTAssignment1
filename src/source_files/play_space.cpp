// esential includes
#include <stdio.h>
#include <math.h>
#include <ctime>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"

using namespace std;

// include self
#include "../header_files/play_space.h"

// generate the playspace's static instance indicator
PlaySpace *PlaySpace::instance = 0;

// generate the GameBlock display manager static instance indicator
DisplayManager *GameBlock::display_manager = 0;

// the map segments with a ghost spawn in it [#][y][x]
int spawn_map_segments[10][11][13] = {

    // courtyard
    {{ 48, 38, 38, 38, 38, 43, 58, 46, 38, 38, 38, 38, 39 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  47, 60, 53, 54, 54, 57, 58, 57, 54, 54, 50, 60, 41 },
    {  47, 60, 55, 58, 58, 58, 58, 58, 58, 58, 55, 60, 41 },
    {  43, 60, 57, 58, 53, 54, 56, 54, 50, 58, 57, 60, 46 },
    {  58, 60, 58, 58, 55, 59, 59, 59, 55, 58, 58, 60, 58 },
    {  40, 60, 57, 58, 52, 54, 54, 54, 51, 58, 57, 60, 49 },
    {  47, 60, 55, 58, 58, 58, 58, 58, 58, 58, 55, 60, 41 },
    {  47, 60, 52, 54, 54, 57, 58, 57, 54, 54, 51, 60, 41 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  45, 44, 44, 44, 44, 40, 58, 49, 44, 44, 44, 44, 42 }},

    // skull keep
    {{ 58, 48, 38, 38, 38, 43, 58, 46, 38, 38, 38, 39, 58 },
    {  48, 43, 60, 60, 60, 60, 60, 60, 60, 60, 60, 46, 39 },
    {  47, 60, 60, 57, 53, 54, 54, 54, 50, 57, 60, 60, 41 },
    {  47, 60, 53, 55, 55, 59, 59, 59, 55, 53, 59, 60, 41 },
    {  43, 60, 55, 55, 52, 54, 56, 54, 51, 55, 55, 60, 46 },
    {  58, 60, 55, 55, 58, 58, 58, 58, 58, 55, 55, 60, 58 },
    {  40, 60, 55, 55, 58, 53, 54, 59, 58, 55, 55, 60, 49 },
    {  47, 60, 52, 51, 58, 52, 54, 51, 58, 52, 51, 60, 41 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  45, 40, 49, 40, 49, 40, 58, 49, 40, 49, 40, 49, 42 },
    {  58, 45, 42, 45, 42, 47, 58, 41, 45, 42, 45, 42, 58 }},

    // oooooohhhhhhhhhh
    {{ 58, 48, 38, 38, 38, 43, 58, 46, 38, 38, 38, 39, 58 },
    {  58, 47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41, 58 },
    {  48, 43, 60, 57, 54, 57, 60, 57, 54, 57, 60, 46, 39 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  43, 60, 59, 54, 54, 57, 58, 57, 54, 54, 59, 60, 46 },
    {  58, 60, 55, 58, 58, 58, 58, 58, 58, 58, 55, 60, 58 },
    {  40, 60, 55, 58, 53, 54, 56, 54, 50, 58, 55, 60, 49 },
    {  47, 60, 57, 58, 55, 59, 59, 59, 55, 58, 55, 60, 41 },
    {  47, 60, 58, 58, 52, 54, 54, 54, 51, 58, 58, 60, 41 },
    {  45, 44, 47, 58, 58, 58, 58, 58, 58, 58, 49, 44, 42 },
    {  58, 58, 45, 44, 44, 47, 58, 49, 44, 44, 42, 58, 58 }},
    
};

// the map segments without a ghost spawn in it [#][y][x]
int map_segments[10][11][13] = {

    // courtyard
    {{ 48, 38, 38, 38, 38, 43, 58, 46, 38, 38, 38, 38, 39 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  47, 60, 53, 54, 54, 57, 60, 57, 54, 54, 50, 60, 41 },
    {  47, 60, 55, 60, 60, 60, 61, 60, 60, 60, 55, 60, 41 },
    {  43, 60, 57, 60, 53, 54, 54, 54, 50, 60, 57, 60, 46 },
    {  58, 60, 60, 60, 55, 58, 58, 58, 55, 60, 60, 60, 58 },
    {  40, 60, 57, 60, 52, 54, 54, 54, 51, 60, 57, 60, 49 },
    {  47, 60, 55, 60, 60, 60, 60, 60, 60, 60, 55, 60, 41 },
    {  47, 60, 52, 54, 54, 57, 60, 57, 54, 54, 51, 60, 41 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  45, 44, 44, 44, 44, 40, 58, 49, 44, 44, 44, 44, 42 }},

    // skull keep
    {{ 58, 48, 38, 38, 38, 43, 58, 46, 38, 38, 38, 39, 58 },
    {  48, 43, 60, 60, 60, 60, 60, 60, 60, 60, 60, 46, 39 },
    {  47, 60, 60, 57, 60, 53, 54, 50, 60, 57, 60, 60, 41 },
    {  47, 60, 53, 59, 60, 55, 57, 55, 60, 53, 59, 60, 41 },
    {  43, 60, 55, 55, 60, 52, 56, 51, 60, 55, 55, 60, 46 },
    {  58, 60, 55, 55, 60, 60, 61, 60, 60, 55, 55, 60, 58 },
    {  40, 60, 55, 55, 60, 53, 54, 59, 60, 55, 55, 60, 49 },
    {  47, 60, 52, 51, 60, 52, 54, 51, 60, 52, 51, 60, 41 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  45, 40, 49, 40, 49, 40, 58, 49, 40, 49, 40, 49, 42 },
    {  58, 45, 42, 45, 42, 47, 58, 41, 45, 42, 45, 42, 58 }},

    // oooooohhhhhhhhhh
    {{ 58, 48, 38, 38, 38, 43, 58, 46, 38, 38, 38, 39, 58 },
    {  58, 47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41, 58 },
    {  48, 43, 60, 57, 54, 57, 60, 57, 54, 57, 60, 46, 39 },
    {  47, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 41 },
    {  43, 60, 59, 54, 54, 57, 60, 57, 54, 54, 59, 60, 46 },
    {  58, 60, 55, 60, 60, 60, 61, 60, 60, 60, 55, 60, 58 },
    {  40, 60, 55, 60, 57, 54, 54, 54, 57, 60, 55, 60, 49 },
    {  47, 60, 57, 60, 60, 60, 60, 60, 60, 60, 57, 60, 41 },
    {  47, 60, 60, 60, 57, 54, 54, 54, 57, 60, 60, 60, 41 },
    {  45, 44, 47, 60, 60, 60, 60, 60, 60, 60, 49, 44, 42 },
    {  58, 58, 45, 44, 44, 47, 58, 49, 44, 44, 42, 58, 58 }},
    
};

const int maps = 3, spawns = 3;


// seeds random number generation
void seedRanGen() {

    srand((unsigned) time(0));

}

// generates a random number with respect (inclusively) to a range
int genRanNumberInRange(const int min, const int max) {

    return (int) (min + (rand() % ((max - min) + 1)));

}

void GameBlock::getDisplayManager () {

    // texture managaer initialisation for GameBlock
    display_manager = display_manager->getInstance();

}

// constructor
GameBlock::GameBlock (const int sprite_id, const int x, const int y, char* type) {

    this->sprite_id = sprite_id;
    this->x = x;
    this->y = y;
    this->type = type;

}

// change the properties of the game block
void GameBlock::changeGameBlockProps (const int sprite_id, char* type) {

    this->sprite_id = sprite_id;
    this->type = type;

}

// adds this play space block to the render queue
void GameBlock::addToRenderQueue () {

    this->display_manager->addRenderTask(this->sprite_id, this->x, this->y);

}

// returns the result of a check to see if the type is
// equal to a given string
bool GameBlock::checkIf (char *str) {

    return ((this->type == str) ? true : false);

}

// constructor
PlaySpace::PlaySpace (const int gamemode, const int segments_wide, const int segments_tall) {

    // texture managaer initialisation for GameBlock
    GameBlock::getDisplayManager();
    
    // seeds random number generation
    seedRanGen();

    // initialise the game board properties
    this->width = (segments_wide * 13);
    this->height = (segments_tall * 11);

    // initialise the game board
    this->game_board = new GameBlock**[this->height];

    for (int x = 0; x < this->height; x++) {

        this->game_board[x] = new GameBlock*[this->width];

    }

    // start the initialisation the map layout variable
    int* layout[segments_tall];

    // randomly generate the map layout
    this->ranGenMapLayout(layout, segments_wide, segments_tall);

    // write the layout to the game board
    this->readAllSegmentsToPlaySpace(layout, segments_wide, segments_tall);

    // plug the outskirt leaks in the game board
    this->plugBoardLeaks(segments_wide, segments_tall);

}

// randomly generate the map
// left to right, top to bottom
void PlaySpace::ranGenMapLayout(int** layout, const int x, const int y) {

    // cycles y - columns
    for (int a = 0; a < y; a++) {

        // initialise the row
        layout[a] = new int[x];

        // cycle x - rows
        for (int b = 0; b < x; b++) {

            // assign random map
            layout[a][b] = genRanNumberInRange(0, maps);

        }

    }

    // randomly select spawn location
    layout[genRanNumberInRange(0, (y - 1))][genRanNumberInRange(0, (x - 1))] = genRanNumberInRange(100, (100 + spawns));

}


// loads an individual segment into the gameboard
void PlaySpace::readSegmentToPlaySpace (int segment[11][13], const int x, const int y) {

    // // cycles y - columns
    // for (int a = 0; a < y; a++) {

    //     // cycle x - rows
    //     for (int b = 0; b < x; b++) {

    //         // assign random map
    //         layout[a][b] = genRanNumberInRange(0, maps);

    //     }

    // }

}

// reads the different maps to a game borad
// left to right, top to bottom
void PlaySpace::readAllSegmentsToPlaySpace (int** layout, const int x, const int y) {

    // cycles y - columns
    for (int a = 0; a < y; a++) {

        // cycle x - rows
        for (int b = 0; b < x; b++) {

            this->readSegmentToPlaySpace(((layout[a][b] >= 100) ? spawn_map_segments[(layout[a][b] - 100)] : map_segments[layout[a][b]]), b, a);
            
        }

    }

}

// plugs the exits on the outskirts of the board
void PlaySpace::plugBoardLeaks (const int x, const int y) {

    //  y      x    stand in's
    int a = 0, b = 0;

    // plug left side
    for (; a < y; a++) {

        this->game_board[a][((b * 11) + 5)]->changeGameBlockProps(57, "wall");

    }

    // plug right side
    a = 0;
    b = (x - 1);

    for (; a < y; a++) {

        this->game_board[a][((b * 11) + 5)]->changeGameBlockProps(57, "wall");

    }

    // plug top side
    a = 0;
    b = 0;

    for (; b < x; b++) {

        this->game_board[((a * 13) + 6)][b]->changeGameBlockProps(57, "wall");

    }

    // plug bottom side
    a = (y - 1);
    b = 0;
    
    for (; b < x; b++) {

        this->game_board[((a * 13) + 6)][b]->changeGameBlockProps(57, "wall");

    }

}

// gets the static instance of the singleton class
PlaySpace *PlaySpace::getInstance (const int gamemode, const int segments_wide, const int segments_tall) {

    if (!instance) instance = new PlaySpace(gamemode, segments_wide, segments_tall);

    return instance;

}

// // triggers all the game blocks to add themselves to the render queue
// void PlaySpace::renderPlaySpace (GameBlock** ) {

//     // this->game_board
//     //replace me with the above line later

// }

// checks for a pellet at x, y and returns the result,
// if found the pellet is removed
int checkForPellet (const int x, const int y) {



}

// checks for a wall at x, y and returns the result
bool isWall (const int x, const int y) {



}