// esential includes
#include <stdio.h>
#include <bits/stdc++.h>
#include <utility>

// include my stuff
// import play space manager file
#include "../header_files/play_space.h"

using namespace std;

#ifndef path_manager_H
#define path_manager_H

class PathNode {

    public:

        // properties
        double parent_cost;
        pair <int, int> parent;

        // constructor
        PathNode ();

        // initialise the class
        void initialise ();

        // updates the class with information
        void update (double cost, const int x, const int y);

};

class PathManager {

    private:

        // properties
        int width, height, chossen_direction;
        bool is_found, **extended_board;
        PathNode*** path_board;

        PlaySpace *play_space = nullptr;

        Location current_location, destination_location;

        //          huristic        direction    y    x
        set < pair < double, pair < int, pair < int , int > > > > queue;

        // temporaily holds a queue position
        pair < double, pair < int, pair < int , int > > > holder;

    public:

        // constructors
        PathManager (const int width, const int height);

        // reinitialises the class for use
        void reinitialise ();

        // finds if a given x and y is the x and y of the start
        bool isStart (const int x, const int y);

        // finds if a given x and y is the x and y of the start
        bool isEnd (const int x, const int y);

        // calculates the huristic value for any position
        // with respect to the destination using distance formula 
        float calculateHuristic (const int x, const int y);

        // creates a single child
        void createChild (const int x, const int y, const int direction);

        // facilitates the exstension of a queue memebers children
        void extendPath ();

        // after calculations, finds the direction of the next move that should
        // be taken
        int findNextMoveDirection(const int x, const int y);

        // returns the direction the entity should move into
        // to get to it's destination
        int calculateNextMove(Location current_location, Location destination_location, const int current_direction);

};

#endif