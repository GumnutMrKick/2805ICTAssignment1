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

    cout << "making";

    initialise();

}

// initialise the class
void PathNode::initialise () {

    this->parent_cost = 9420;
    this->parent = make_pair(0, 0);

}

// updates the class with information
void PathNode::update (double cost, const int x, const int y) {
cout << endl << "fuck everything, "<< cost << "   " << x << "  " << y << "  " << this->parent_cost << "  " << this->parent.first << "   " << this->parent.second;
    this->parent_cost = cost;
    cout << endl << "cost";
    this->parent = make_pair(y, x);
    cout << endl << "parent";

}

// constructors
PathManager::PathManager (const int width, const int height) {
cout << "hello";
cout << "looky here " << width << "  " <<  height << endl;
    this->width = width;
    this->height = height;
cout << "looky here " << this->width << "  " <<  this->height << endl;


    // initialise the extended board, and the path board
    for (int y = 0; y < this->height; y++) {
       
        cout << "haha";
        vector <bool> b;
        vector <PathNode *> p;

        for (int x = 0; x < this->width; x++) {
            cout << "hehe";
            b.push_back(false);
            p.push_back(new PathNode());
        }

        this->extended_board.push_back(b);
        this->path_board.push_back(p);

    }

    // get the play space instance
    this->play_space = this->play_space->getInstance();

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

// finds if a given x and y is the x and y of the start
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
cout << "wtf";
    // if it is not a wall add it to the list
    if (this->play_space->isWall(x, (y - 1))) {
cout <<endl<< "wtf true";

        // calculate it's huristic
        double h = ((this->holder.first) + (this->calculateHuristic(x, y)));
cout <<endl<< "h -g";
        // add it to the queue
        this->queue.insert(make_pair(h, make_pair(direction, make_pair(y, x))));
cout <<endl<< "h -g queue in";


        cout << y<< " "<< x << " "<< h << " " << this->holder.second.second.second << " " << this->holder.second.second.first;
        // update it's info
        this->path_board[y][x]->update(h, this->holder.second.second.second, this->holder.second.second.first);
cout <<endl<< "up -g";

    // else mark it as extended
    } else {
cout << "wtf false";
        this->extended_board[y][x] = true;

    }
cout << "wtf final";

}

// facilitates the exstension of a queue memebers children
void PathManager::extendPath () {
cout << "ok " << endl;

    int y = this->holder.second.second.first;
    int x = this->holder.second.second.second;
    int direction = this->holder.second.first;
cout << this->extended_board.size() << "      "<< this->extended_board[0].size()  <<"okdsfasdfasdfasdfasdfasdfasdf " << direction << endl;

    // up
    // not done and able based on direction
    if (((!(this->extended_board[(y - 1)][x])) && (direction != 2))) {

        this->createChild(x, (y - 1), 0);

        if (this->isEnd(x, (y - 1))) return;

    }
cout << "ok " << endl;

    // right
    // not done and able based on direction
    if (((!(this->extended_board[y][(x + 1)])) && (direction != 3))) {

        this->createChild((x + 1), y, 1);

        if (this->isEnd((x + 1), y)) return;

    }
cout << "ok " << endl;

    // down
    // not done and able based on direction
    if (((!(this->extended_board[(y + 1)][x])) && (direction != 0))) {

        this->createChild(x, (y + 1), 2);

        if (this->isEnd(x, (y + 1))) return;

    }
cout << "ok second last " <<((!(this->extended_board[y][(x - 1)])) && (direction != 1)) <<  endl;
        
    // left
    // not done and able based on direction
    if (((!(this->extended_board[y][(x - 1)])) && (direction != 1)) ) {

        cout << "working" << " " << (x - 1) << " " << y ;
        this->createChild((x - 1), y, 3);
cout << "working?" ;

        if (this->isEnd((x - 1), y)) return;
cout << "working final" ;
    }
cout << "ok final " << endl;

}

// after calculations, finds the direction of the next move that should
// be taken
int PathManager::findNextMoveDirection(const int x, const int y) {

    // if the next is the start, then figure out what the,
    // direction on the next move should be
cout << "ok " << endl;
    if (this->isStart(this->path_board[y][x]->parent.second, this->path_board[y][x]->parent.first)) {
cout << "ok " << endl;
        int new_direction = this->chossen_direction;

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

    cout << "fuck me ";

    // copy over and clean information
    this->current_location = current_location;
    this->current_location.x = ((this->current_location.x - (this->current_location.x % 16)) / 16);
    this->current_location.y = ((this->current_location.y - (this->current_location.y % 16)) / 16);
    this->destination_location = destination_location;
    this->destination_location.x = ((this->destination_location.x - (this->destination_location.x % 16)) / 16);
    this->destination_location.y = ((this->destination_location.y - (this->destination_location.y % 16)) / 16);
    this->chossen_direction = current_direction;

    cout << this->current_location.x << " sadasdasd " << this->current_location.x;

    pair <int, int> relative_left, relative_right;

            cout << "weeee" << endl;

    switch (current_direction) {
    
        // if the direction is up
        case (0) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;

        // if the direction is up
        case (1) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;

        // if the direction is up
        case (2) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;

        // if the direction is up
        case (3) :

            relative_left = make_pair(this->current_location.y, (this->current_location.x - 1));
            relative_right = make_pair(this->current_location.y, (this->current_location.x + 1));

        break;
        
        default :

            cout << "error : an invalid direction has been given";
     
        break;
    
    }

            cout << "weeee" << endl;


    // perform short circuit test
    // if there are walls to the left and the right, it doesn't really
    // matter what this whole function returns. if there is no choice that,
    // can currently be made other then forwards then choose forwards
    cout << relative_left.second << " " << relative_left.first << " " << relative_right.second << " " << relative_right.first << " " << ((!this->play_space->isWall(relative_left.second, relative_left.first)) && (!this->play_space->isWall(relative_right.second, relative_right.first))) << endl;
    if (((this->play_space->isWall(relative_left.second, relative_left.first)) && (this->play_space->isWall(relative_right.second, relative_right.first)))) {
            cout << "weeee" << endl;

        this->queue.insert(make_pair(0.0, make_pair(current_direction, make_pair(this->current_location.y, this->current_location.x))));
            cout << "weeee" << endl;

        this->isEnd(this->current_location.x, this->current_location.y);
            cout << "weeee" << endl;

        cout << endl;
        while (((!this->queue.empty()) && (!this->is_found))) {
            cout << "weeee" << endl;

            // put the next position into the holder
            this->holder = *this->queue.begin();

            cout << endl << "wow " << this->holder.first;

            // remove it
            this->queue.erase(this->queue.begin());
cout << "yeet";
            // mark it as extended
            this->extended_board[holder.second.second.first][holder.second.second.second] = true;
cout << "yeet";

            // extend the path
            this->extendPath();
cout << "yeet";

        }

        this->findNextMoveDirection(this->destination_location.x, this->destination_location.y);
cout << "yeet";

    }
cout << "yeet";

    int tobesent = this->chossen_direction;
    this->reinitialise();
    cout << "yay I got here" << this->chossen_direction << endl;
    return tobesent;

}