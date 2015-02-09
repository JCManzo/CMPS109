#include <ctime>
#include <iostream>
#include <limits>
#include "disjointset.h"
#include "board.h"
#include "ai.h"


// Loops until input given is a number.
int validInput() {
    int x;
    cin >> x;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Bad entry. Enter a NUMBER: ";
        cin >> x;
    }
    return x;
}

int main() {
    std::srand (unsigned (time(0)));
    int board_size;
    int row, col;

    cout << "Enter a game board size: ";
    cin >> board_size;

    Board board(board_size);

    srand((unsigned)time( NULL ));
    int total_moves = board_size * board_size;

    // Starting player
    string player = "BLACK";
    cout << endl << "~~Welcome to the game of Hex~~" << endl;
    cout << endl << "-Player BLACK goes from top to bottom-";
    cout << endl << "-Player WHITE goes from side to side-" << endl;
    cout << endl << board;
    for(int i = 0; i < total_moves; ++i) {
       row = 0;
       col = 0;
        if(player == "BLACK") {
            // Get the player input and check if it's a number. Throw
            // error if not a number. Next check if cell coordinates are valid.
            // If true, we break and proceed to AI. If false ask for player input again.
            cout << endl;
            cout << "Enter a row: ";
            row = validInput();
            if(!cin.fail()) {
                cout << "Enter a column: ";
                col = validInput();
            }
            while (true) {
                if(!board.is_valid_entry(row - 1, col - 1, player)) {
                    cout << "Try again. Row and column must be between 1 and " << board_size << endl;
                    cout << "Enter a row: ";
                    row = validInput();
                    if(!cin.fail()) {
                        cout << "Enter a column: ";
                        col = validInput();
                    }
                } else {
                    break;
                }
            }
        } else {
            cout << "AI is making move..."  << endl;

            AI ai(board);
            int move = ai.getBestMove();
            board.is_valid_entry(move / board_size, move % board_size, "WHITE");
        }

        // Display and check for a winner after every turn.
        cout << board << endl;
        if(board.get_winner() != "") {
            cout << endl << board << endl;
            cout << endl << "Player " << board.get_winner() << " won!" << endl;
            return 0;
        }
        // Switch player turn.
        player = (player == "BLACK") ? "WHITE" : "BLACK";
    }

    return 0;
}
