//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#include "Model.h"

#include <utility>



Othello::Model::Model() : board_(0)
{}

void Othello::Model::AddPiece(Coordinate coordinate, Color color) {
    auto [row, column] = coordinate;
    auto& cell = board_.at(row).at(column);
    if (cell.color != EMPTY) {
        throw std::logic_error("You are trying to add a piece to a square that already has one.");
    }
    cell.color = color;
}

void Othello::Model::InvertCell(Coordinate coordinate) {
    auto [row, column] = coordinate;
    auto& cell = board_.at(row).at(column);
    Color curr_color = cell.color;
    if (curr_color == EMPTY) {
        throw std::logic_error("You are trying to invert a cell that is empty.");
    }
    else {
        Color new_color = (curr_color == BLACK) ? WHITE : BLACK;
        cell.color = new_color;
    }
}

void Othello::Model::Init(int board_size, std::string black_name, std::string white_name) {
    black_ = new Player(std::move(black_name), BLACK);
    white_ = new Player(std::move(white_name), WHITE);
    board_ = std::vector<std::vector<Cell>>(board_size, std::vector<Cell>(board_size));
    board_size_ = board_size;
    active_player_ = black_; // BLACK goes first by default
}

Color Othello::Model::GetCellColor(Coordinate coordinate) const {
    auto [row, column] = coordinate;
    auto cell = board_.at(row).at(column);
    return cell.color;
}

int Othello::Model::GetBoardSize() const {
    return board_size_;
}

bool Othello::Model::IsGameOver() const {
    return !CanMove(black_) && !CanMove(white_);
}

bool Othello::Model::CanMove(Othello::Player *player) const {
    int size = (int)board_.size();
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            // If the cell is occupied, skip
            if (GetCellColor({row, column}) != EMPTY) continue;
            // From this cell, check in all directions
            Move move = {row, column, player->GetPlayerColor()};
            if (!GetTilesFlipped(move).empty()) {
                return true;
            }
        }
    }
    return false;
}

bool Othello::Model::TurnValid() const{
    return CanMove(active_player_);
}

bool Othello::Model::IsValidMove(Move move) const {
    return !GetTilesFlipped(move).empty();
}

std::vector<Coordinate> Othello::Model::GetTilesFlipped(Move move) const {
    auto [coordinate, same_color] = move;
    auto [start_row, start_column] = coordinate;
    Color alt_color = (same_color == BLACK) ? WHITE : BLACK;
    std::vector<Coordinate> directions = {
            {0, 1}, // Horizontal
            {1, 0}, // Vertical
            {1, 1}, // Right Diagonal
            {1, -1} // Left Diagonal
    };

    // offset for forward and backwards pass
    std::vector<int> offsets = {
            -1,                 // Backward Pass
             1                  // Forward Pass
    };

    std::vector<Coordinate> tiles_flipped;
    for (auto& direction : directions) {
        // for each direction, we perform a forward and backward pass
        for (auto offset : offsets) {
            auto [row_activated, column_activated] = direction;

            // We collect all alternate-color pieces
            std::vector<Coordinate> potential_tiles_flipped;

            // neat trick for combining forward and backward passes into one loop
            int row_offset = offset * row_activated;
            int column_offset = offset * column_activated;
            int row = start_row + row_offset;
            int column = start_column + column_offset;

            // we add the potential tiles flipped once we encounter a tile of the same color
            bool completed_flip = false;

            // flip check loop
            while (Inbounds(row) && Inbounds(column)) {
                auto cell_color = GetCellColor({row, column});
                if (cell_color == alt_color) {
                    potential_tiles_flipped.push_back({row, column});
                } else if (cell_color == same_color) {
                    completed_flip = true;
                    break;
                } else {
                    completed_flip = false;
                    break;
                }

                // update
                offset += offset;
                row_offset = offset * row_activated;
                column_offset = offset * column_activated;
                row = start_row + row_offset;
                column = start_column + column_offset;
            }
            if (completed_flip) {
                // flip all intermediate tiles if flip is completed
                tiles_flipped.insert(tiles_flipped.end(),
                                     potential_tiles_flipped.begin(),
                                     potential_tiles_flipped.end());
            }
        }
    }
    return tiles_flipped;
}

