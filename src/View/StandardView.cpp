//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#include "StandardView.h"
#include <iostream>

using std::cout, std::cin, std::string, std::pair;

int Othello::StandardView::GetBoardSize() {
    // TODO: Add validation for an even board size
    int board_size;
    std::cout << "Enter an even board size: \n";
    std::cin >> board_size;
    return board_size;
}

pair<std::string, std::string> Othello::StandardView::GetPlayerNames() {
    string black_name, white_name;
    cout << "Enter the Name of player with the black pieces: \n";
    cin >> black_name;
    cout << "Enter the Name of player with the white pieces: \n";
    cin >> white_name;
    return {black_name, white_name};
}

// Design taken from Code Review Stack Exchange
// https://codereview.stackexchange.com/questions/51716/shortest-possible-way-of-printing-a-specific-board
void Othello::StandardView::PrintBoard(Model *model) {
    int size = model->GetBoardSize();
    string letter_bar, decoration_bar;

    // We want to pad each line with a consistent amount of spaces
    int total_padding = (int)log10(size);
    // Construct letter bar
    for (int _ = 0; _ < total_padding; _++) {
        letter_bar += " ";
    }
    for (char letter = 'a'; (int)letter < 'a' + size; letter++) {
        letter_bar += letter;
        letter_bar += " ";
    }

    // Construct decoration bar
    for (int _ = 0; _ < total_padding; _++) {
        decoration_bar += " ";
    }
    decoration_bar += "+";
    for (int _ = 0; _ < size; _++) {
        decoration_bar += "--";
    }
    decoration_bar += "--+";

    // Print board
    cout << "   " << letter_bar << '\n';
    cout << " " << decoration_bar << '\n';
    for (int row = 0; row < size; row++) {
        int num_digits = (int)log10(row + 1);
        for (int _ = 0; _ < total_padding - num_digits; _++) {
            cout << " ";
        }
        cout << row + 1 << "| ";
        for (int column = 0; column < size; column++) {
            Color color = model->GetCellColor({row, column});
            switch (color) {
                case BLACK:
                    std::cout << 'B';
                    break;
                case WHITE:
                    std::cout << 'W';
                    break;
                case EMPTY:
                    std::cout  << ' ';
                    break;
                default:
                    throw std::logic_error("Cell has not been initialized.");
            }
            cout << " ";
        }
        std::cout << " |\n";
    }
    cout << " " << decoration_bar << '\n';
}

Move Othello::StandardView::GetMove(Othello::Model *model) {
    Move move{0};
    do {
        PrintBoard(model);
        auto color = model->GetActiveColor();
        auto name = model->GetActiveName();
        cout << "It's your move " << name << "\n";
        cout << "You have the " << ToString(color) << " pieces\n";
        cout << "Enter move as space separated row number and column character\n";
        cout << "Ex. 1 a\n";
        int raw_row; char raw_col;

        // add some validation here later
        cin >> raw_row >> raw_col;
        int row = raw_row - 1;
        int column = tolower(raw_col)-'a';
        move = {row, column, color};

    } while (!model->IsValidMove(move));
    return move;
}




