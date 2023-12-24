//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H
#include <string>
#include "Utility.h"

namespace Othello {
    class Player {
    public:
        Player(std::string name, Color color);
        std::string GetName();
        Color GetPlayerColor();
    private:
        std::string name_;
        Color color_;
    };
}



#endif //OTHELLO_PLAYER_H
