#ifndef AI_H
#define AI_H

#include <algorithm>
#include <tuple>
#include "board.h"

class AI {
    public:
        AI(Board& board);
        int findBestMove(Board board, int const position);
        int getBestMove();
    private:
        Board board;
        vector<tuple<Board, int, int> > mcTrials;
};

#endif
