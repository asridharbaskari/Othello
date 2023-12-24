//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#include "Controller.h"


void Othello::Controller::SetUpGame() {
    // Get size of the board and player names
    int board_size = Othello::StandardView::GetBoardSize();
    auto [black_name, white_name] = Othello::StandardView::GetPlayerNames();

    // Create the board and players
    model_->Init(board_size, black_name, white_name);

    // Set up the board with the usual configuration
    int center_row = board_size / 2 - 1;
    int center_col = center_row;

    Coordinate top_left = {center_row, center_col};
    Coordinate top_right = {center_row, center_col + 1};
    Coordinate bottom_left = {center_row + 1, center_col};
    Coordinate bottom_right = {center_row + 1, center_col + 1};

    model_->AddPiece(top_left, WHITE);
    model_->AddPiece(top_right, BLACK);
    model_->AddPiece(bottom_left, BLACK);
    model_->AddPiece(bottom_right, WHITE);
    view_->PrintBoard(model_);
}

void Othello::Controller::PlayGame() {
    // Game ends when neither player can make a move
    while (!model_->IsGameOver()) {
        // Check if active player can make a move
        // If not, skip turn
        if (!model_->TurnValid()) {
            model_->ChangeTurn();
            continue;
        }
        // If active player cannot move, turn is skipped
        auto move = view_->GetMove(model_); // We need to use the model to check if move is valid
        this->EnactMove(move);
        model_->ChangeTurn();
    }
//    view_.DeclareWinner(model_.GetWinner());
}

void Othello::Controller::EnactMove(Move move) {
    auto [coordinate, color] = move;
    model_->AddPiece(coordinate, color);
    auto tiles_flipped = model_->GetTilesFlipped(move);
    for (auto& tile : tiles_flipped) {
        model_->InvertCell(tile);
    }
}

Othello::Controller::Controller() {
    model_ = new Model();
    view_ = new StandardView();
}

