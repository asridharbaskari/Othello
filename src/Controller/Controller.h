//
// Created by Aadithyaa Sridharbaskari  on 11/26/23.
//

#ifndef OTHELLO_CONTROLLER_H
#define OTHELLO_CONTROLLER_H

#include "../View/StandardView.h"
#include "../Model/Model.h"

namespace Othello {
    class Controller {
    public:
        Controller();
        void SetUpGame();
        void PlayGame();
    private:
        Model* model_;
        StandardView* view_;

        void EnactMove(Move move);
    };
}


#endif //OTHELLO_CONTROLLER_H
