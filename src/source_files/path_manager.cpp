// esential includes
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <utility>
#include <vector>

// include my stuff
// import play space manager file
#include "../header_files/play_space.h"

using namespace std;

// include self
#include "../header_files/path_manager.h"


// constructor
PathNode::PathNode () {

    this->initialise();

}

// initialise the class
void PathNode::initialise () {

    this->parent_cost = 9420;
    this->parent = make_pair(0, 0);

}

// updates the class with information
void PathNode::update (double cost, const int x, const int y) {
    
    this->parent_cost = cost;
    this->parent = make_pair(y, x);

}

// constructors
PathManager::PathManager (const int width, const int height) {

    this->width = width;
    this->height = height;

    // initialise the extended board, and the path board
    for (int y = 0; y < this->height; y++) {
       
        vector <bool> b;
        vector <PathNode *> p;

        for (int x = 0; x < this->width; x++) {

            b.push_back(false);
            p.push_back(new PathNode());

        }

        this->extended_board.push_back(b);
        this->path_board.push_back(p);

    }

    // get the play space instance
    this->play_space = this->play_space->getInstance();

    cout << "Path manager:" << ((true) ? "OK" : "error") << endl;

}

// reinitialises the class for use
void PathManager::reinitialise() {

    this->is_found = false;

    for (int y = 0; y < this->height; y++) {

        for (int x = 0; x < this->width; x++) {

            this->extended_board[y][x] = false;
            this->path_board[y][x]->initialise();
        
        }

    }    

}

// finds if a given x and y is the x and y of the start
bool PathManager::isStart (const int x, const int y) {

    return ((this->current_location.x == x) && (this->current_location.y == y));

}

// finds if a given x and y is the x and y of the end
bool PathManager::isEnd (const int x, const int y) {

    if ((this->destination_location.x == x) && (this->destination_location.y == y)) {

        this->is_found = true;
        return true;

    } else {

        return false;

    }

}

// calculates the huristic value for any position
// with respect to the destination using distance formula
float PathManager::calculateHuristic (const int x, const int y) {

    int a = abs((x - this->destination_location.x));
    int b = abs((y - this->destination_location.y));

    return (double) sqrt((a * a) + (b * b));

}

// exstends a single child
void PathManager::createChild (const int x, const int y, const int direction) {

    // if it is not a wall add it to the list
    if (this->play_space->isWall(x, (y - 1))) {

        // calculate it's huristic
        double h = ((this->holder.first) + (this->calculateHuristic(x, y)));

        // add it to the queue
        this->queue.insert(make_pair(h, make_pair(direction, make_pair(y, x))));

        // update it's info
        this->path_board[y][x]->update(h, this->holder.second.second.second, this->holder.second.second.first);

    // else mark it as extended
    } else {

        this->extended_board[y][x] = true;

    }

}

// facilitates the exstension of a queue memebers children
void PathManager::extendPath () {

    int y = this->holder.second.second.first;
    int x = this->holder.second.second.second;
    int direction = this->holder.second.first;

    // up
    // not done and able based on direction
    if (((!(this->extended_board[(y - 1)][x])) && (direction != 2))) {

        this->createChild(x, (y - 1), 0);

        if (this->isEnd(x, (y - 1))) return;

    }

    // right
    // not done and able based on direction
    if (((!(this->extended_board[y][(x + 1)])) && (direction != 3))) {

        this->createChild((x + 1), y, 1);

        if (this->isEnd((x + 1), y)) return;

    }

    // down
    // not done and able based on direction
    if (((!(this->extended_board[(y + 1)][x])) && (direction != 0))) {

        this->createChild(x, (y + 1), 2);

        if (this->isEnd(x, (y + 1))) return;

    }
        
    // left
    // not done and able based on direction
    if (((!(this->extended_board[y][(x - 1)])) && (direction != 1)) ) {

        this->createChild((x - 1), y, 3);

        if (this->isEnd((x - 1), y)) return;

    }

}

// after calculations, finds the direction of the next move that should
// be taken
int PathManager::findNextMoveDirection(const int x, const int y) {

    // if the next is the start, then figure out what the,
    // direction on the next move should be
    if (this->isStart(this->path_board[y][x]->parent.second, this->path_board[y][x]->parent.first)) {

        int new_direction = this->current_direction;

        // using the second step find the next move direction
        // by finding it's direction relative to the start

        // right, left
        if (this->path_board[y][x]->parent.second != x) {

            // right or left
            new_direction += ((this->path_board[y][x]->parent.second < x) ? 1 : 3);

        // up, down
        } else {

            // up or down
            new_direction += ((this->path_board[y][x]->parent.first > y) ? 0 : 2);

        }

        if (new_direction >= 4) new_direction -= 4;

        return new_direction;

    // else keep going down the path
    } else {

        return this->findNextMoveDirection(this->path_board[y][x]->parent.second, this->path_board[y][x]->parent.first);
    
    }

}

