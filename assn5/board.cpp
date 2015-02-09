
#include "board.h"

// Initialize a hex board of size board_size*board_size and the constructor
// of the DisjointSet class.
Board::Board(int board_size) : union_p1(DisjointSet(board_size * board_size)),
                               union_p2(DisjointSet(board_size * board_size)) {
    size = board_size;
    winner = "";

    // Sets a size*size grid with all cells (indices) containg the enum EMPTY
    grid = vector<State>(size * size, Board::EMPTY);

    // Keeps track of separate graphs for each player's moves.
    graph_p1 = Graph(size * size);
    graph_p2 = Graph(size * size);
}

int Board::get_size() {
  return size;
}

string Board::get_winner() {
    return winner;
}

// Checks for winner each time a player makes a move.
void Board::check_for_winner(int cell, string player) {
    if(player == "BLACK") {
        //BLACK wins from top row to bottom row or vice-versa.
        // Check each node in top and bottom rows againts the current
        // cell. If it is conneceted to both rows, player BLACK has won.
        for(int row_top = 0; row_top < size; ++row_top)
            if(union_p1.is_connected(row_top, cell)) {
                for(int row_bot = size * (size - 1); row_bot < size * size; ++row_bot) {
                    if(union_p1.is_connected(row_bot, cell)) {
                        winner = "BLACK";
                        return;
                    }
                }
               break;
           }
    } else {
        // WHITE wins from left column to right column or vice-versa.
        // Check each node in left and right column againts the current
        // cell. If it is conneceted to both columns, player WHITE has won.
        for(int col_left = 0; col_left < size * size; col_left += size)
            if(union_p2.is_connected(col_left, cell)) {
                for(int col_right = size - 1; col_right < size * size; col_right += size) {
                    if(union_p2.is_connected(col_right, cell)) {
                        winner = "WHITE";
                        return;
                     }
                }
                break;
            }
      }
}

// Checks for valid input between 0 <= size of the board.
bool Board::is_valid_entry(int row, int col, string player) {
    if(row >= size || row < 0 || col >= size || col < 0) {
        return false;
    }

    // Keep track of where we are on the board.
    int cell = (row * size) + col;

    // Cell can't be in a WHITE or BLACK state.
    if(grid[cell] == Board::EMPTY) {
        if(player == "BLACK") {
            grid[cell] = Board::BLACK ;
        } else {
            grid[cell] = Board::WHITE ;
        }
        check_grid(cell, player);
        return true;
    } else {
        return false;
    }
}

// Creates the graph using the hex board representation.
void Board::bridge(int cell, size_t node, string player) {
    if(player == "BLACK") {
       if(grid[node] == Board::BLACK) {
           graph_p1.add_edge(cell, node, 1);
           union_p1.union_set(cell, node);
       }
    } else {
        if(grid[node] == Board::WHITE) {
            graph_p2.add_edge(cell, node, 1);
            union_p2.union_set(cell, node);
        }
    }
}

// Adds all possible connections from each hex. There are 9 cases that must
// be handled differently depending for where we are on the map.
void Board::check_grid(int cell, string player) {
    // All possible neighbors of a hexagon.
    size_t hex_r   = cell + 1;
    size_t hex_l   = cell - 1;
    size_t hex_b_r = cell + size;
    size_t hex_b_l = cell + (size - 1);
    size_t hex_t_r = cell - (size - 1);
    size_t hex_t_l = cell - size;

    if(cell == 0) {
        // Case 1: Top left corner of grid. Only two possible neighbors.
        bridge(cell, hex_r, player);
        bridge(cell, hex_b_r, player);

    } else if(cell == size - 1) {
        // Case 2: Top right corner of grid. Only three possible neighbors.
        bridge(cell, hex_l, player);
        bridge(cell, hex_b_r, player);
        bridge(cell, hex_b_l, player);

    } else if(cell == size * (size -1)) {
        // Case 3: Bottom left corner of grid. Only three neighbors.
        bridge(cell, hex_r, player);
        bridge(cell, hex_t_l, player);
        bridge(cell, hex_t_r, player);

    } else if(cell == size * size - 1) {
        // Case 4: Bottom right corner. Only two neighbors.
        bridge(cell, hex_l, player);
        bridge(cell, hex_t_l, player);

    } else if(cell < size) {
        // Case 5: Top Row (exlcuding corners.) Four possible neighbor connections.
        bridge(cell, hex_l, player);
        bridge(cell, hex_r, player);
        bridge(cell, hex_b_r, player);
        bridge(cell, hex_b_l, player);

    } else if(cell > size * (size - 1)) {
        // Case 6: Bottom row (exlcuding corners). Four possible neighbors
        bridge(cell, hex_l, player);
        bridge(cell, hex_r, player);
        bridge(cell, hex_t_l, player);
        bridge(cell, hex_t_r, player);

    } else if(cell % size == 0) {
        // Case 7: Outer left column, exlcuding corners. Four possible connections.
        bridge(cell, hex_r, player);
        bridge(cell, hex_b_r, player);
        bridge(cell, hex_t_l, player);
        bridge(cell, hex_t_r, player);

    } else if(cell % size == size - 1) {
        // Case 8: Outer right column, exlcuding corners. Four possible connections.
        bridge(cell, hex_l, player);
        bridge(cell, hex_b_r, player);
        bridge(cell, hex_t_l, player);
        bridge(cell, hex_b_l, player);

    } else {
        // Case 9: Internal nodes. Six possible neighbors.
        bridge(cell, hex_l, player);
        bridge(cell, hex_r, player);
        bridge(cell, hex_b_r, player);
        bridge(cell, hex_t_l, player);
        bridge(cell, hex_b_l, player);
        bridge(cell, hex_t_r, player);
    }

    check_for_winner(cell, player);
}

// Overloads the << operator to print the Board object.
ostream& operator<<(ostream& out, Board board) {
    // Keeps track on where we are on the grid.
    int current;

    string padding = "            ";
    out << padding + "  ";
    // Prints top column header.
    for(int i = 1; i <= board.size; ++i) {
        out << i % 10  << " " ;
    }
    out << endl;
    for(int row = 0; row < board.size; ++row) {
         if(row > 8) {
            out << "           ";
         } else {
            out << padding;
         }
        for(int col = 0 ; col < board.size; ++col) {
            current = row * board.size + col;

            // Pretty print left column rows.
            if(col == 0) {
                out << (row + 1) << "  ";
            }

            if(board.grid[current] == Board::BLACK) {
                out << "B ";
            } else if(board.grid[current] == Board::WHITE) {
                out << "W ";
            } else {
                out << "- ";
            }

            // Pretty print right column rows.
            if(col == board.size - 1) {
                out  << " " << (row + 1) ;
            }
        }
        out << endl;
        // Indent the next row by +1 each time.
        for(int j =0; j < row ; ++j) {
            out << " ";
        }
       out << " ";
    }
    out << padding + "  ";

    // Prints bottom column header.
    for(int i = 1; i <= board.size; ++i) {
        out << " " << i % 10  ;
    }
    return out;
}
