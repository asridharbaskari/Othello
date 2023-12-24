//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#include "Player.h"

#include <utility>

using std::vector;

Othello::Player::Player(std::string name, Color color) : name_(std::move(name)), color_(color) {
}

std::string Othello::Player::GetName() {
    return name_;
}

Color Othello::Player::GetPlayerColor() {
    return color_;
}



