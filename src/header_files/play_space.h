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

// seeds random number generation
void seedRanGen();

// generates a random number with respect (inclusively) to a range
int genRanNumberInRange(const int min, const int max);

class GameBlock {

    private:

        // properties
        static DisplayManager *display_manager;
        char* type;
        int sprite_id, x, y;

    public:

        // get display manager
        static void getDisplayManager ();

        // constructor
        GameBlock (const int sprite_id, const int x, const int y, char* type);

        // change the properties of the game block
        void changeGameBlockProps (const int sprite_id = 58, char* type = "empty");
        
        // adds this play space block to the render queue
        void addToRenderQueue ();

        // returns the result of a check to see if the type is
        // equal to a given string
        bool checkIf(char *str);

};

class PlaySpace {

    private:

        // properties
        int width, height;

        GameBlock ***game_board;

        // randomly generate the map
        // left to right, top to bottom
        void ranGenMapLayout (int** layout, const int x, const int y);

        // loads an individual segment into the gameboard
        void readSegmentToPlaySpace (int segment[11][13], const int x, const int y);

        // reads the different maps to a game borad
        // left to right, top to bottom
        void readAllSegmentsToPlaySpace (int** layout, const int x, const int y);

        // plugs the exits on the outskirts of the board
        void plugBoardLeaks (const int x, const int y);

        // constructor
        PlaySpace (const int gamemode, const int segments_wide, const int segments_tall);

    public:

        // instance holder for static singleton class
        static PlaySpace *instance;

        // gets the static instance of the singleton class
        static PlaySpace *getInstance (const int gamemode, const int segments_wide, const int segments_tall);

        // triggers all the game blocks to add themselves to the render queue
        void renderPlaySpace ();

        // checks for a pellet at x, y and returns the result,
        // if found the pellet is removed
        bool checkForPellet (const int x, const int y);

        // checks for a wall at x, y and returns the result
        bool isWall (const int x, const int y);

};

#endif