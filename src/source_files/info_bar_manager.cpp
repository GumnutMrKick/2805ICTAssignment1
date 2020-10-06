// esential includes
#include <stdio.h>
#include <string>
#include <math.h>
#include <ctime>
#include <utility>

// include my stuff
// import display manager file
#include "../header_files/display_manager.h"

using namespace std;

// include self
#include "../header_files/info_bar_manager.h"


// turns a single char into the appropriate id
int InfoBarManager::charToSpriteId (const char given_char) {
    
    int intifiedchar = ((int)given_char);

    // check for letter
    if ((intifiedchar >= 97) && (intifiedchar <= 122)) {

        return (intifiedchar - 97);

    }

    // check for number
    if ((intifiedchar >= 47) && (intifiedchar <= 57)) {

        return (intifiedchar - 21);

    }
    
    // check for space
    if (intifiedchar == 32) {

        return 58;

    }

    // assume exclamation mark
    return 26;

}

// turns a string into a array of ints
void InfoBarManager::stringToSpriteIds (string str, int* ids) {

    // transform it's chars into ids
    for (int x = 0; x < (int) str.length(); x++) {

        ids[x] = this->charToSpriteId(str.at(x));

    }

}

// calculates the correct start place of the info
int InfoBarManager::calculateStartPoint (string align, const int length) {

    if (align == "center") {

        return ((this->info_space_width/2) - ((length * 16) / 2));

    }

    if (align == "right") {

        return (this->info_space_width - (length * 16));

    }
    
    return 0;

}

// queues the render tasks for the info
void InfoBarManager::renderInfo (int* info, const int x, const int y, const int end_point, const int start_point) {

    this->display_manager->addRenderTask(info[start_point], x, y);

    if (start_point < (end_point - 1)) this->renderInfo(info, (x + 16), y, end_point, (start_point + 1));

}

// queues the queueing of the different infos
void InfoBarManager::renderInformation (int** infos, int* lengths, int* starts, const int info_count) {

    int y = this->vertical_start;

    for (int x = 0; x < info_count; x++) {

        y += this->padding;
        this->renderInfo(infos[x], starts[x], y, lengths[x]);

    }

}

// constructor
InfoBarManager::InfoBarManager (const int width, const int height, const int info_space_height, const int lines) {

    // get the display manager instance
    this->display_manager = display_manager->getInstance();

    // set the vertical start
    this->vertical_start = (((height * 11) * 16) + 1);
    // set the width
    this->info_space_width = ((width * 13) * 16);
    // set the height
    this->info_space_height = info_space_height;

    // set the padding
    this->padding = ((info_space_height - (3 * 16)) / 3);

}

// updates the info to be displayed by the class
void InfoBarManager::updateInfoBar (const int state, const int score) {

    // update the state
    this->state = (state == 3) ? "you died" : ((state == 2) ? "invulnerable" : "vulnerable");
    // update the score
    this->player_score = score;
    
}

// prepares the class properties to render the info
void InfoBarManager::renderInfoBar () {

    // turn the score into a string
    string score_str_front = "score ", score_str_back = to_string(this->player_score), score_str;

    // pad the start of the score with zeros until the
    // number is seven digits long
    for (int x = 0; x < (7 - (int) score_str_back.length()); x++) {

        score_str_front = score_str_front + "0";

    }

    // assemble the score string
    score_str = score_str_front + score_str_back;

    // make the arrays
    int score_ids[(int) score_str.length()];
    int state_ids[(int) score_str.length()];
    int namco_ids[1] = {37}; // this is a weird sprite that has been custom made

    // get the sprite ids
    this->stringToSpriteIds(score_str, score_ids);
    this->stringToSpriteIds(this->state, state_ids);

    int* infos[] = {

        score_ids,
        state_ids,
        namco_ids

    };
    
    int lengths[] = {
                        (int) score_str.length(),
                        (int) this->state.length(),
                        1
                    };

    int starts[] = {
                        this->calculateStartPoint("left", (int) score_str.length()),
                        this->calculateStartPoint("center", (int) this->state.length()),
                        this->calculateStartPoint("right", 7)
                    };

    this->renderInformation(infos, lengths, starts, 3);

}