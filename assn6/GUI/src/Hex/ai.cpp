#include "ai.h"

AI::AI(Board& currentBoard) : board(currentBoard) {
    // Iterate through the current play board. If there are empty cells
    // we create a tuple of this postion.
    vector<Board::State>::iterator it;
    mcTrials.reserve(board.size * board.size - 1);

    int position = 0;
    for(it = board.grid.begin(); it != board.grid.end(); ++it) {
        if(*it == Board::State::EMPTY) {
            mcTrials.push_back(make_tuple(board, position, 0));
        }
        position += 1;
    }
}

int AI::getBestMove() {
    vector<tuple<Board, int, int> >::iterator it;

    // Perform monte carlo trials on each of the available postions
    // to determine the best move.
    for(it = mcTrials.begin(); it != mcTrials.end(); ++it) {
        get<2>(*it) = findBestMove(get<0>(*it), get<1>(*it));
    }

    // Iterate through the vector. Checks the score of each tuple and returns the
    // vector the tuple with the highest score. .
   return get<1>(*max_element(mcTrials.begin(), mcTrials.end(), [] (tuple<Board,int, int> t1, tuple<Board,int, int> t2)
          { return get<2>(t1) < get<2>(t2);
          }));
}

int AI::findBestMove(Board board, int position) {
    vector<tuple<Board, int, int> >::iterator it;
    vector<int> movesLeft;
    movesLeft.reserve(mcTrials.size() - 1);

    for(it = mcTrials.begin(); it != mcTrials.end(); ++it) {
        if (get<1>(*it) != position) {
            movesLeft.push_back(get<1>(*it));
        }
    }

    // Runs 1,000 simulated games with the current state of the board.
    // Returns the position with the best score. This will be the AI's
    // best move.
    int score = 0;
    int row = position / board.size;
    int col = position % board.size;
    board.is_valid_entry(row, col, "WHITE");

    for(int i = 0; i < 1000 ; ++i) {
        Board tempBoard = board;
        random_shuffle(movesLeft.begin(), movesLeft.end());

        for(size_t j = 0; j < movesLeft.size() / 2; ++j) {
             row = movesLeft[j] / board.size;
             col = movesLeft[j] % board.size;
             tempBoard.is_valid_entry(row, col, "WHITE");
        }
        // Update the score for this position.
        if (tempBoard.get_winner() == "WHITE") {
            score++;
        }
    }
    return score;
}
