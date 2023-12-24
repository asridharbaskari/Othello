//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#ifndef OTHELLO_MODEL_H
#define OTHELLO_MODEL_H


#include "Player.h"

namespace Othello {
    class Model {
    public:
        Model();
        void Init(int board_size, std::string black_name, std::string white_name);

        // Board editing utility
        void AddPiece(Coordinate coordinate, Color color);
        void InvertCell(Coordinate coordinate);


        // Getters & commonly used board state
        Color GetCellColor(Coordinate coordinate) const;
        int GetBoardSize() const;
        bool IsGameOver() const;
        bool CanMove(Player* player) const;
        bool IsValidMove(Move move) const;
        bool TurnValid() const;
        std::vector<Coordinate> GetTilesFlipped(Move move) const;

        // Active Player Methods
        Color GetActiveColor() const;
        std::string GetActiveName() const;
        void ChangeTurn();


    private:
        Player* black_;
        Player* white_;
        std::vector<std::vector<Cell>> board_;
        int board_size_;
        Player* active_player_;
        bool Inbounds(int coordinate) const;
    };
}



#endif //OTHELLO_MODEL_H
