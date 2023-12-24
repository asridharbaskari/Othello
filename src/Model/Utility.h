//
// Created by Aadithyaa Sridharbaskari  on 11/28/23.
//

#ifndef OTHELLO_UTILITY_H
#define OTHELLO_UTILITY_H

#include "Player.h"
enum Color { EMPTY, BLACK,  WHITE };

inline std::string ToString(Color color) {
    switch (color) {
        case EMPTY:
            return "empty";
        case BLACK:
            return "black";
        case WHITE:
            return "white";
    }
}

struct Coordinate {
    int row;
    int column;
};

struct Cell {
    Coordinate coordinate;
    Color color;
};

struct Move {
    Coordinate coordinate;
    Color color;
};


#endif //OTHELLO_UTILITY_H
