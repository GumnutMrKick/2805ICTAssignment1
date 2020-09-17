// esential includes
#include <stdio.h>
#include <math.h>
#include <ctime>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"

using namespace std;

#ifndef play_space_H
#define play_space_H

class GameBlock {

    private:

        // properties
        DisplayManager *display_manager;
        char* type;
        int id, x, y;

    public:

        // constructor
        GameBlock (const int id, const int x, const int y, const char* type = "wall");
        
        // adds this play space block to the render queue
        void addToRenderQueue ();

        // returns the result of a check to see if the type is
        // equal to a given string
        bool checkIf(const char *str);

};

class PlaySpace {

    private:

        // properties
        int width, height;

        GameBlock **game_board;

        // constructor
        PlaySpace (const int gamemode, const int segments_wide, const int segments_tall);

        // plugs the exits on the outskirts of the board
        void plugSquareBoardLeaks ();

        // intialises the game board for the square game
        void squareInitialisation ();
        
        // plugs the exits on the outskirts of the board
        void plugHexagonBoardLeaks ();

        // intialises the game board for the hexagon game
        void hexagonInitialisation ();

    public:

        // instance holder for static singleton class
        static PlaySpace *instance;

        // gets the static instance of the singleton class
        static PlaySpace *getInstance (const int gamemode, const int segments_wide, const int segments_tall);

        // triggers all the game blocks to add themselves to the render queue
        void renderPlaySpace ();

        // checks for a pellet at x, y and returns the result,
        // if found the pellet is removed
        int checkForPellet (const int x, const int y);

        // checks for a wall at x, y and returns the result
        bool isWall (const int x, const int y);

};

#endif