void Othello::Model::ChangeTurn() {
    bool is_black = (active_player_ == black_);
    active_player_ = (is_black) ? white_ : black_;
}

bool Othello::Model::Inbounds(int coordinate) const {
    return (coordinate >= 0) && (coordinate < board_size_);
}

Color Othello::Model::GetActiveColor() const {
    return active_player_->GetPlayerColor();
}

std::string Othello::Model::GetActiveName() const {
    return active_player_->GetName();
}

//
//bool Othello::Model::FlipsVerticalTiles(Move move) const {
//    auto [coordinate, same_color] = move;
//    auto [start_row, start_column] = coordinate;
//    Color alt_color = (same_color == BLACK) ? WHITE : BLACK;
//    bool ok_above = (start_row + 1 >= board_size_) && GetPlayerColor({start_row + 1, start_column}) == alt_color;
//    bool ok_below = (start_row - 1 >= 0) && GetPlayerColor({start_row - 1, start_column}) == alt_color;
//    bool move_found;
//
//    // Check if we flip tiles above coordinate
//    move_found = false;
//    for (int row = start_row - 1; row >= 0 && ok_above; row--) {
//        if (GetPlayerColor({row, start_column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_above &= move_found;
//
//    // Check if we flip tiles below coordinate
//    move_found = false;
//    for (int row = start_row + 1; row < board_size_ && ok_below; row++) {
//        if (GetPlayerColor({row, start_column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_below &= move_found;
//
//    return ok_above || ok_below;
//}
//
//bool Othello::Model::FlipsHorizontalTiles(Move move) const {
//    auto [coordinate, same_color] = move;
//    auto [start_row, start_column] = coordinate;
//    Color alt_color = (same_color == BLACK) ? WHITE : BLACK;
//    bool ok_right = (start_column + 1 >= board_size_) && GetPlayerColor({start_row, start_column + 1}) == alt_color;
//    bool ok_left = (start_column - 1 >= 0) && GetPlayerColor({start_row, start_column - 1}) == alt_color;
//    bool move_found;
//    //TODO: Self-challenge: see if you can combine the below into one loop
//
//    // Check if we flip tiles to the right of coordinate
//    move_found = false;
//    for (int column = start_column + 1; column < board_size_ && ok_right; column++) {
//        if (GetPlayerColor({start_row, column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_right &= move_found;
//
//    // Check if we flip tiles to the left of coordinate
//    move_found = false;
//    for (int column = start_column - 1; column >= 0 && ok_left; column--) {
//        if (GetPlayerColor({start_row, column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_left&= move_found;
//
//    return ok_right || ok_left;
//}
//
//bool Othello::Model::FlipsDiagonalTiles(Move move) const {
//    auto [coordinate, same_color] = move;
//    auto [start_row, start_column] = coordinate;
//    Color alt_color = (same_color == BLACK) ? WHITE : BLACK;
//    bool ok_right_diag = (start_row + 1 >= board_size_ && start_column + 1 >= board_size_) && GetPlayerColor({start_row + 1, start_column + 1}) == alt_color;
//    bool ok_left_diag = (start_row - 1 >= 0) && GetPlayerColor({start_row - 1, start_column}) == alt_color;
//    bool move_found;
//
//    // Check if we flip tiles to the left diagonal of coordinate
//    move_found = false;
//    for (int row = start_row - 1; row >= 0 && ok_above; row--) {
//        if (GetPlayerColor({row, start_column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_above &= move_found;
//
//    // Check if we flip tiles below coordinate
//    move_found = false;
//    for (int row = start_row + 1; row < board_size_ && ok_below; row++) {
//        if (GetPlayerColor({row, start_column}) == same_color) {
//            move_found = true;
//            break;
//        }
//    }
//    ok_below &= move_found;
//
//    return ok_above || ok_below;
//}
