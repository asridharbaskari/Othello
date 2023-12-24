//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#ifndef OTHELLO_STANDARDVIEW_H
#define OTHELLO_STANDARDVIEW_H


#include <utility>
#include <string>
#include "../Model/Model.h"

namespace Othello {
    class StandardView {
    public:
        StandardView() = default;

        // Input methods
        static int GetBoardSize();
        static std::pair<std::string, std::string> GetPlayerNames();

        // Output methods
        void PrintBoard(Model *model) ;

        Move GetMove(Othello::Model *model);
    };
}


#endif //OTHELLO_STANDARDVIEW_H