// returns the direction the entity should move into
// to get to it's destination
int PathManager::calculateNextMove(Location current_location, Location destination_location, const int current_direction) {

    // copy over
    this->current_location = current_location;
    this->destination_location = destination_location;
    this->current_direction = current_direction;

    int new_direction;

    pair <int, int> relative_left, relative_right, relative_front;

    switch (current_direction) {
    
        // if the direction is up
        case (0) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_front = make_pair((this->current_location.y - 1), this->current_location.x);
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;

        // if the direction is right
        case (1) :

            relative_left = make_pair((this->current_location.y - 1), this->current_location.x);
            relative_front = make_pair(this->current_location.y, (this->current_location.x + 1));
            relative_right = make_pair((this->current_location.y + 1), this->current_location.x);

        break;

        // if the direction is down
        case (2) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x + 1));
            relative_front = make_pair((this->current_location.y + 1), this->current_location.x);
            relative_right = make_pair(this->current_location.y, (this->current_location.x - 1));

        break;

        // if the direction is left
        case (3) :

            relative_left = make_pair((this->current_location.y + 1), this->current_location.x);
            relative_front = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair((this->current_location.y - 1), this->current_location.x);

        break;
    
    }

    // perform short circuit test
    // if there are walls to the left and the right, it doesn't really
    // matter what this whole function returns. if there is no choice that,
    // can currently be made other then forwards then choose forwards
    if (this->play_space->isWall(relative_left.second, relative_left.first) && this->play_space->isWall(relative_right.second, relative_right.first)) {

        // if forwards is also blocked give the command to turn around
        if (this->play_space->isWall(relative_front.second, relative_front.first)) {

            new_direction = ((this->current_direction + 2) % 4);

        // else continue forward
        } else {

            new_direction = this->current_direction;

        }

    // if the short circuit is not the case however, calculate a path to the objective
    } else {

        this->queue.insert(make_pair(0.0, make_pair(this->current_direction, make_pair(this->current_location.y, this->current_location.x))));

        this->isEnd(this->current_location.x, this->current_location.y);

        while (((!this->queue.empty()) && (!this->is_found))) {

            // put the next position into the holder
            this->holder = *this->queue.begin();

            // remove it
            this->queue.erase(this->queue.begin());

            // mark it as extended
            this->extended_board[holder.second.second.first][holder.second.second.second] = true;

            // extend the path
            this->extendPath();

        }

        // if the calculations worked the destination should have a cost, 
        // if it doesn't then the entity should be told to turn to the left
        if (!(this->path_board[this->destination_location.y][this->destination_location.x]->parent_cost)) {

            this->findNextMoveDirection(this->destination_location.x, this->destination_location.y);
        
        } else {

            new_direction = ((this->current_direction + 3) % 4);

        }
    
    }

    // reinitialise for next time
    this->reinitialise();

    // return the choice
    return new_direction;

}

// randomly chosses the next move that should be
// taken by the ghost assuming that there is a decision
// to be made
int PathManager::randomlyChooseNextMove (Location current_location, const int current_direction) {

    // copy over
    this->current_location = current_location;
    this->destination_location = destination_location;
    this->current_direction = current_direction;

    int new_direction;

    pair <int, int> relative_left, relative_right, relative_front;

    switch (current_direction) {
    
        // if the direction is up
        case (0) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_front = make_pair((this->current_location.y - 1), this->current_location.x);
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;

        // if the direction is right
        case (1) :

            relative_left = make_pair((this->current_location.y - 1), this->current_location.x);
            relative_front = make_pair(this->current_location.y, (this->current_location.x + 1));
            relative_right = make_pair((this->current_location.y + 1), this->current_location.x);

        break;

        // if the direction is down
        case (2) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x + 1));
            relative_front = make_pair((this->current_location.y + 1), this->current_location.x);
            relative_right = make_pair(this->current_location.y, (this->current_location.x - 1));

        break;

        // if the direction is left
        case (3) :

            relative_left = make_pair((this->current_location.y + 1), this->current_location.x);
            relative_front = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair((this->current_location.y - 1), this->current_location.x);

        break;
    
    }

    // perform short circuit test
    // if there are walls to the left and the right, it doesn't really
    // matter what this whole function returns. if there is no choice that,
    // can currently be made other then forwards then choose forwards
    if (this->play_space->isWall(relative_left.second, relative_left.first) && this->play_space->isWall(relative_right.second, relative_right.first)) {

        // if forwards is also blocked give the command to turn around
        if (this->play_space->isWall(relative_front.second, relative_front.first)) {

            new_direction = ((this->current_direction + 2) % 4);

        // else continue forward
        } else {

            new_direction = this->current_direction;

        }

    // if the short circuit is not the case however, calculate a path to the objective
    } else {

        vector <int> choices;

        choices.clear();
        if (!this->play_space->isWall(relative_left.second, relative_left.first)) choices.push_back(3);
        if (!this->play_space->isWall(relative_front.second, relative_front.first)) choices.push_back(0);
        if (!this->play_space->isWall(relative_right.second, relative_right.first)) choices.push_back(1);

        int choice = genRanNumberInRange(0, (choices.size() - 1));


        new_direction = ((this->current_direction + choices[choice]) % 4);

    }

    // reinitialise for next time
    this->reinitialise();

    // return the choice
    return new_direction;

}