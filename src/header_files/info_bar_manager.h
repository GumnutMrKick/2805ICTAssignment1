// esential includes
#include <stdio.h>
#include <string>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"

using namespace std;

#ifndef info_bar_manager_H
#define info_bar_manager_H

class InfoBarManager {

    private:
        // properties
        // display manager
        DisplayManager *display_manager;
        // general information
        string state;
        int vertical_start, info_space_width, info_space_height, padding, player_score;

        // turns a single char into the appropriate char id
        int charToSpriteId (const char given_char);

        // turns a string into a array of ints
        void stringToSpriteIds (string str, int* ids);

        // calculates the correct start place of the info
        int calculateStartPoint (string align, const int length);

        // queues the render tasks for the info
        void renderInfo (int* info, const int x, const int y, const int end_point, const int start_point = 0);

        // queues the queueing of the different infos
        void renderInformation (int** infos, int* lengths, int* starts, const int info_count);

    public:

        // constructor
        InfoBarManager (const int width, const int height, const int info_space_height, const int lines = 3);

        // updates the info to be displayed by the class
        void updateInfoBar (const int state, const int score);

        // prepares the class properties to render the info
        void renderInfoBar ();

};



#endif