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

void GameBlock::getDisplayManager () {

    // texture managaer initialisation for GameBlock
    display_manager = display_manager->getInstance();

}

// constructor
GameBlock::GameBlock (const int id, const int x, const int y, const char* type) {

    

}

// adds this play space block to the render queue
void GameBlock::addToRenderQueue () {



}

// returns the result of a check to see if the type is
// equal to a given string
bool GameBlock::checkIf (const char *str) {



}

// constructor
PlaySpace::PlaySpace (const int gamemode, const int segments_wide, const int segments_tall) {

    // texture managaer initialisation for GameBlock
    GameBlock::getDisplayManager();

}

// plugs the exits on the outskirts of the board
void PlaySpace::plugSquareBoardLeaks () {



}

// intialises the game board for the square game
void PlaySpace::squareInitialisation () {



}
        
// plugs the exits on the outskirts of the board
void PlaySpace::plugHexagonBoardLeaks () {



}

// intialises the game board for the hexagon game
void PlaySpace::hexagonInitialisation () {



}

// gets the static instance of the singleton class
PlaySpace *PlaySpace::getInstance (const int gamemode, const int segments_wide, const int segments_tall) {



}

// triggers all the game blocks to add themselves to the render queue
void PlaySpace::renderPlaySpace () {



}

// checks for a pellet at x, y and returns the result,
// if found the pellet is removed
int checkForPellet (const int x, const int y) {



}

// checks for a wall at x, y and returns the result
bool isWall (const int x, const int y) {



}